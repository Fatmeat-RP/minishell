/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarle-m <acarle-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 11:34:58 by cben-bar          #+#    #+#             */
/*   Updated: 2022/07/24 02:40:51 by acarle-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	built_in_env(char **arg, t_instance *instance)
{
	size_t	i;

	(void)arg;
	i = 0;
	if (instance->envp == NULL)
		return (-1);
	while (instance->envp[i])
	{
		printf("%s\n", instance->envp[i]);
		i++;
	}
	return (0);
}
