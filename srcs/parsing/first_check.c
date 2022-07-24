/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cben-bar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 14:00:39 by cben-bar          #+#    #+#             */
/*   Updated: 2022/07/07 19:17:42 by cben-bar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_bool	first_check(char *line)
{
	if (!check_empty_line(line))
		return (false);
	if (!check_quote(line))
		return (false);
	if (!check_first_pipe(line))
		return (false);
	if (!check_last_pipe(line))
		return (false);
	if (!check_last_chev(line))
		return (false);
	if (!check_consec_pipe(line))
		return (false);
	return (true);
}
