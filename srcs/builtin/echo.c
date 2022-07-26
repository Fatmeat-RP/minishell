/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarle-m <acarle-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 19:34:51 by cben-bar          #+#    #+#             */
/*   Updated: 2022/07/24 04:17:32 by acarle-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	looper(char **arg, int i)
{
	if (arg[i] == NULL)
		return ;
	while (arg[i])
	{
		write(1, arg[i], ft_strlen(arg[i]));
		i++;
		if (arg[i])
			write(1, " ", 2);
	}
	return ;
}

int	builtin_echo(char **arg, t_instance *instance)
{
	int	i;

	(void)instance;
	i = 1;
	if (arg[1] && ft_strncmp(arg[1], "-n", 3) == 0)
		looper(arg, i);
	else
	{
		looper(arg, ++i);
		write(1, "\n", 3);
	}
	return (0);
}