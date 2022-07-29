/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarle-m <acarle-m@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 01:22:11 by acarle-m          #+#    #+#             */
/*   Updated: 2022/07/28 01:22:11 by acarle-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*cmd_bad_access(char *cmd)
{
	if (access(cmd, F_OK) == -1)
	{
		write(2, "minishell: ", 11);
		write(2, cmd, ft_strlen(cmd));
		write(2, ": command not found\n", 20);
	}
	else if (access(cmd, X_OK) == -1)
	{
		write(2, "minishell: ", 11);
		write(2, cmd, ft_strlen(cmd));
		write(2, ": Permission denied\n", 20);
	}
	return (cmd);
}

char	*get_path(char *cmd, char **envp, size_t j)
{
	char	**paths;
	char	*path;
	char	*part_path;

	j = 0;
	while (envp[j] && ft_strnstr(envp[j], "PATH=", 5) == 0)
		j++;
	if (envp[j] == NULL)
		return (cmd);
	paths = exec_split(envp[j] + 5, ':');
	j = -1;
	while (paths[++j] != NULL)
	{
		part_path = ft_strjoin(paths[j], "/");
		path = ft_strfreejoin(part_path, cmd);
		if (access(path, F_OK) == 0)
		{
			cmd_free(paths);
			free(cmd);
			return (path);
		}
		free(path);
	}
	cmd_free(paths);
	return (cmd_bad_access(cmd));
}
