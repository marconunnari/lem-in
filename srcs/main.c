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

void		li_error(int cond, char *msg)
{
	if (cond)
		ft_error(msg, 1);
}

t_room		*parse_room(char *line)
{
	char	**split;
	t_room	*room;

	split = ft_strsplit(line, ' ');
	li_error(ft_arrlen((void**)split) != 3, "wrong number of infos for room");
	li_error(split[0][0] == 'L', "a room's name can't start with L");
	//check if room is a duplicate
	li_error(!ft_isint(split[1]), "room's coordinates have to be integers");
	li_error(!ft_isint(split[2]), "room's coordinates have to be integers");
	room = (t_room*)malloc(sizeof(t_room));
	room->name = ft_strdup(split[0]);
	room->x = ft_atoi(split[1]);
	room->y = ft_atoi(split[2]);
	return (room);
}

t_list		*parse_rooms()
{
	t_list		*rooms;
	t_room		*room;
	char		*line;
	int			i;

	rooms = NULL;
	while((i = get_next_line(0, &line)) > 0)
	{
		if (line[0] == '#')
			continue;
		room = parse_room(line);
		ft_lstpushnew(&rooms, room, sizeof(t_room));
	}
	li_error(i == -1, "input error");
	return (rooms);
}

void		print_room(t_list *lst)
{
	t_room	*room;

	room = (t_room*)lst->content;
	if (room)
		ft_printfnl("  name: %s, x %d, y %d", room->name,
				room->x, room->y);
}

int			main(int argc, char **argv)
{
	uintmax_t	ants;
	t_list		*rooms;

	(void)argv;
	li_error(argc > 1, "too many arguments");
	ants = parse_ants();
	rooms = parse_rooms();
	ft_printfnl("ants: %ju", ants);
	ft_putendl("rooms:");
	ft_lstiter(rooms, print_room);
}
