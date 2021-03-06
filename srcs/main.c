/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnunnari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/14 20:37:42 by mnunnari          #+#    #+#             */
/*   Updated: 2017/06/24 21:55:08 by mnunnari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			main(int argc, char **argv)
{
	uintmax_t	ants;
	t_hex		*hex;
	t_li_info	*li_info;

	(void)argv;
	li_error(argc > 1, "too many arguments", NULL);
	ants = parse_ants();
	(void)ants;
	hex = (t_hex*)malloc(sizeof(t_hex));
	hex->rooms = NULL;
	hex->links = NULL;
	li_info = (t_li_info*)malloc(sizeof(t_li_info));
	li_info->start = NULL;
	li_info->end = NULL;
	li_info->start_ant = 1;
	li_info->total_ants = ants;
	parse_links(hex, parse_rooms(hex, li_info));
	li_info->start->ant = (ants * (ants + 1)) / 2;
	li_solve(hex, li_info);
	free_hex(hex);
	free(li_info);
}
