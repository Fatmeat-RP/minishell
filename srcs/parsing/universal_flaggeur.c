/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   universal_flaggeur.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cben-bar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 16:44:15 by cben-bar          #+#    #+#             */
/*   Updated: 2022/06/14 11:21:10 by cben-bar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	universal_flaggeur(t_control_parse *parsing)
{
	int	tem;

	tem = 0;
	parsing->iter = parsing->first;
	while (parsing->iter)
	{
		if (parsing->iter->flag == ARGS_FLAG && tem == 0)
		{
			parsing->iter->flag = CMD_FLAG;
			tem = 1;
		}
		if (parsing->iter->flag == PIPE_FLAG)
			tem = 0;
		parsing->iter = parsing->iter->next;
	}
}
