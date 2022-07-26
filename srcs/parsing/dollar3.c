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
