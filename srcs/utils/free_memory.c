#include <minishell.h>

void	cmd_free(char **cmd)
{
	size_t	i;

	i = 0;
	if (!cmd)
		return ;
	while (cmd[i])
	{
		free(cmd[i]);
		i++;
	}
	free(cmd);
}
