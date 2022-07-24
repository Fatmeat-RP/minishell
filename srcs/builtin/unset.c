#include <minishell.h>

int	builtin_unset(char **arg, char **envp)
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
