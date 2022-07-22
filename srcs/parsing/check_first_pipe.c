/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_first_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cben-bar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 20:16:22 by cben-bar          #+#    #+#             */
/*   Updated: 2022/06/15 16:37:10 by cben-bar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	check_first_pipe(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '|')
	{
		if (line[i] == '|')
		{
			printf("minishell: syntax error near unexpected token `|\'\n");
			return (false);
		}
		i++;
	}
	return (true);
}
