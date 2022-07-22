/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flaggeur_file_name.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cben-bar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 14:33:00 by cben-bar          #+#    #+#             */
/*   Updated: 2022/06/14 16:41:17 by cben-bar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

void	flaggeur_file_name(t_control_parse *parsing)
{
	int	i;

	i = 0;
	parsing->iter = parsing->first;
	while (parsing->iter)
	{
		if (parsing->iter->flag == REDIR_IN_FLAG
			|| parsing->iter->flag == REDIR_OUT_FLAG
			|| parsing->iter->flag == REDIR_OUT_ADD_FLAG)
			i = 1;
		else if (parsing->iter->flag == HERE_DOC_FLAG)
			i = 2;
		else if (i == 1 && parsing->iter->flag != PIPE_FLAG)
		{
			parsing->iter->flag = FILE_NAME;
			i = 0;
		}
		else if (i == 2 && parsing->iter->flag != PIPE_FLAG)
		{
			parsing->iter->flag = DELIM_NAME;
			i = 0;
		}
		parsing->iter = parsing->iter->next;
	}
}
