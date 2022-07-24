#include <minishell.h>

/*
static int	looper(char **arg)
{
	int		i;
	char	*line;

	i = 0;
	while (arg[1] && arg[1][i] != '=')
		i++;
	line = malloc(i);
	i = 0;
		while (arg[1] && arg[1][i] != '=')
		i++;
	return (i);
}

int	builtin_export(char **arg, char **envp)
{
	char	*line;
	int		i;
	size_t	size;

	i = 0;
	while(arg[j] != NULL)
	{
		line = looper(arg);
		size = ft_strlen(line);
		while (envp[i] && ft_strncmp(envp[i], line, size) != 0)
			i++;
		envp[i] = ft_strdup(arg[1]);
		free(line);
	}
	return (0);
}
*/

int	builtin_export(char **arg, char **envp)
{
	size_t	i;

	(void)arg;
	i = 0;
	if (envp == NULL)
		return (-1);
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
	return (0);
}
