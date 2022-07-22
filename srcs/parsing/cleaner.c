/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cben-bar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 16:26:54 by cben-bar          #+#    #+#             */
/*   Updated: 2022/07/08 22:05:24 by cben-bar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleaner(t_control_parse *parsing)
{
	t_parse	*ptr;

	while (parsing->first)
	{
		ptr = parsing->first;
		free(ptr->elem);
		parsing->first = parsing->first->next;
		free(ptr);
	}
	free(parsing);
}

void	tab_cleaner(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	var_clear(t_var *var)
{
	t_var	*tmp;

	if (var)
	{
		while (var)
		{
			tmp = var;
			free(tmp->varname);
			free(tmp->value);
			var = var->next;
			free(tmp);
			tmp = NULL;
		}
		tmp = NULL;
	}
}
