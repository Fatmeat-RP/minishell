/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarle-m <acarle-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 18:02:45 by acarle-m          #+#    #+#             */
/*   Updated: 2022/07/24 03:46:57 by acarle-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int redirect_in(t_exec *cmd)
{
	int i;
	int	fd;

	i = 0;
	fd = -1;
	if (cmd->in[0] != NULL)
	{
		while (cmd->in[i] != NULL)
		{
			if (access(cmd->in[i], F_OK | R_OK) == -1)
				return (-1);
			fd = open(cmd->in[i], O_RDONLY);
			if (fd == -1)
				return (-1);
			dup2(fd, STDIN_FILENO);
			close(fd);
			i++;
		}
		return (i);
	}
	return (0);
}

void	redir_in_error(t_exec *cmd)
{
	if (redirect_in(cmd) == -1)
	{
		write(2, "minishell: ", 12);
		write(2, cmd->in[line_counter(cmd->in)],
			ft_strlen(cmd->in[line_counter(cmd->in)]));
		write(2, ": No such file or directory\n", 29);
		g_status = -1;
		exit (g_status);
	}
}

int redirect_out(t_exec *cmd)
{
	int	i;
	int	fd;

	i = 0;
	fd = -1;
	if (cmd->out[0] != NULL)
	{
		while (cmd->out[i] != NULL)
		{
			close(fd);
			if (cmd->is_append[i] == '0')
				fd = open(cmd->out[i], O_CREAT | O_WRONLY | O_TRUNC);
			else
				fd = open(cmd->out[i], O_CREAT | O_APPEND | O_WRONLY);
			i++;
		}
		if (fd != -1)
		{
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
	}
	return (0);
}

static int utils_hdoc(t_exec *cmd, int *pipefd)
{
	char	*line;
	size_t	tmp;

	signal(SIGINT, sig_int_child_handler);
	signal(SIGQUIT, sig_quit_handler);
	close(pipefd[0]);
	tmp = ft_strlen(cmd->limiter);
	line = readline("heredoc> ");
	while (line && ft_strncmp(line, cmd->limiter, tmp) != 0)
	{
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
		line = readline("heredoc> ");
	}
	free(line);
	free_exe(cmd);
	close(pipefd[1]);
	exit (0);
}

int here_doc(t_exec *cmd, t_instance *instance)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		free_instance(instance, 0);
		utils_hdoc(cmd, pipefd);
	}
	else
	{
		close(pipefd[1]);
		dup2(pipefd[0], 0);
		close(pipefd[0]);
		waitpid(pid, NULL, 0);
	}
	return (0);
}
