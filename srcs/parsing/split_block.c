/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_block.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cben-bar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 13:55:51 by cben-bar          #+#    #+#             */
/*   Updated: 2022/07/19 16:13:22 by cben-bar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_control_parse	*split_block_2(t_control_parse *new_lst, char **tab)
{
	new_lst->iter = init_parse(ft_strdup(tab[0]), 0);
	new_lst->iter->next = 0;
	tab_cleaner(tab);
	return (new_lst);
}

t_control_parse	*split_block(char *elem, int x)
{
	char			**tab;
	size_t			i;
	t_control_parse	*new_lst;
	size_t			j;
	int				q;

	i = 0;
	j = 0;
	q = 0;
	new_lst = init_control_parse();
	tab = ft_split_it(elem, ' ', j, q);
	while (tab[i])
		i++;
	if (i == 1)
		return (split_block_2(new_lst, tab));
	i = 0;
	while (tab[i])
	{
		parse_add_back(new_lst, init_parse(ft_strdup(tab[i]), 0));
		i++;
	}
	if (x == 1)
		parse_add_back(new_lst, init_parse(ft_strdup("|"), 7));
	tab_cleaner(tab);
	return (new_lst);
}

static void	hellothenorme(t_control_parse *parsing, t_control_parse *rep, int i)
{
	t_control_parse	*new;

	new = split_block(parsing->iter->elem, (parsing->iter->next != 0));
	if (i == 0)
		rep->first = new->iter;
	if (i > 0)
		rep->iter->next = new->iter;
	rep->iter = new->iter;
	while (rep->iter->next)
		rep->iter = rep->iter->next;
	free(new);
}

void	splitter(t_control_parse *parsing, t_control_parse *rep)
{
	int	i;

	i = 0;
	parsing->iter = parsing->first;
	while (parsing->iter)
	{
		if (parsing->iter->flag != 7)
			hellothenorme(parsing, rep, i);
		else if (parsing->iter->flag == 7)
		{
			parse_add_just_back(rep, init_parse(ft_strdup("|"), 7));
			rep->iter = rep->iter->next;
		}
		parsing->iter = parsing->iter->next;
		i++;
	}
}
