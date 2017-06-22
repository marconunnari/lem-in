#include "lem_in.h"

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
//		ft_printf("min_distance %d ", min_distance);
//		ft_printf("neighbour: ");
//		print_room(neighbours);
		if (min_distance == 0 || neighbour->distance < min_distance)
		{
			next = neighbour;
			min_distance = neighbour->distance;
		}
		neighbours = neighbours->next;
	}
	if (next != li_info->start)
		if(next->ant == 0 || next == li_info->end)
			return (next);
	return (NULL);
}

void			move_ant_from_start(t_list **newfullrooms, t_li_info *li_info)
{
	t_room		*next;

	next = get_next_room(li_info->start, li_info);
	if (!next)
		return ft_lstpushnew(newfullrooms, li_info->start, 0);
	li_info->start->ant -= li_info->start_ant;
	next->ant += li_info->start_ant;
//	ft_printfnl("ant start %d", li_info->start_ant);
	if (li_info->start->ant != 0)
		ft_lstpushnew(newfullrooms, li_info->start, 0);
	li_info->start_ant += 1;
	if (next != li_info->end)
		ft_lstpushnew(newfullrooms, next, 0);
	ft_printf("L%ju-%s ", next->ant, next->name);
}

void			move_ant(t_room *room, t_list **newfullrooms, t_li_info *li_info)
{
	t_room		*next;

	next = get_next_room(room, li_info);
	if (!next)
		return ft_lstpushnew(newfullrooms, room, 0);
	next->ant = room->ant;
	room->ant = 0;
	if (next != li_info->end)
		ft_lstpushnew(newfullrooms, next, 0);
	ft_printf("L%ju-%s ", next->ant, next->name);
}

void			move_ants(t_list *fullrooms, t_li_info li_info)
{
	t_list		*newfullrooms;
	t_room		*room;

	(void)li_info;
	if (!fullrooms)
		return ;
	ft_putendl("full rooms:");
	ft_lstiter(fullrooms, print_room);
//	ft_printfnl("start?ant %d", li_info.start_ant);
	newfullrooms = NULL;
	while (fullrooms)
	{
		room = (t_room*)fullrooms->content;
		if (room == li_info.start)
			move_ant_from_start(&newfullrooms, &li_info);
		else
			move_ant(room, &newfullrooms, &li_info);
		fullrooms = fullrooms->next;
		//free previous
	}
	//free(fullrooms)
	ft_putchar('\n');
	move_ants(newfullrooms, li_info);
}
