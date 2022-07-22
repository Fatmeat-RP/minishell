/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_multi_node_chev.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cben-bar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 16:36:27 by cben-bar          #+#    #+#             */
/*   Updated: 2022/07/19 16:54:42 by cben-bar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_node(t_parse *node)
{
	free(node->elem);
	if (node->flag == REDIR_IN_FLAG
		|| node->flag == HERE_DOC_FLAG)
		node->elem = ft_strdup("syntax error near unexpected token `<'");
	if (node->flag == REDIR_OUT_FLAG
		|| node->flag == REDIR_OUT_ADD_FLAG)
		node->elem = ft_strdup("syntax error near unexpected token `>'");
	node->flag = PARSE_ERROR;
}

void	check_multi_node_chev_2(t_control_parse *parsing, t_control_parse *cpy)
{
	while (cpy->iter)
	{
		if (parsing->iter->flag == REDIR_IN_FLAG
			|| parsing->iter->flag == REDIR_OUT_FLAG
			|| parsing->iter->flag == HERE_DOC_FLAG
			|| parsing->iter->flag == REDIR_OUT_ADD_FLAG)
		{
			if (cpy->iter->flag == REDIR_IN_FLAG
				|| cpy->iter->flag == REDIR_OUT_FLAG
				|| cpy->iter->flag == HERE_DOC_FLAG
				|| cpy->iter->flag == REDIR_OUT_ADD_FLAG)
			{
				replace_node(parsing->iter->next);
				break ;
			}
		}
		cpy->iter = cpy->iter->next;
		parsing->iter = parsing->iter->next;
	}
}

int	check_multi_node_chev(t_control_parse *parsing)
{
	t_control_parse	*cpy;

	cpy = malloc(sizeof(t_control_parse));
	if (!cpy)
		return (false);
	parsing->iter = parsing->first;
	cpy->iter = parsing->iter->next;
	check_multi_node_chev_2(parsing, cpy);
	free(cpy);
	return (true);
}
