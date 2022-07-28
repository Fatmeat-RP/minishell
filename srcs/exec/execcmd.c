/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execcmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarle-m <acarle-m@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 01:23:04 by acarle-m          #+#    #+#             */
/*   Updated: 2022/07/28 01:23:04 by acarle-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	execuction(t_exec *cmd, t_instance *instance)
{
	int	ret;

	ret = 0;
	if (cmd->is_here_doc == true)
		here_doc(cmd, instance);
	signal(SIGINT, sig_int_child_handler);
	signal(SIGQUIT, sig_quit_handler);
	if (cmd->is_builtin == true)
	{
		while (instance->builtin->iter->next
			&& ft_strcmp(cmd->cmd[0], instance->builtin->iter->name) != 0)
			instance->builtin->iter = instance->builtin->iter->next;
		ret = (*instance->builtin->iter->fun)(cmd->cmd, instance);
	}
	else
		ret = execve(cmd->cmd[0], cmd->cmd, instance->envp);
	free_instance(instance, 0);
	free_exe(cmd);
	exit (ret);
}

int	choose_your_path(t_exec *cmd, t_instance *instance, int fd)
{
	if (fd != -1)
		return (execuction(cmd, instance));
	return (execve(cmd->cmd[0], cmd->cmd, instance->envp));
}

int	forklift(t_exec *cmd, t_instance *instance, int fd)
{
	int	pid;
	int	pipefd[2];

	if (pipe(pipefd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		redir_in_error(cmd);
		dup2(fd, STDIN_FILENO);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		close(fd);
		redirect_out(cmd);
		execuction(cmd, instance);
	}
	g_status = pid;
	close(fd);
	close(pipefd[1]);
	waitpid(pid, &g_status, 0);
	return (pipefd[0]);
}
