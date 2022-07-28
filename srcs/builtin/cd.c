/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarle-m <acarle-m@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 01:23:44 by acarle-m          #+#    #+#             */
/*   Updated: 2022/07/28 01:23:44 by acarle-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	**ret_pwd_arg(char **arg)
{
	if (arg)
	{
		free(arg[0]);
		free(arg[1]);
		free(arg);
	}
	arg = malloc(sizeof(char *) * 3);
	if (!arg)
		return (NULL);
	arg[0] = ft_strdup("export");
	arg[1] = ft_strjoin("PWD=", getcwd(NULL, 0));
	arg[2] = NULL;
	return (arg);
}

static char	**ret_old_pwd(void)
{
	char	*tmp;
	char	**arg;

	arg = malloc(sizeof(char *) * 3);
	arg[0] = ft_strdup("export");
	tmp = ft_strjoin("OLD_PWD=", getcwd(NULL, 0));
	arg[1] = ft_strdup(tmp);
	free(tmp);
	arg[2] = NULL;
	return (arg);
}

int	builtin_cd(char **arg, t_instance *instance)
{
	char	**path;

	path = ret_old_pwd();
	builtin_export(path, instance);
	if (chdir(arg[1]) == -1)
	{
		write(1, "minishell: ", 12);
		write(1, arg[0], ft_strlen(arg[0]));
		write(1, arg[1], ft_strlen(arg[1]));
		write(1, ": No such file or directory\n", 29);
		return (-1);
	}
	path = ret_pwd_arg(path);
	builtin_export(path, instance);
	free(path[0]);
	free(path[1]);
	free(path);
	return (0);
}
