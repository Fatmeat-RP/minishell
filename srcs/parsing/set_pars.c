/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cben-bar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 01:40:56 by cben-bar          #+#    #+#             */
/*   Updated: 2022/07/09 01:41:00 by cben-bar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_control_parse	*set_pars(t_control_parse *pars, char **line_tab, char **env)
{
	size_t	i;
	size_t	x;

	i = 0;
	x = 0;
	pars = init_control_parse();
	while (line_tab[i])
	{
		parse_add_back(pars, init_parse(ft_strdup(line_tab[i]), 0));
		i++;
	}
	while (line_tab[x])
		x++;
	tab_cleaner(line_tab);
	pars = parse(pars, x, env);
	return (pars);
}
