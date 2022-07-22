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

#include <builtins.h>

//#include <stdio.h>
//#include <stdlib.h>

/*typedef struct s_instance
**{
**	char	**envp;
**	char	*prompt;
**}		t_instance;*/

void	built_in_env(t_instance *instance)
{
	size_t	i;

	i = -1;
	while (instance->envp[++i])
	{
		printf("%s\n", instance->envp[i]);
	}
}

/*int	main(int ac, char **av, char **env)
**{
**	(void)ac;
**	(void)av;
**	t_instance *inst;
**
**	inst = malloc(sizeof(t_instance));
**	inst->envp = env;
**	built_in_env(inst);
**	return (0);
}*/
