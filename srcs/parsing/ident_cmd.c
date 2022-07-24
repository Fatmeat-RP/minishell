/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ident_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cben-bar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 01:18:32 by cben-bar          #+#    #+#             */
/*   Updated: 2022/07/09 01:21:41 by cben-bar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ident_cmd(char *s)
{
	if (ft_strcmp(s, "echo") == 0)
		return (BUILTIN_FLAG);
	if (ft_strcmp(s, "cd") == 0)
		return (BUILTIN_FLAG);
	if (ft_strcmp(s, "pwd") == 0)
		return (BUILTIN_FLAG);
	if (ft_strcmp(s, "env") == 0)
		return (BUILTIN_FLAG);
	if (ft_strcmp(s, "export") == 0)
		return (BUILTIN_FLAG);
	if (ft_strcmp(s, "unset") == 0)
		return (BUILTIN_FLAG);
	if (ft_strcmp(s, "exit") == 0)
		return (BUILTIN_FLAG);
	return (CMD_FLAG);
}
