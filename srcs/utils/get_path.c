#include <minishell.h>

/* static int	path_bad_access(char *cmd)
{
	int	i;

	i = 0;
	if (access(cmd, F_OK) == -1)
	{
		write(2, cmd, ft_strlen(cmd));
		write(2, ": command not found\n", 20);
		i = -1;
	}
	else if (access(cmd, X_OK) == -1)
	{
		write(2, cmd, ft_strlen(cmd));
		write(2, ": Permission denied\n", 20);
		i = -1;
	}
	return (i);
} */

/* static char	*cmd_bad_access(char *cmd)
{
	if (access(cmd, F_OK) == -1)
	{
		write(2, cmd, ft_strlen(cmd));
		write(2, ": command not found\n", 20);
	}
	else if (access(cmd, X_OK) == -1)
	{
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

	while (envp[j] && ft_strncmp(envp[j], "PATH=", 6) != 0)
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
} */

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
	return (cmd);
}
