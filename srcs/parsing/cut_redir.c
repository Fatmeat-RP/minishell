/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cben-bar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 15:43:45 by cben-bar          #+#    #+#             */
/*   Updated: 2022/07/19 11:15:51 by cben-bar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_parse	*cutter(t_parse *node, size_t i)
{
	char	*s;
	size_t	c;
	t_parse	*new;

	s = malloc(sizeof(char) * i);
	if (!s)
		return (NULL);
	c = 0;
	while (c < i)
	{
		s[c] = node->elem[c];
		c++;
	}
	s[c] = '\0';
	new = init_parse(ft_strdup(&node->elem[i]), ARGS_FLAG);
	free(node->elem);
	node->elem = s;
	return (new);
}

size_t	need_cut(char *elem)
{
	size_t	i;
	int		q;

	i = 0;
	q = 0;
	if (elem[i] == '<' || elem[i] == '>')
	{
		while (elem[i] == '<' || elem[i] == '>')
			i++;
		if (elem[i])
			return (i);
	}
	else
	{
		while (elem[i])
		{
			q = tote(elem[i], q);
			if (!q && (elem[i] == '<' || elem[i] == '>'))
				return (i);
			i++;
		}
	}
	return (false);
}	

void	cut_redir(t_control_parse *parsing)
{
	size_t	i;

	parsing->iter = parsing->first;
	while (parsing->iter)
	{
		i = need_cut(parsing->iter->elem);
		if (i)
			parse_add_just_back(parsing, cutter(parsing->iter, i));
		parsing->iter = parsing->iter->next;
	}
}
