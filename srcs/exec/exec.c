/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarle-m <acarle-m@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 01:23:15 by acarle-m          #+#    #+#             */
/*   Updated: 2022/07/28 01:23:15 by acarle-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	exec_one_builtin(t_exec *cmd, t_instance *instance)
{
	int		save[2];

	save[0] = dup(0);
	save[1] = dup(1);
	if (cmd->is_here_doc == true)
		here_doc(cmd, instance);
	redir_in_error(cmd);
	redirect_out(cmd);
	while (instance->builtin->iter->next
		&& ft_strncmp(cmd->cmd[0], instance->builtin->iter->name,
			ft_strlen(instance->builtin->iter->name)) != 0)
		instance->builtin->iter = instance->builtin->iter->next;
	g_status = (*instance->builtin->iter->fun)(cmd->cmd, instance);
	dup2(save[0], 0);
	dup2(save[1], 1);
	close(save[0]);
	close(save[1]);
	return (g_status);
}

static int	exec_one_cmd(t_exec *cmd, t_instance *instance, int fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		signal(SIGINT, sig_int_child_handler);
		signal(SIGQUIT, sig_quit_handler);
		if (fd && cmd->is_here_doc == false)
		{
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		if (cmd->is_here_doc == true)
			here_doc(cmd, instance);
		redir_in_error(cmd);
		redirect_out(cmd);
		pid = execve(cmd->cmd[0], cmd->cmd, instance->envp);
		free_exe(cmd);
		exit(free_instance(instance, pid));
	}
	g_status = pid;
	waitpid(pid, &g_status, 0);
	return (close(fd));
}

static int	execution_solo(t_exec *cmd, t_instance *instance)
{
	if (cmd->is_builtin == true)
		return (exec_one_builtin(cmd, instance));
	else
		return (exec_one_cmd(cmd, instance, -1));
}

static int	execution_pipe(t_control_exec *exes, t_instance *instance)
{
	int	fd;

	fd = dup(STDIN_FILENO);
	while (exes->iter->next != NULL)
	{
		fd = forklift(exes->iter, instance, fd);
		exes->iter = exes->iter->next;
	}
	exec_one_cmd(exes->iter, instance, fd);
	close(fd);
	return (0);
}

int	chose_exec(t_control_exec *exes, t_instance *instance)
{
	int	ret;

	ret = 0;
	if (!exes->first)
		return (-1);
	if (exes->first->next == NULL)
		ret = execution_solo(exes->first, instance);
	else
		ret = execution_pipe(exes, instance);
	exes->iter = exes->first;
	return (ret);
}
