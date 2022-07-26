#include <minishell.h>

void	exec_cleaner(t_control_exec *exec)
{
	int i;

	if (!exec)
		return ;
	exec->iter = exec->first;
	while (exec->first != NULL)
	{
		i = 0;
		exec->iter = exec->first->next;
		free(exec->first->limiter);
		while(exec->first->cmd[i] != NULL)
			free(exec->first->cmd[i++]);
		i = 0;
		while(exec->first->out[i] != NULL)
			free(exec->first->out[i++]);
		i = 0;
		while(exec->first->in[i] != NULL)
			free(exec->first->in[i++]);
		free(exec->first);
		exec->first = exec->iter;
	}
	free(exec);
}

int	control_parse(t_control_parse *truct)
{
	if (!truct)
		return (-1);
	if (!truct->first)
	{
		free(truct);
		return (-1);
	}
	return (0);
}

int	test_free(t_control_exec *exec, int nb_pipe)
{
	if (!exec)
		return (-1);
	exec->first = init_exe();
	exec->iter = exec->first;
	if (!exec->first)
	{
		free (exec);
		return (-1);
	}
	while (nb_pipe != 0)
	{
		if (exec_add_back(exec, init_exe()) == -1)
		{
			exec_cleaner(exec);
			return (-1);
		}
		nb_pipe--;
	}
	exec->iter = exec->first;
	return (0);
}

int	free_instance(t_instance *instance, int i)
{
	int	j;

	j = 0;
	while (instance->envp[j])
		free(instance->envp[j++]);
	free(instance->envp);
	while (instance->builtin->first->next != NULL)
	{
		instance->builtin->iter = instance->builtin->first->next;
		if (i == 3)
			free(instance->builtin->first->name);
		free(instance->builtin->first);
		instance->builtin->first = instance->builtin->iter;
	}
	free(instance->builtin->first);
	free(instance->builtin);
	free(instance);
	return (i);
}

int	free_exe(t_exec *exec)
{
	int	i;

	i = 0;
	free(exec->limiter);
	while(exec->cmd[i] != NULL)
		free(exec->cmd[i++]);
	i = 0;
	while(exec->out[i] != NULL)
		free(exec->out[i++]);
	i = 0;
	while(exec->in[i] != NULL)
		free(exec->in[i++]);
	free(exec);
	return (g_status);
}
