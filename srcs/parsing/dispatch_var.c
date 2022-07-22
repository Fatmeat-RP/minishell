/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cben-bar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 20:42:52 by cben-bar          #+#    #+#             */
/*   Updated: 2022/07/08 23:18:18 by cben-bar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_name_value(size_t i, char *s)
{
	size_t	j;
	size_t	x;
	char	*value;

	j = 0;
	x = ft_strlen(s);
	value = malloc(sizeof(char) * (x - i + 1));
	while (s[i])
	{
		value[j] = s[i];
		j++;
		i++;
	}
	value[j] = '\0';
	return (value);
}

char	*ft_namer(size_t i, char *s)
{
	size_t	j;
	char	*name;

	name = malloc(sizeof(char) * i + 1);
	j = 0;
	while (j != i)
	{
		name[j] = s[j];
		j++;
	}
	name[j] = '\0';
	return (name);
}

size_t	ft_len_name(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '=')
		i++;
	return (i);
}

t_var	*dispatch_var(t_var *var)
{
	size_t	i;
	char	*name;
	char	*value;
	t_var	*start;

	i = 0;
	start = var;
	while (var)
	{
		name = NULL;
		value = NULL;
		i = ft_len_name(var->varname);
		name = ft_namer(i, var->varname);
		i++;
		value = ft_name_value(i, var->varname);
		free(var->varname);
		var->varname = name;
		var->value = value;
		var = var->next;
	}
	var = start;
	return (var);
}
