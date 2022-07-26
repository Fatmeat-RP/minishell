/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supp_empty_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cben-bar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 15:02:48 by cben-bar          #+#    #+#             */
/*   Updated: 2022/07/19 18:28:30 by cben-bar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_bool	empty_elem(char *s)
{
	if (!s)
		return (true);
	if (ft_strlen(s) == 0)
		return (true);
	return (false);
}

void	supp_node(t_control_parse *parsing, t_parse *tmp)
{
	while (tmp->next != parsing->iter)
		tmp = tmp->next;
	tmp->next = parsing->iter->next;
	free(parsing->iter->elem);
	free(parsing->iter);
	parsing->iter = tmp;
}

int	supp_first(t_control_parse *parsing, t_parse *tmp)
{
	parsing->first = parsing->first->next;
	parsing->iter = parsing->first;
	free(tmp->elem);
	free(tmp);
	tmp = NULL;
	return (1);
}

int	supp_empty_node(t_control_parse *parsing)
{
	size_t	i;
	t_parse	*tmp;
	int		ori_flag;

	i = 1;
	ori_flag = 0;
	parsing->iter = parsing->first;
	while (parsing->iter)
	{
		tmp = parsing->first;
		if (empty_elem(parsing->first->elem))
			ori_flag = supp_first(parsing, tmp);
		else if (empty_elem(parsing->iter->elem))
			supp_node(parsing, tmp);
		else
			parsing->iter = parsing->iter->next;
		i++;
	}
	return (ori_flag);
}
