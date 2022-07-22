/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cben-bar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 16:09:27 by cben-bar          #+#    #+#             */
/*   Updated: 2022/07/09 01:40:15 by cben-bar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_control_parse	*parsing(char *line, char **envp)
{
	t_control_parse	*parsing;
	char			**line_tab;
	size_t			i;
	int				q;

	parsing = NULL;
	i = 0;
	q = 0;
	if (first_check(line))
	{
		line_tab = ft_split_it(line, '|', i, q);
		parsing = set_pars(parsing, line_tab, envp);
		if (!printer_error(parsing))
		{
			cleaner(parsing);
			return (NULL);
		}
	}
	return (parsing);
}
