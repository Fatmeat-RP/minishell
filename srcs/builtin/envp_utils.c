/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarle-m <acarle-m@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 01:23:39 by acarle-m          #+#    #+#             */
/*   Updated: 2022/07/28 01:23:39 by acarle-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**init_envp(char **envp)
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

void	addshlv(t_instance *instance)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = malloc(sizeof(char *) * 3);
	while (i < 3)
		tmp[i++] = NULL;
	i = 0;
	while (instance->envp[i] && ft_strnstr(instance->envp[i], "SHLVL=", 6) == 0)
		i++;
	if (instance->envp[i] == NULL)
		tmp[0] = ft_strdup("SHLVL=1");
	else
	{
		i = ft_atoi(instance->envp[i] + 6);
		tmp[0] = ft_itoa(++i);
		tmp[1] = ft_strjoin("SHLVL=", tmp[0]);
	}
	builtin_export(tmp, instance);
	i = 0;
	while (tmp[i] != NULL)
		free(tmp[i++]);
	free(tmp);
	return ;
}
