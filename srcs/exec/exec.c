/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarle-m <acarle-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 20:21:49 by acarle-m          #+#    #+#             */
/*   Updated: 2022/07/24 02:36:00 by acarle-m         ###   ########.fr       */
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
	while(instance->builtin->iter->next
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

static int	exec_one_cmd(t_exec *cmd, t_instance *instance)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		if (cmd->is_here_doc == true)
			here_doc(cmd, instance);
		signal(SIGINT, sig_int_child_handler);
		signal(SIGQUIT, sig_quit_handler);
		redir_in_error(cmd);
		redirect_out(cmd);
		pid = execve(cmd->cmd[0], cmd->cmd, instance->envp);
		free_instance(instance, 0);
		free_exe(cmd);
		exit(pid);
	}
	g_status = pid;
	waitpid(pid, &g_status, 0);
	return (g_status);
}

static int	execution_solo(t_exec *cmd, t_instance *instance)
{
	if (cmd->is_builtin == true)
		return (exec_one_builtin(cmd, instance));
	else
		return (exec_one_cmd(cmd, instance));
}

static int	execution_pipe(t_control_exec *exes, t_instance *instance)
{
	while (exes->iter->next != NULL)
	{
		forklift(exes->iter, instance);
		exes->iter = exes->iter->next;
	}
	exec_one_cmd(exes->iter, instance);
	return (0);
}

int	chose_exec(t_control_exec *exes, t_instance *instance)
{
	int ret;
	int	fd[2];

	fd[0] = dup(STDIN_FILENO);
	fd[1] = dup(STDOUT_FILENO);
	ret = 0;
	if (!exes->first)
		return (-1);
	if (exes->first->next == NULL)
		ret = execution_solo(exes->first, instance);
	else
		ret = execution_pipe(exes, instance);
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	exes->iter = exes->first;
	return (ret);
}

