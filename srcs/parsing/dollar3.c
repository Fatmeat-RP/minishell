/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarle-m <acarle-m@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 01:52:08 by acarle-m          #+#    #+#             */
/*   Updated: 2022/07/28 01:52:08 by acarle-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	sub_it(char *final_s, t_parse *node, t_var *var, size_t	dellen)
{
	size_t	i;
	size_t	j;
	int		q;
	int		round;

	i = 0;
	j = 0;
	q = 0;
	round = 0;
	while (node->elem[i])
	{
		q = tote(node->elem[i], q);
		if (q != 1 && node->elem[i] == '$' && round == 0)
		{
			j += cpy_value(&node->elem[i], var, dellen, &final_s[j]);
			i += dellen;
			final_s[j] = '\0';
			round = 1;
		}
		else
			final_s[j++] = node->elem[i++];
	}
	final_s[j] = '\0';
}

size_t	ft_find_value(char *varname, t_var *var)
{
	t_var	*start;
	size_t	len;
	char	*itoa_g_status;

	start = var;
	len = 0;
	if (ft_strcmp(varname, "?") == 0)
	{
		itoa_g_status = ft_itoa(g_status);
		len = ft_strlen(itoa_g_status);
		free(itoa_g_status);
		return (len);
	}
	while (var && len == 0)
	{
		if (ft_strcmp(varname, var->varname) == 0)
		{
			len = ft_strlen(var->value);
			break ;
		}
		var = var->next;
	}
	var = start;
	return (len);
}

size_t	cpy_value(char *s, t_var *var, size_t dellen, char *dst)
{
	size_t	i;
	size_t	j;
	char	*varname;
	t_var	*start;
	char	*itoa_g_status;

	start = var;
	i = 0;
	j = 0;
	varname = find_name(s, dellen, i, j);
	if (search_value(varname, var) == 2)
	{
		itoa_g_status = ft_itoa(g_status);
		i = cpy_value_2(dst, itoa_g_status, i);
		free(itoa_g_status);
	}
	else if (search_value(varname, var) == 1)
	{
		var = node_env(varname, var);
		i = cpy_value_2(dst, var->value, i);
	}
	var = start;
	free(varname);
	return (i);
}
