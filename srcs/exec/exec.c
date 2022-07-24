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

static int	execution_solo(t_control_exec *exes, t_instance *instance)
{
	pid_t	pid;
	int		pipefd[2];
 
	if (pipe(pipefd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (exes->first->is_here_doc == true)
		here_doc(exes->first);
	if (pid == 0)
		exec_one_cmd(exes->first, instance->envp);
	else
		waitpid(pid, &g_status, 0);
	return (g_status);
}

static int	execution_pipe(t_control_exec *exes, t_instance *instance)
{
	while (exes->iter != NULL)
	{
		forklift(exes->iter, instance->envp);
		exes->iter = exes->iter->next;
	}
	dup2(0, STDIN_FILENO);
	return (0);
}

int	chose_exec(t_control_exec *exes, t_instance *instance)
{
	if (!exes->first)
		return (-1);
	if (exes->first->next == NULL)
		return (execution_solo(exes, instance));
	else
		return (execution_pipe(exes, instance));
	return (0);
}

void	exec_one_cmd(t_exec *cmd, char **envp)
{
	signal(SIGINT, sig_int_child_handler);
	signal(SIGQUIT, sig_quit_handler);
	redir_in_error(cmd);
	redirect_out(cmd);
	g_status = execve(cmd->cmd[0], cmd->cmd, envp);
	exit(g_status);
}
