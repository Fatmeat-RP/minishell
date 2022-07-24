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

int redirect_in(t_exec *cmd)
{
	int i;
	int	fd;

	i = 0;
	fd = -1;
	if (cmd->in[0] != NULL)
	{
		while (cmd->in[i + 1] != NULL)
			i++;
		if (access(cmd->in[i], F_OK | R_OK) == -1)
			return (-1);
		fd = open(cmd->in[i], O_RDONLY);
		if (fd == -1)
			return (-1);
		dup2(fd, STDIN_FILENO);
		return (i);
	}
	return (-2);
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
			dup2(fd, STDOUT_FILENO);
	}
	return (0);
}

int here_doc(t_exec *cmd)
{
	char	*line;
	int		pipefd[2];
	pid_t	pid;

	line = 1;
	pid = fork();
	if (pid == -1)
		return(-1);
	if (pid)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		while (line != NULL && ft_strncmp(line, cmd->limiter, ft_strlen(cmd->limiter)) != 0)
		{
			line = readline("heredoc> ");
			write(pipefd[1], line, ft_strlen(line));
			free(line);
		}
		if (line)
			free(line);
		exit (0);
	}
	else
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
	}
	return (pipefd[0]);
}
