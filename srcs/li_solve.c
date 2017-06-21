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
			ft_lstaddnewsimple(queue, neighbour);
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
	ft_lstaddnewsimple(&queue, end);
	while (queue)
	{
		currentlst = ft_lstpop(&queue);
		room = (t_room*)currentlst->content;
		set_neighbours_distances(room, &queue);
	}
}

t_room			*get_next_room(t_room *room)
{
	uintmax_t	min_distance;
	t_room		*next;
	t_list		*neighbours;
	t_room		*neighbour;

	min_distance = 0;
	next = NULL;
	neighbours = room->neighbours;
	while (neighbours)
	{
		neighbour = (t_room*)neighbours->content;
		if (neighbour->ant == 0)
			if (min_distance == 0 || neighbour->distance < min_distance)
				next = neighbour;
		neighbours = neighbours->next;
	}
	return (next);
}

void			move_ant_from_start(t_list **newfullrooms, t_li_info li_info)
{
	t_room		*next;

	next = get_next_room(li_info.start);
	if (!next)
		return;
	li_info.start->ant -= li_info.start_ant;
	next->ant += li_info.start_ant;
	if (li_info.start->ant != 0)
	{
		ft_lstaddnewsimple(newfullrooms, li_info.start);
		li_info.start_ant++;
	}
	ft_lstaddnewsimple(newfullrooms, next);
	ft_printfnl("L%ju-%s", next->ant, next->name);
}

void			move_ant(t_room *room, t_list **newfullrooms)
{
	t_room		*next;

	next = get_next_room(room);
	if (!next)
		return;
	next->ant += room->ant;
	room->ant = 0;
	ft_lstaddnewsimple(newfullrooms, next);
	ft_printfnl("L%ju-%s", next->ant, next->name);
}

void			move_ants(t_list *fullrooms, t_li_info li_info)
{
	t_list		*newfullrooms;
	t_room		*room;

	if (!fullrooms)
		return ;
	newfullrooms = NULL;
	while (fullrooms)
	{
		room = (t_room*)fullrooms->content;
		if (room == li_info.start)
			move_ant_from_start(&newfullrooms, li_info);
		else
			move_ant(room, &newfullrooms);
		fullrooms = fullrooms->next;
		//free previous
	}
	//free(fullrooms)
	move_ants(newfullrooms, li_info);
}

void			li_solve(t_hex *hex, t_li_info *li_info)
{
	t_list		*startfullrooms;

	(void)hex;
	set_distances(li_info->end);
	startfullrooms = NULL;
	ft_lstaddnewsimple(&startfullrooms, li_info->start);
	move_ants(startfullrooms, *li_info);
}
