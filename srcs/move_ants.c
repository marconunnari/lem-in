/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnunnari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 21:35:15 by mnunnari          #+#    #+#             */
/*   Updated: 2017/06/23 22:33:02 by mnunnari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				cmprooms(t_btree *b1, t_btree *b2)
{
	t_room *room1;
	t_room *room2;

	room1 = (t_room*)b1->content;
	room2 = (t_room*)b2->content;
	return (room1->distance - room2->distance);
}

t_list			*get_next_rooms(t_room *room, t_li_info *li_info)
{
	uintmax_t	min_distance;
	t_list		*nexts;
	t_list		*neighbours;
	t_room		*neighbour;

	min_distance = 0;
	neighbours = room->neighbours;
	while (neighbours)
	{
		neighbour = (t_room*)neighbours->content;
		if (neighbour != li_info->start &&
			(neighbour->ant == 0 || neighbour == li_info->end) &&
			(min_distance == 0 || neighbour->distance < min_distance))
			min_distance = neighbour->distance;
		neighbours = neighbours->next;
	}
	//ft_printfnl("debug min_distance %d", min_distance);
	//ft_printfnl("debug min_distance + .. %d", min_distance + li_info->total_ants - li_info->start_ant);
	nexts = NULL;
	neighbours = room->neighbours;
	while (neighbours)
	{
		neighbour = (t_room*)neighbours->content;
		if (neighbour != li_info->start &&
			(neighbour->ant == 0 || neighbour == li_info->end) &&
			(neighbour->distance <= //== min_distance)) //<=
			(min_distance + li_info->total_ants - li_info->start_ant)))
		{
			//ft_printfnl("neighbour name %s distance %ju", neighbour->name, neighbour->distance);
			ft_lstaddnew(&nexts, neighbour, 0);
		}
		neighbours = neighbours->next;
	}
	return (nexts);
}

void			move_ant_from_start(t_btree **newfullrooms, t_li_info *li_info)
{
	t_list		*nexts;
	t_room		*next;
	int			first;

	first = 1;
	nexts = get_next_rooms(li_info->start, li_info);
	if (!nexts)
		return ft_btreeaddnew(newfullrooms, li_info->start, 0, cmprooms);
	while (nexts)
	{
		if (li_info->start->ant == 0)
			return ;
		next = (t_room*)nexts->content;
		//ft_printfnl("next %s distance %ju", next->name, next->distance);
		li_info->start->ant -= li_info->start_ant;
		next->ant += li_info->start_ant;
		li_info->start_ant += 1;
		if (next != li_info->end)
			ft_btreeaddnew(newfullrooms, next, 0, cmprooms);
		ft_printf("L%ju-%s ", li_info->start_ant - 1, next->name);
		nexts = nexts->next;
	}
	if (li_info->start->ant != 0)
		ft_btreeaddnew(newfullrooms, li_info->start, 0, cmprooms);
}

t_room			*get_next_room(t_room *room, t_li_info *li_info)
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
		if (neighbour != li_info->start &&
			(min_distance == 0 || neighbour->distance < min_distance))
		{
			next = neighbour;
			min_distance = neighbour->distance;
		}
		neighbours = neighbours->next;
	}
	if (next->ant == 0 || next == li_info->end)
		return (next);
	return (NULL);
}

void			move_ant(t_room *room, t_btree **newfullrooms, t_li_info *li_info)
{
	t_room		*next;
	uintmax_t	ant;

	next = get_next_room(room, li_info);
	if (!next)
		return ft_btreeaddnew(newfullrooms, room, 0, cmprooms);
	ant = room->ant;
	next->ant = room->ant;
	room->ant = 0;
	if (next != li_info->end)
		ft_btreeaddnew(newfullrooms, next, 0, cmprooms);
	ft_printf("L%ju-%s ", ant, next->name);
}

void			move_ants_from_fullroom(t_btree *fullroom, void *param)
{
	t_room		*room;
	t_param		*p;

	p = (t_param*)param;
	room = (t_room*)fullroom->content;
//	ft_printfnl("fullroom: %s ant %ju", room->name,
//			room == p->li_info->start ? p->li_info->start_ant : room->ant);
	if (room == p->li_info->start)
		move_ant_from_start(p->newfullrooms, p->li_info);
	else
		move_ant(room, p->newfullrooms, p->li_info);
}

void			move_ants(t_btree *fullrooms, t_li_info *li_info)
{
	t_btree		*newfullrooms;
	t_param		*param;

	if (!fullrooms)
		return ;
	newfullrooms = NULL;
	param = (t_param*)malloc(sizeof(t_param));
	param->newfullrooms = &newfullrooms;
	param->li_info = li_info;
	ft_btree_apply_infixp(fullrooms, move_ants_from_fullroom, param);
	ft_printfnl("");
	move_ants(newfullrooms, li_info);
}
