/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_last_chev.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cben-bar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 17:01:43 by cben-bar          #+#    #+#             */
/*   Updated: 2022/06/08 17:14:38 by cben-bar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

t_bool	check_last_chev(char *line)
{
	size_t	len;

	len = (ft_strlen(line) - 1);
	while (line[len] == ' ')
		len--;
	if (line[len] != '<' && line[len] != '>')
		return (true);
	if (line[len] == '<' || line[len] == '>')
	{
		printf("syntax error near unexpected token `newline'\n");
		return (false);
	}
	return (true);
}
