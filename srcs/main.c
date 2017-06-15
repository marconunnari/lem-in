/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnunnari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/14 20:37:42 by mnunnari          #+#    #+#             */
/*   Updated: 2017/06/15 19:51:34 by mnunnari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		li_error(int cond, char *msg, t_hex *hex)
{
	if (!cond)
		return;
	if (hex)
		free_hex(hex);
	ft_error(msg, 1);
}

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

	(void)argv;
	li_error(argc > 1, "too many arguments", NULL);
	ants = parse_ants();
	hex = (t_hex*)malloc(sizeof(t_hex));
	parse_links(hex, parse_rooms(hex));
	ft_printfnl("ants: %ju", ants);
	ft_putendl("rooms:");
	ft_lstiter(hex->rooms, print_room);
	ft_putendl("links:");
	ft_lstiter(hex->links, print_link);
	free_hex(hex);
}
