/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_back.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarle-m <acarle-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 14:25:37 by acarle-m          #+#    #+#             */
/*   Updated: 2022/05/09 14:26:41 by acarle-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	exec_add_back(t_control_exec *lst, t_exec *add)
{
	if (add == NULL)
		return (-1);
	if (lst->first == NULL)
		lst->first = add;
	else
	{
		lst->iter = exec_last(lst);
		add->prev = lst->iter;
		lst->iter->next = add;
	}
	lst->iter = lst->first;
	if (exec_last(lst) != add)
		return (-1);
	return (0);
}
