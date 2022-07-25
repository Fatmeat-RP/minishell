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
}*/

int	builtin_export(char **arg, char **envp)
{
	(void)arg;
	(void)envp;
/*	char	*line;
	int		i;
	size_t	size;
	int		j;

	i = 0;
	j = 0;
	while(arg[j] != NULL)
	{
		line = looper(arg);
		size = ft_strlen(line);
		while (envp[i] && ft_strncmp(envp[i], line, size) != 0)
			i++;
		envp[i] = ft_strdup(arg[1]);
		free(line);
		j++;
	}*/
	return (0);
}
