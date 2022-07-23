/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cben-bar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 11:34:58 by cben-bar          #+#    #+#             */
/*   Updated: 2022/07/02 14:06:55 by cben-bar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	built_in_env(t_instance *instance)
{
	size_t	i;

	i = 0;
	if (instance->envp == NULL)
		return (-1)
	while (instance->envp[i])
	{
		printf("%s\n", instance->envp[i]);
		i++;
	}
	return (0);
}
