#include <minishell.h>

int	builtin_cd(char **arg, t_instance *instance)
{
	(void)instance;
	//set_oldpwd
	if (chdir(arg[1]) == -1)
	{
		write(1, "minishell: ", 12);
		write(1, arg[0], ft_strlen(arg[0]));
		write(1, arg[1], ft_strlen(arg[1]));
		write(1, ": No such file or directory\n", 29);
		return (-1);
	}
	//export_newpwd
	return (0);
}
