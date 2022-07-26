/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_flaggeur.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cben-bar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 00:11:53 by cben-bar          #+#    #+#             */
/*   Updated: 2022/07/19 16:21:37 by cben-bar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	re_flaggeur_2(t_control_parse *parsing, int tem_flag)
{
	if (parsing->iter->flag == CMD_FLAG)
		tem_flag = 1;
	else if (parsing->iter->flag == BUILTIN_FLAG)
		tem_flag = 1;
	parsing->iter = parsing->iter->next;
	return (tem_flag);
}

void	re_flaggeur(t_control_parse *parsing)
{
	int				tem_flag;
	t_parse			*tmp;

	parsing->iter = parsing->first;
	while (parsing->iter)
	{
		tem_flag = 0;
		tmp = parsing->iter;
		while (parsing->iter && parsing->iter->flag != PIPE_FLAG)
			tem_flag = re_flaggeur_2(parsing, tem_flag);
		if (tem_flag == 0)
		{
			while (tmp && tmp != parsing->iter)
			{
				if (tmp->flag == ARGS_FLAG)
				{
					tmp->flag = ident_cmd(tmp->elem);
					break ;
				}
				tmp = tmp->next;
			}
		}
		if (parsing->iter)
			parsing->iter = parsing->iter->next;
	}
}
