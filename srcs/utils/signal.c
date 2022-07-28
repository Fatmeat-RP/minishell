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
	write(2, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	if (g_status <= 255)
		rl_redisplay();
}

void	sig_int_child_handler(int signum)
{
	(void)signum;
	exit(0);
	rl_redisplay();
}

void	sig_quit_handler(int signum)
{
	char	*tmp;

	write(2, "\nQuit: %i\n", signum);
	tmp = ft_itoa(signum);
	if (!tmp)
		write(2, "0\n", 2);
	else
	{
		write(2, tmp, ft_strlen(tmp));
		write(2, "\n", 1);
	}
	free(tmp);
}
