/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarle-m <acarle-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 10:55:54 by acarle-m          #+#    #+#             */
/*   Updated: 2022/04/27 12:32:04 by acarle-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

size_t	ft_size(char **array)
{
	size_t	i;

	i = 0;
	if (!array)
		return (i);
	while (array[i] != NULL)
		i++;
	return (i);
}

int	pipe_counter(t_control_parse *parse)
{
	int	i;

	i = 0;
	while (parse->iter)
	{
		if (parse->iter->flag == PIPE_FLAG)
			i++;
		parse->iter = parse->iter->next;
	}
	parse->iter = parse->first;
	return (i);
}

int	line_counter(char **aos)
{
	int	i;

	i = 0;
 	if (!aos)
		return (0);
	if (!aos[i])
		return (0);
	while (aos[i + 1] != NULL)
		i++;
	return (i);
}

static char	*cmd_bad_access(char *cmd)
{
	if (access(cmd, F_OK | X_OK) == -1)
	{
		write(2, cmd, ft_strlen(cmd));
		write(2, ": command not found", 20);
	}
	return (cmd);
}

char	*get_path(char *cmd, char **envp, size_t j)
{
	char	**paths;
	char	*path;
	char	*part_path;

	while (envp[j] && ft_strncmp(envp[j], "PATH=", 6) == 0)
		j++;
	if (envp[j] == NULL)
		return (cmd);
	paths = exec_split(envp[j] + 5, ':');
	j = -1;
	while (paths[++j] != NULL)
	{
		part_path = ft_strjoin(paths[j], "/");
		path = ft_strfreejoin(part_path, cmd);
		if (access(path, F_OK | X_OK) == 0)
		{
			cmd_free(paths);
			return (path);
		}
		free(path);
	}
	cmd_free(paths);
	return (cmd_bad_access(cmd));
}
