#include <minishell.h>

int	redir_in_error(t_exec *cmd)
{
	if (redirect_in(cmd) == -1 && cmd->in[0] != NULL)
	{
		write(2, "minishell: ", 12);
		write(2, cmd->in[line_counter(cmd->in)],
			ft_strlen(cmd->in[line_counter(cmd->in)]));
		write(2, ": No such file or directory\n", 29);
		g_status = 1;
		exit (g_status);
	}
}