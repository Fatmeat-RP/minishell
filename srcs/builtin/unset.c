#include <minishell.h>

int	builtin_unset(char **arg, t_instance *instance)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (arg[i] != NULL)
	{
		while (instance->envp[j])
		{
			if (ft_strncmp(instance->envp[j], arg[i], ft_strlen(arg[i]) == 0))
				instance->envp = del_envp(instance->envp, j);
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}
