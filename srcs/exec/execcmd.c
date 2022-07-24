#include <minishell.h>

int	execuction(t_exec *cmd, t_instance *instance)
{
	if (cmd->is_builtin == true)
	{
		while(instance->builtin->iter->next
			&& ft_strcmp(cmd->cmd[0], instance->builtin->iter->name) != 0)
			instance->builtin->iter = instance->builtin->iter->next;
		g_status = (*instance->builtin->iter->fun)(cmd->cmd, instance->envp);
		exit (g_status);
	}
	else
	{
		g_status = execve(cmd->cmd[0], cmd->cmd, instance->envp);
		exit (g_status);
	}
	exit (EXIT_FAILURE);
}

int	forklift(t_exec *cmd, t_instance *instance)
{
	int	pid;
	int	pipefd[2];

	if (pipe(pipefd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (cmd->is_here_doc == true)
		here_doc(cmd);
	if (pid == 0)
	{
		redir_in_error(cmd);
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		redirect_out(cmd);
		execuction(cmd, instance);
	}
	else
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		waitpid(pid, &g_status, 0);
	}	
	return (pipefd[0]);
}
