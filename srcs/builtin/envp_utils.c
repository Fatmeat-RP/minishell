#include <minishell.h>

char **init_envp(char **envp)
{
	char	**env_ret;
	size_t	size;
	int		i;

	size = ft_size(envp);
	env_ret = malloc(sizeof(char *) * (size + 1));
	i = 0;
	while (envp[i])
	{
		env_ret[i] = ft_strdup(envp[i]);
		i++;
	}
	env_ret[i] = NULL;
	return (env_ret);
}

//char **add_envp(char **envp)