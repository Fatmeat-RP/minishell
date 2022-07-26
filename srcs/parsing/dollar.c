/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cben-bar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 16:17:02 by cben-bar          #+#    #+#             */
/*   Updated: 2022/07/19 18:44:16 by cben-bar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_var	*node_env(char *varname, t_var *var)
{
	while (var)
	{
		if (ft_strcmp(varname, var->varname) == 0)
			break ;
		var = var->next;
	}
	return (var);
}

t_bool	in_charset(char c)
{
	if (c == ' ' || c == '|' || c == '-' || c == '\0'
		|| c == '$' || c == '\'' || c == '\"')
		return (true);
	return (false);
}

char	*find_name(char *s, size_t dellen, size_t i, size_t j)
{
	char	*varname;
	int		q;

	varname = malloc(sizeof(char) * dellen);
	q = 0;
	while (s[i] && j == 0)
	{
		q = tote(s[i], q);
		if (q != 1 && s[i] == '$')
		{
			i++;
			while ((j < dellen - 1) && !in_charset(s[i]))
			{
				varname[j] = s[i];
				j++;
				i++;
			}
			varname[j] = '\0';
		}
		i++;
	}
	return (varname);
}

int	search_value(char *varname, t_var *var)
{
	t_var	*start;

	start = var;
	if (ft_strcmp(varname, "?") == 0)
		return (2);
	while (var)
	{
		if (ft_strcmp(varname, var->varname) == 0)
			return (1);
		var = var->next;
	}
	var = start;
	return (0);
}

size_t	cpy_value_2(char *dst, char *value, size_t i)
{
	while (value[i])
	{
		dst[i] = value[i];
		i++;
	}
	return (i);
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
		{
			final_s[j] = node->elem[i];
			i++;
			j++;
		}
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

size_t	findaddlen(char *s, size_t dellen, t_var *var)
{
	char	*varname;
	size_t	addlen;
	t_var	*start;
	size_t	i;
	size_t	j;

	start = var;
	addlen = 0;
	i = 0;
	j = 0;
	varname = find_name(s, dellen, i, j);
	addlen = ft_find_value(varname, var);
	free(varname);
	var = start;
	return (addlen);
}

size_t	finddellen(char *s, size_t i)
{
	size_t	j;
	int		q;
	size_t	del;

	j = 0;
	q = 0;
	while (s[i])
	{
		q = tote(s[i], q);
		if (q != 1 && s[i] == '$')
		{
			j = i + 1;
			del = 1;
			while (!in_charset(s[j]))
			{
				j++;
				del++;
			}
			if (in_charset(s[j]))
				return (del);
		}
		i++;
	}
	return (del);
}

int	ft_alloc(t_parse *node, t_var *var)
{
	size_t	delen;
	size_t	addlen;
	char	*s;
	size_t	i;

	i = 0;
	delen = finddellen(node->elem, i);
	addlen = findaddlen(node->elem, delen, var);
	s = malloc(sizeof(char) * (ft_strlen(node->elem) + addlen - delen + 1));
	if (!s)
		return (false);
	sub_it(s, node, var, delen);
	free(node->elem);
	node->elem = s;
	return (true);
}

t_bool	there_is_doll(char *s)
{
	size_t	i;
	int		q;

	i = 0;
	q = 0;
	while (s[i])
	{
		q = tote(s[i], q);
		if ((q == 0 || q == 2) && s[i] == '$')
			return (true);
		i++;
	}
	return (false);
}

int	dollar(t_control_parse *parsing, char **env)
{
	t_var	*var;

	var = set_var(env);
	parsing->iter = parsing->first;
	while (parsing->iter)
	{
		if (there_is_doll(parsing->iter->elem))
		{
			if (!ft_alloc(parsing->iter, var))
				return (false);
		}
		else
			parsing->iter = parsing->iter->next;
	}
	var_clear(var);
	return (true);
}
