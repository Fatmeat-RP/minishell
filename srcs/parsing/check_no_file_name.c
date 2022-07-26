/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_no_file_name.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cben-bar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 14:55:03 by cben-bar          #+#    #+#             */
/*   Updated: 2022/07/19 11:30:23 by cben-bar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	replace_node2(t_parse *node)
{
	free(node->elem);
	node->elem = ft_strdup("syntax error near unexpected token `|'");
	node->flag = PARSE_ERROR;
}

int	check_no_file_name(t_control_parse *parsing)
{
	t_control_parse	*cpy;

	cpy = malloc(sizeof(t_control_parse));
	if (!cpy)
		return (false);
	parsing->iter = parsing->first;
	cpy->iter = parsing->iter->next;
	while (cpy->iter)
	{
		if (parsing->iter->flag == REDIR_IN_FLAG
			|| parsing->iter->flag == REDIR_OUT_FLAG
			|| parsing->iter->flag == HERE_DOC_FLAG
			|| parsing->iter->flag == REDIR_OUT_ADD_FLAG)
		{
			if (cpy->iter->flag == PIPE_FLAG)
			{
				replace_node2(parsing->iter->next);
				break ;
			}
		}
			cpy->iter = cpy->iter->next;
			parsing->iter = parsing->iter->next;
	}
	free(cpy);
	return (true);
}
