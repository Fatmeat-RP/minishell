/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_empty_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cben-bar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 18:36:44 by cben-bar          #+#    #+#             */
/*   Updated: 2022/07/08 18:22:16 by cben-bar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_bool	check_empty_line(char *line)
{
	size_t	i;

	i = 0;
	if (!ft_strlen(line))
		return (false);
	else
	{
		while (line[i] == ' ')
			i++;
		if (!line[i])
			return (false);
	}
	return (true);
}
