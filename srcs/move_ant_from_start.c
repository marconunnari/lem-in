/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ant_from_start.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnunnari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/24 21:24:58 by mnunnari          #+#    #+#             */
/*   Updated: 2017/06/24 21:40:19 by mnunnari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				validnext(t_room *neighbour, t_li_info *li_info)
{
	return (neighbour != li_info->start && neighbour->distance &&
			(neighbour->ant == 0 || neighbour == li_info->end));
}

int				closer(uintmax_t min_distance, t_room *neighbour)
{
	return (min_distance == 0 || neighbour->distance < min_distance);
}

int				is_worth(uintmax_t min_distance, t_room *neighbour,
						t_li_info *li_info)
{
	return (neighbour->distance <=
			(min_distance + li_info->total_ants - li_info->start_ant));
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
		if (validnext(neighbour, li_info) && closer(min_distance, neighbour))
			min_distance = neighbour->distance;
		neighbours = neighbours->next;
	}
	nexts = NULL;
	neighbours = room->neighbours;
	while (neighbours)
	{
		neighbour = (t_room*)neighbours->content;
		if (validnext(neighbour, li_info) &&
				is_worth(min_distance, neighbour, li_info))
			ft_lstaddnew(&nexts, neighbour, 0);
		neighbours = neighbours->next;
	}
	return (nexts);
}

void			move_ant_from_start(t_btree **newfullrooms, t_li_info *li_info)
{
	t_list		*nexts;
	t_room		*next;
	t_list		*tmp;

	nexts = get_next_rooms(li_info->start, li_info);
	if (!nexts)
		return (ft_btreeaddnew(newfullrooms, li_info->start, 0, cmprooms));
	while (nexts)
	{
		tmp = nexts;
		if (li_info->start->ant == 0)
			return (free(tmp));
		next = (t_room*)nexts->content;
		li_info->start->ant -= li_info->start_ant;
		next->ant += li_info->start_ant;
		li_info->start_ant += 1;
		if (next != li_info->end)
			ft_btreeaddnew(newfullrooms, next, 0, cmprooms);
		ft_printf("L%ju-%s ", li_info->start_ant - 1, next->name);
		nexts = nexts->next;
		free(tmp);
	}
	if (li_info->start->ant != 0)
		ft_btreeaddnew(newfullrooms, li_info->start, 0, cmprooms);
}
