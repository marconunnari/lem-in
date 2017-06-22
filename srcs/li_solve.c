/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   li_solve.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnunnari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/20 21:13:56 by mnunnari          #+#    #+#             */
/*   Updated: 2017/06/21 21:15:49 by mnunnari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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

void			set_distances(t_room *end)
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
		set_neighbours_distances(room, &queue);
	}
}

void			li_solve(t_hex *hex, t_li_info *li_info)
{
	t_list		*startfullrooms;

	(void)hex;
	set_distances(li_info->end);
	startfullrooms = NULL;
	ft_lstaddnew(&startfullrooms, li_info->start, 0);
	move_ants(startfullrooms, *li_info);
}
