/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarle-m <acarle-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 14:06:32 by cben-bar          #+#    #+#             */
/*   Updated: 2022/07/24 02:40:45 by acarle-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	exit_builtin(char **arg, t_instance *instance)
{
	(void)arg;
	(void)instance;
	write(2, "exit\n", 5);\
	free_instance(instance, 0);
	exit (0);
	return (0);
}
