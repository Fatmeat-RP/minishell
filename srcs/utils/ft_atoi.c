#include <minishell.h>

int ft_atoi(char *s)
{
	int		res;
	int		maybe_neg;
	size_t	i;

	res = 0;
	maybe_neg = 1;
	i = 0;
	while ((s[i] >= 9 && s[i] <= 13) || s[i] == ' ')
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			maybe_neg *= (-1);
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		res = res * 10 + (s[i] - '0');
		i++;
	}
	return (res * maybe_neg);
}
