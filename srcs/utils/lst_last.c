/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_last.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarle-m <acarle-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 14:29:45 by acarle-m          #+#    #+#             */
/*   Updated: 2022/07/03 17:42:42 by cben-bar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parsing/minishell.h"

t_parse	*parse_last(t_control_parse *lst)
{
	if (!lst->first)
		return (NULL);
	lst->iter = lst->first;
	while (lst->iter->next)
		lst->iter = lst->iter->next;
	return (lst->iter);
}
