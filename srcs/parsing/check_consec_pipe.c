/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_consec_pipe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cben-bar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 12:13:02 by cben-bar          #+#    #+#             */
/*   Updated: 2022/06/15 16:38:10 by cben-bar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_bool	check_consec_pipe(char *line)
{
	size_t	i;
	size_t	p;
	int		q;

	i = 0;
	q = 0;
	p = 0;
	while (line[i])
	{
		q = tote(line[i], q);
		if (q == 0)
			while (line[i] == ' ')
				i++;
		if (line[i] == '|' && q == 0)
			p++;
		else
			p = 0;
		if (p == 2 && q == 0)
		{
			printf("minishell: syntax error near unexpected token `|'\n");
			return (false);
		}
		i++;
	}
	return (true);
}
