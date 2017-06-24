/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnunnari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/14 20:37:42 by mnunnari          #+#    #+#             */
/*   Updated: 2017/06/24 21:44:45 by mnunnari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room		*g_start;
t_room		*g_end;

void		print_link(t_list *lst)
{
	t_link	*link;

	link = (t_link*)lst->content;
	ft_printfnl("%s-%s", link->room1->name, link->room2->name);
}

void		print_room(t_list *lst)
{
	t_room	*room;

	room = (t_room*)lst->content;
	if (room == g_start)
		ft_printfnl("##start");
	if (room == g_end)
		ft_printfnl("##end");
	ft_printfnl("%s %d %d", room->name, room->x, room->y);
}

void		print_hex(t_hex *hex, t_li_info *li_info)
{
	g_start = li_info->start;
	g_end = li_info->end;
	ft_printfnl("%ju", li_info->total_ants);
	ft_lstiter(hex->rooms, print_room);
	ft_lstiter(hex->links, print_link);
	ft_putchar('\n');
}
