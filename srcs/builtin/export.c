/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarle-m <acarle-m@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 01:23:35 by acarle-m          #+#    #+#             */
/*   Updated: 2022/07/28 01:23:35 by acarle-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	error_export(char *arg)
{
	write(2, "minishell: ", 12);
	write(2, "export: '", 9);
	write(2, arg, ft_strlen(arg));
	write(2, "': not a valid identifier\n", 27);
	return (-1);
}

static int	printf_env(char **arg, t_instance *instance)
{
	size_t	i;

	(void)arg;
	i = 0;
	if (instance->envp == NULL)
		return (-1);
	while (instance->envp[i])
	{
		write(1, "declare -x ", 11);
		write(1, instance->envp[i], ft_strlen(instance->envp[i]));
		write(1, "\n", 1);
		i++;
	}
	return (0);
}

static int	is_envp(char *arg, char **envp)
{
	int		i;
	char	*varname;
	size_t	len;

	i = 0;
	if (arg[0] == '=')
		return (-3);
	varname = get_varname(arg);
	if (varname == NULL)
		return (-1);
	len = ft_strlen(varname);
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], varname, len) == 0)
		{
			free(varname);
			return (i);
		}
		i++;
	}
	free(varname);
	return (-2);
}

int	builtin_export(char **arg, t_instance *instance)
{
	int		i;
	int		j;

	i = 1;
	if (arg[i] == NULL)
		return (printf_env(arg, instance));
	while (arg[i] != NULL)
	{
		j = is_envp(arg[i], instance->envp);
		if (j == -2)
			instance->envp = add_envp(instance->envp, arg[i]);
		else if (j == -3)
			return (error_export(arg[i]));
		else
		{
			free(instance->envp[j]);
			instance->envp[j] = ft_strdup(arg[i]);
		}
		i++;
	}
	return (0);
}
