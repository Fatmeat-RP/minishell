/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cben-bar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 16:53:52 by cben-bar          #+#    #+#             */
/*   Updated: 2022/06/15 17:00:16 by cben-bar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_bool	printer_error(t_control_parse *parsing)
{
	parsing->iter = parsing->first;
	while (parsing->iter)
	{
		if (parsing->iter->flag == PARSE_ERROR)
		{
			write(2, "minishell: %s\n", 15);
			write(2, parsing->iter->elem, ft_strlen(parsing->iter->elem));
			return (false);
		}
		parsing->iter = parsing->iter->next;
	}
	return (true);
}
