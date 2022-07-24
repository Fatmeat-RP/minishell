#include <minishell.h>

static int	looper(char **arg)
{
	int	i;

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

	i = 0;
	line = malloc(looper(arg[1]));
	while ()
	return (0);
}