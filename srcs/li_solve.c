/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   li_solve.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnunnari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/20 21:13:56 by mnunnari          #+#    #+#             */
/*   Updated: 2017/06/22 22:36:48 by mnunnari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		g_there_is_path = 0;

void			set_neighbours_distances(t_room *room, t_list **queue)
{
	t_list		*neighbours;
	t_room		*neighbour;

	neighbours = room->neighbours;
	while (neighbours)
	{
		neighbour = (t_room*)neighbours->content;
		if (neighbour->distance == 0)
		{
			neighbour->distance = room->distance + 1;
			ft_lstaddnew(queue, neighbour, 0);
		}
		neighbours = neighbours->next;
	}
}

void			set_distances(t_room *end, t_li_info *li_info)
{
	t_list		*queue;
	t_list		*currentlst;
	t_room		*room;

	queue = NULL;
	end->distance = 1;
	ft_lstaddnew(&queue, end, 0);
	while (queue)
	{
		currentlst = ft_lstpop(&queue);
		room = (t_room*)currentlst->content;
		if (room == li_info->start)
			g_there_is_path = 1;
		set_neighbours_distances(room, &queue);
	}
}

void			li_solve(uintmax_t ants, t_hex *hex, t_li_info *li_info)
{
	t_btree		*startfullrooms;

	(void)hex;
	set_distances(li_info->end, li_info);
	startfullrooms = ft_btreenew(li_info->start, 0);
	li_error(!g_there_is_path, "start and end rooms are not connected", hex);
	print_hex(ants, hex);
	move_ants(startfullrooms, li_info);
}
