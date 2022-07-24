/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_back.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarle-m <acarle-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 14:25:37 by acarle-m          #+#    #+#             */
/*   Updated: 2022/07/03 17:42:08 by cben-bar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	parse_add_back(t_control_parse *lst, t_parse *add)
{
	if (lst->first == NULL)
		lst->first = add;
	else
	{
		lst->iter = parse_last(lst);
		lst->iter->next = add;
		lst->iter = lst->first;
	}
	lst->size++;
}

void	parse_add_just_back(t_control_parse *lst, t_parse *add)
{
	t_parse	*dec;

	dec = lst->iter->next;
	if (lst->first == NULL)
		lst->first = add;
	else
	{
		lst->iter->next = add;
		add->next = dec;
	}
	lst->size++;
}

t_var	*ft_lstlast(t_var *lst)
{
	t_var	*tmp;

	tmp = lst;
	if (!lst)
		return (NULL);
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	return (tmp);
}

void	ft_lstadd_back(t_var **alst, t_var *new)
{
	t_var	*tmp;

	if (!(alst) || !new)
		return ;
	tmp = ft_lstlast(*alst);
	if (!tmp)
		*alst = new;
	else
		tmp->next = new;
}

void	ft_lstadd_just_back(t_var *lst, t_var *new)
{
	t_var	*tmp;

	if (!(lst) || !new)
		return ;
	tmp = lst->next;
	if (!tmp)
		lst = new;
	else
	{
		ft_lstadd_back(&lst, new);
		new->next = tmp;
	}
}
