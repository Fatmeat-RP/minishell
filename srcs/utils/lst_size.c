/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_size.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarle-m <acarle-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 14:32:56 by acarle-m          #+#    #+#             */
/*   Updated: 2022/05/09 14:19:32 by acarle-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

size_t	parse_size(t_control_parse *lst)
{
	size_t	i;

	i = 1;
	printf("1");
	sleep(1);
	if (!lst->iter)
		return (0);
	while (lst->iter->next != NULL)
	{
		lst->iter = lst->iter->next;
		i++;
	}
	lst->iter = lst->first;
	return (i);
}

size_t	exec_size(t_control_exec *lst)
{
	size_t	i;

	i = 1;
	if (!lst->iter)
		return (0);
	while (lst->iter->next)
	{
		lst->iter = lst->iter->next;
		i++;
	}
	return (i);
}
