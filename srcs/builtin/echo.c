/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cben-bar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 19:34:51 by cben-bar          #+#    #+#             */
/*   Updated: 2022/07/02 14:19:36 by cben-bar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>

static t_bool	is_option(char *option)
{
	size_t	i;

	i = 2;
	if (option[0] == '-' && option[1] == 'n')
	{
		if (option[i] == '\0')
			return (true);
		else
		{
			while (option[i])
			{
				if (option[i] != 'n')
					return (false);
				i++;
			}
		}
		return (true);
	}
	return (false);
}

static	char	*new_line(char *old_line, size_t mark)
{
	while (old_line[mark] == ' ')
		mark++;
	return (&old_line[mark]);
}

static int	built_in_echo(char *line, size_t option)
{
	if (option)
		printf("%s", line);
	else
		printf("%s\n", line);
	return (0);
}

void	built_in_echo(char *line)
{
	char	**splited_line;
	size_t	i;
	char	*tmp;

	splited_line = ft_split(line, ' ');
	i = 0;
	i = ft_strlen(splited_line[0]);
	if (is_option(splited_line[0]))
	{
		tmp = new_line(line, i);
		built_in_echo(tmp, 1);
	}
	else
		built_in_echo(line, 0);
}

int	main(int ac, char **av)
{
	(void)ac;
	call_built_in_echo(av[2]);
	return (0);
}
