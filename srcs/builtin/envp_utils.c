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

char	**add_envp(char **envp, char *new)
{
	char	**new_envp;
	int		i;

	i = 0;
	new_envp = malloc(sizeof(char *) * (ft_size(envp) + 2));
	if (new_envp == NULL)
		return (envp);
	while (envp[i] != NULL)
	{
		new_envp[i] = ft_strdup(envp[i]);
		free(envp[i]);
		i++;
	}
	free(envp);
	new_envp[i] = ft_strdup(new);
	new_envp[i + 1] = NULL;
	return (new_envp);
}

char	*get_varname(char *new)
{
	int		i;
	char	*ret;

	i = 0;
	while (new[i] != '=')
	{
		i++;
		if (!new[i])
			return (NULL);
	}
	ret = (char *)malloc(i + 2);
	ret[i + 1] = 0;
	while (i >= 0)
	{
		ret[i] = new[i];
		i--;
	}
	return (ret);
}

char	**del_envp(char **envp, int index)
{
	char	**new_envp;
	int		i;
	int		k;

	i = 0;
	k = 0;
	printf("%i\n", index);
	new_envp = malloc(sizeof(char *) * ft_size(envp));
	if (new_envp == NULL)
		return (envp);
	while (envp[i] != NULL)
	{
		if (i != index)
		{
			new_envp[k] = ft_strdup(envp[i]);
			k++;
		}
		free(envp[i]);
		i++;
	}
	free(envp);
	new_envp[k] = NULL;
	return (new_envp);
}
