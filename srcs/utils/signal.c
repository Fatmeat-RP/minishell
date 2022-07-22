/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarle-m <acarle-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 20:17:50 by acarle-m          #+#    #+#             */
/*   Updated: 2022/07/18 02:48:20 by acarle-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	sig_int_handler(int signum)
{
	(void)signum;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	sig_int_child_handler(int signum)
{
	kill(0, signum);
	rl_redisplay();
}

void	sig_quit_handler(int signum)
{
	kill(0, signum);
	printf("\nQuit: %i\n", signum);
}
