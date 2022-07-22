/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_printer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cben-bar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 14:11:23 by cben-bar          #+#    #+#             */
/*   Updated: 2022/06/08 14:52:47 by cben-bar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing_printer(t_control_parse *parse_list)
{
	size_t	i;

	parse_list->iter = parse_list->first;
	i = 0;
	printf("INDEX\n");
	while (parse_list->iter)
	{
		printf("[%zu]->", i);
		parse_list->iter = parse_list->iter->next;
		i++;
	}
	parse_list->iter = parse_list->first;
	printf("\n\nELEM\n");
	while (parse_list->iter)
	{
		printf("[%s]->", parse_list->iter->elem);
		parse_list->iter = parse_list->iter->next;
	}
	parse_list->iter = parse_list->first;
	printf("\n\nFLAGS\n");
	while (parse_list->iter)
	{
		printf("[%d]->", parse_list->iter->flag);
		parse_list->iter = parse_list->iter->next;
	}
	printf("\n--------------------------------------");
	printf("\n\n");

//	print tempon
//	printf("\nelem a ajouter\n");
//	while (parse_list->iter)
//	{
//		printf("[%s]", parse_list->iter->flag);
//		parse_list->iter = parse_list->iter->next;
//	}

	return (0);
}
