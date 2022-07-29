/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarle-m <acarle-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 19:34:51 by cben-bar          #+#    #+#             */
/*   Updated: 2022/07/24 04:17:32 by acarle-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	only_0(char *is_n)
{
	int	i;

	i = 0;
	while (is_n[i])
	{
		if (is_n[i] == '1')
			return (-1);
		i++;
	}
	return (1);
}

static void	looper(char **arg, int i, char *is_n)
{
	int	j;

	if (arg[i] == NULL)
		return ;
	while (arg[i])
	{
		j = 0;
		if (is_n[i - 1] == '0')
		{
			while (arg[i][j])
			{
				if (is_n[i - 1] == '1' && arg[i][j] == '\n')
					;
				else
					write(1, &arg[i][j], 1);
				j++;
			}
		}
		if (arg[i + 1] && is_n[i] != '1' && i != 1)
			write(1, " ", 1);
		i++;
	}
	return ;
}

static char	*check_arg(char **arg)
{
	int		i;
	char	*is_n;
	int		j;

	i = 0;
	is_n = malloc(ft_size(arg));
	if (!is_n)
		return (NULL);
	while (arg[++i])
	{
		j = 0;
		if (arg[i][j] == '-')
		{
			while (arg[i][j + 1] == 'n')
				j++;
			if (arg[i][j + 1] == '\0' && arg[i][j] == 'n')
				is_n[i - 1] = '1';
			else
				is_n[i - 1] = '0';
		}
		else
			is_n[i - 1] = '0';
	}
	is_n[i - 1] = 0;
	return (is_n);
}

int	builtin_echo(char **arg, t_instance *instance)
{
	int		i;
	char	*is_n;

	(void)instance;
	i = 1;
	is_n = check_arg(arg);
	if (!is_n)
		return (-1);
	looper(arg, i, is_n);
	if (arg[1] && only_0(is_n) != -1)
		write(1, "\n", 1);
	free(is_n);
	return (0);
}
