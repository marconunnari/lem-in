/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rooms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnunnari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/17 16:58:21 by mnunnari          #+#    #+#             */
/*   Updated: 2017/06/17 16:58:28 by mnunnari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu_hex.h"

void		draw_room(t_image image, t_li_info *li_info, t_room *room)
{
	int			color;
	t_point		p;

	if (room->ant > 0)
			color = 0x00ff0000;
	else if (room == li_info->end)
		color = 0x0000ff00;
	else
		color = 0x00ffff00;
	p.x = room->x * 20;
	p.y = room->y * 20 + 20;
	fill_square(image, p, 20, color);
}

void		draw_rooms(t_image image, t_hex *hex, t_li_info *li_info)
{
	t_list		*rooms;
	t_room		*room;

	(void)li_info;
	rooms = hex->rooms;
	while (rooms)
	{
		room = (t_room*)rooms->content;
		draw_room(image, li_info, room);
		rooms = rooms->next;
	}
}
