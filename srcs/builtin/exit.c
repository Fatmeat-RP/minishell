/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cben-bar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 14:06:32 by cben-bar          #+#    #+#             */
/*   Updated: 2022/07/02 14:06:35 by cben-bar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtin.h>

int	main(int ac, char **av)
{
	pid_t pid;

	pid = getppid();
	if (ac == 2)
	{
		kill(pid, SIGKILL);
		return (ft_atoi(av[1]));
	}
	kill(pid, SIGKILL);
	return (0);
}
