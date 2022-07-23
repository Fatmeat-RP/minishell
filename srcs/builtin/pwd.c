/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarle-m <acarle-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 19:17:38 by cben-bar          #+#    #+#             */
/*   Updated: 2022/07/02 14:05:39 by cben-bar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>

int	built_in_pwd(void)
{
	char	*place;

	place = getcwd(NULL, 0);
	if (!place)
		return (-1);
	printf("%s\n", place);
	free(place);
	return (0)
}
