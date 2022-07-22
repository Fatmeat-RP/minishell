/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarle-m <acarle-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 10:55:54 by acarle-m          #+#    #+#             */
/*   Updated: 2022/04/27 12:32:04 by acarle-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

size_t	ft_size(char **array)
{
	size_t	i;

	i = 0;
	if (!array)
		return (i);
	while (array[i] != NULL)
		i++;
	return (i);
}

int	pipe_counter(t_control_parse *parse)
{
	int	i;

	i = 0;
	while (parse->iter)
	{
		if (parse->iter->flag == PIPE_FLAG)
			i++;
		parse->iter = parse->iter->next;
	}
	parse->iter = parse->first;
	return (i);
}

int	line_counter(char **aos)
{
	int	i;

	i = 0;
 	if (!aos)
		return (0);
	if (!aos[i])
		return (0);
	while (aos[i + 1] != NULL)
		i++;
	return (i);
}
