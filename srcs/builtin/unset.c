/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarle-m <acarle-m@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 01:23:31 by acarle-m          #+#    #+#             */
/*   Updated: 2022/07/28 01:23:31 by acarle-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	**loop(char **envp, char *arg)
{
	int	j;

	j = 0;
	while (envp[j])
	{
		if (ft_strncmp(envp[j], arg, ft_strlen(arg)) == 0)
			envp = del_envp(envp, j);
		j++;
	}
	return (envp);
}

int	builtin_unset(char **arg, t_instance *instance)
{
	int	i;

	i = 1;
	while (arg[i] != NULL)
	{
		instance->envp = loop(instance->envp, arg[i]);
		i++;
	}
	return (0);
}
