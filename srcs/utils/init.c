/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarle-m <acarle-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 14:18:59 by acarle-m          #+#    #+#             */
/*   Updated: 2022/07/06 17:31:15 by cben-bar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parsing/minishell.h"

t_parse	*init_parse(char *elem, float flag)
{
	t_parse	*parse;

	parse = malloc(sizeof(t_parse));
	if (!parse)
		return (NULL);
	parse->elem = elem;
	parse->flag = flag;
	parse->next = NULL;
	return (parse);
}

t_control_parse	*init_control_parse(void)
{
	t_control_parse	*parse;

	parse = malloc(sizeof(t_control_parse));
	if (!parse)
		return (NULL);
	parse->first = NULL;
	parse->iter = NULL;
	parse->size = 0;
	return (parse);
}

t_var	*init_var(void)
{
	t_var	*var;

	var = malloc(sizeof(t_var));
	if (!var)
		return (NULL);
	var->varname = NULL;
	var->value = NULL;
	var->next = NULL;
	return (var);
}

t_var	*ft_lstnew(char *line)
{
	t_var	*new;

	new = malloc(sizeof(t_var));
	if (!new)
		return (NULL);
	new->varname = ft_strdup(line);
	new->value = NULL;
	new->next = NULL;
	return (new);
}
