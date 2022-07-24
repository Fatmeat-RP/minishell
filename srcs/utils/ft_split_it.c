/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cben-bar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 17:09:36 by cben-bar          #+#    #+#             */
/*   Updated: 2022/06/15 17:37:07 by cben-bar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_strsuperdup(char **split, int i, const char *s, size_t len)
{
	size_t	j;

	j = 0;
	split[i] = malloc (len + 1);
	if (!split[i])
	{
		while (i >= 0)
		{
			free (split[i]);
			i--;
		}
		free (split);
		return (0);
	}
	else
	{
		while (s[j] && j < len)
		{
			split[i][j] = s[j];
			j++;
		}
		split[i][j] = 0;
	}
	return (1);
}

size_t	parts_counter(char *s, char c)
{
	size_t	parts;
	size_t	beg;
	size_t	end;
	int		q;

	beg = 0;
	end = 0;
	parts = 0;
	q = 0;
	while (s[end])
	{
		q = tote(s[end], q);
		if (s[end] == c && q == 0)
		{
			if (end > beg)
				parts++;
			beg = end + 1;
		}
		end++;
	}
	if (end > beg)
		parts++;
	return (parts);
}

char	**ft_split_it(char *s, char c, size_t i, int q)
{
	char	**split;
	size_t	beg;
	size_t	end;

	beg = 0;
	end = 0;
	split = malloc(sizeof(char *) * (parts_counter(s, c) + 1));
	if (!split)
		return (NULL);
	while (s[end])
	{
		q = tote(s[end], q);
		if (s[end] == c && q == 0)
		{
			if (end > beg && !ft_strsuperdup (split, i++, s + beg, end - beg))
				return (NULL);
			beg = end + 1;
		}
		end++;
	}
	if (end > beg && !ft_strsuperdup (split, i++, s + beg, end - beg))
		return (NULL);
	split[i] = NULL;
	return (split);
}
