/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnunnari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/14 20:37:42 by mnunnari          #+#    #+#             */
/*   Updated: 2017/06/16 17:53:12 by mnunnari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		print_room(t_list *lst)
{
	t_room	*room;

	room = (t_room*)lst->content;
	if (room)
		ft_printfnl("  name: %s, x %d, y %d", room->name,
				room->x, room->y);
}

void		print_link(t_list *lst)
{
	t_link	*link;

	link = (t_link*)lst->content;
	if (link)
		ft_printfnl("  room1: %s, room2: %s",
			link->room1->name, link->room2->name);
}

int			main(int argc, char **argv)
{
	uintmax_t	ants;
	t_hex		*hex;
	t_li_info	*li_info;

	(void)argv;
	li_error(argc > 1, "too many arguments", NULL);
	ants = parse_ants();
	hex = (t_hex*)malloc(sizeof(t_hex));
	hex->rooms = NULL;
	hex->links = NULL;
	li_info = (t_li_info*)malloc(sizeof(t_li_info));
	li_info->start = NULL;
	li_info->end = NULL;
	parse_links(hex, parse_rooms(hex, li_info));

	ft_printfnl("ants: %ju", ants);
	ft_putendl("rooms:");
	ft_lstiter(hex->rooms, print_room);
	ft_putendl("links:");
	ft_lstiter(hex->links, print_link);
	ft_printfnl("start: %s", li_info->start->name);
	ft_printfnl("end: %s", li_info->end->name);
	free_hex(hex);
}
