#include <minishell.h>

static long	no_sep(char const *s, char c)
{
	long	i;

	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (!(*s))
			break ;
		i++;
		while (*s && *s != c)
			s++;
	}
	return (i);
}

static char	*asdup(char const *s, char c)
{
	long	len;
	char	*sa;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	sa = malloc(len + 1);
	if (!sa)
		return (NULL);
	sa[len] = 0;
	while (len > 0)
	{
		sa[len - 1] = s[len - 1];
		len -= 1;
	}
	return (sa);
}

static void	lefree(char **aos, long i)
{
	while (i)
	{
		free (aos[i]);
		i--;
	}
	free (aos);
}

char	**exec_split(char const *s, char c)
{
	char	**aos;
	long	n;

	n = 0;
	aos = malloc((no_sep (s, c) + 1) * sizeof (char *));
	if (!aos)
		return (NULL);
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (!(*s))
			break ;
		aos[n++] = asdup(s, c);
		if (!aos[n - 1])
		{
			lefree(aos, n);
			return (aos);
		}
		while (*s && *s != c)
			s++;
	}
	aos[n] = NULL;
	return (aos);
}
