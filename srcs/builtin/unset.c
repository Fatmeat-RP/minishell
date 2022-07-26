#include <minishell.h>

static int	loop(t_instance *instance, char *arg)
{
	int	j;

	j = 0;
	while (instance->envp[j])
	{
		if (ft_strncmp(instance->envp[j], arg, ft_strlen(arg) == 0))
			instance->envp = del_envp(instance->envp, j);
		j++;
	}
	return (0);
}

int	builtin_unset(char **arg, t_instance *instance)
{
	int	i;

	i = 1;
	while (arg[i] != NULL)
	{
		loop(instance, arg[i]);
		i++;
	}
	return (0);
}
