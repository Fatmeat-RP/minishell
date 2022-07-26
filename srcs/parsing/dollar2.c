#include <minishell.h>

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
