/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarle-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:02:05 by acarle-m          #+#    #+#             */
/*   Updated: 2021/11/11 22:15:42 by acarle-m         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ft_strnstr(const char *s1, char *s2, size_t n)
{
	char const  *p;

	p = s1;
	if (ft_strlen(s2) == 0)
		return ((char *)s1);
	while (*p && n)
	{	
		if (ft_memcmp((void *)p, s2, ft_strlen(s2)) == 0 && ft_strlen(s2) <= n)
			return ((char *)p);
		p++;
		n--;
	}
	return (NULL);
}

char	*ft_strfreejoin(char *s1, char *s2)
{
	char	*s;
	size_t	i;
	size_t	j;

	i = 0;
	j = ft_strlen(s1);
	s = malloc(j + ft_strlen(s2) + 1);
	if (!s)
		return (NULL);
	while (i < j)
	{
		s[i] = s1[i];
		i++;
	}
    free(s1);
	while (i < (j + ft_strlen(s2)))
	{
		s[i] = s2[i - j];
		i++;
	}
	s[i] = 0;
	return (s);
}

size_t	ft_strlcpy(char *dst, char *src, size_t dstsize)
{
	size_t	src_len;
	size_t	i;

	i = 0;
	src_len = ft_strlen(src);
	if (dstsize == 0)
		return (ft_strlen(src));
	while (src[i] && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_len);
}

int	ft_memcmp(void *s1, void *s2, size_t n)
{
	size_t				i;
	unsigned char	*ss1;
	unsigned char	*ss2;

	i = 0;
	ss1 = s1;
	ss2 = s2;
	while (i < n)
	{
		if (ss1[i] != ss2[i])
			return (ss1[i] - ss2[i]);
		i++;
	}
	return (0);
}
