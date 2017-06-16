/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rooms.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnunnari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 17:11:53 by mnunnari          #+#    #+#             */
/*   Updated: 2017/06/16 17:26:27 by mnunnari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	parse_room(char *line, t_hex *hex)
{
	char	**split;
	t_room	*room;

	split = ft_strsplit(line, ' ');
	if (ft_arrlen((void**)split) != 3)
	{
		ft_arrdel((void**)split);
		return (0);
	}
	li_error(split[0][0] == 'L', "room start with L", hex);
	li_error(get_room(hex, split[0]) != NULL, "room duplicate", hex);
	li_error(!ft_isint(split[1]), "room's coordinates not integers", hex);
	li_error(!ft_isint(split[2]), "room's coordinates not integers", hex);
	room = (t_room*)malloc(sizeof(t_room));
	room->name = ft_strdup(split[0]);
	room->x = ft_atoi(split[1]);
	room->y = ft_atoi(split[2]);
	ft_lstaddnew(&hex->rooms, room, sizeof(t_room));
	free(room);
	ft_arrdel((void**)split);
	return (1);
}

static void	parse_li_info(t_cmd cmd, t_room *room, t_li_info *li_info)
{
	if (cmd == NONE)
		return ;
	if (cmd == START)
		li_info->start = room;
	if (cmd == END)
		li_info->end = room;
}

char		*parse_rooms(t_hex *hex, t_li_info *li_info)
{
	char		*line;
	int			i;
	t_cmd		cmd;

	cmd = NONE;
	while((i = get_next_line(0, &line)) > 0)
	{
		if (line[0] == '#')
		{
			if (ft_strequ(line, "##start"))
				cmd = START;
			if (ft_strequ(line, "##end"))
				cmd = END;
			continue;
		}
		if (!parse_room(line, hex))
			break;
		parse_li_info(cmd, (t_room*)hex->rooms->content, li_info);
		free(line);
		cmd = NONE;
	}
	li_error(li_info->start == NULL, "no start room", hex);
	li_error(li_info->end == NULL, "no end room", hex);
	li_error(i == -1, "input error", hex);
	return (line);
}
