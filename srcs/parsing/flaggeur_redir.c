/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flaggeur_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cben-bar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 19:21:12 by cben-bar          #+#    #+#             */
/*   Updated: 2022/06/24 13:16:23 by cben-bar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	flaggeur_redir(t_control_parse *parsing)
{
	char	*s;

	parsing->iter = parsing->first;
	while (parsing->iter)
	{
		s = parsing->iter->elem;
		if (parsing->iter->flag != PIPE_FLAG)
		{
			if (ft_strncmp(s, "<<", 2) == 0)
				parsing->iter->flag = HERE_DOC_FLAG;
			else if (ft_strncmp(s, "<", 1) == 0)
				parsing->iter->flag = REDIR_IN_FLAG;
			else if (ft_strncmp(s, ">>", 2) == 0)
				parsing->iter->flag = REDIR_OUT_ADD_FLAG;
			else if (ft_strncmp(s, ">", 1) == 0)
				parsing->iter->flag = REDIR_OUT_FLAG;
			else
				parsing->iter->flag = ARGS_FLAG;
		}
		parsing->iter = parsing->iter->next;
	}
}
