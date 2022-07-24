/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_last_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cben-bar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 19:34:59 by cben-bar          #+#    #+#             */
/*   Updated: 2022/06/15 16:37:45 by cben-bar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_bool	check_last_pipe(char *line)
{
	size_t	len;

	len = (ft_strlen(line) - 1);
	while (line[len] == ' ')
		len--;
	if (line[len] != '|')
		return (true);
	if (line[len] == '|')
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		return (false);
	}
	return (true);
}
