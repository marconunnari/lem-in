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
	li_error(split[0][0] == 'L', "a room's name can't start with L", hex);
	li_error(get_room(hex, split[0]) != NULL, "can't be two rooms with the same name", hex);
	li_error(!ft_isint(split[1]), "room's coordinates have to be integers", hex);
	li_error(!ft_isint(split[2]), "room's coordinates have to be integers", hex);
	room = (t_room*)malloc(sizeof(t_room));
	room->name = ft_strdup(split[0]);
	room->x = ft_atoi(split[1]);
	room->y = ft_atoi(split[2]);
	ft_lstpushnew(&hex->rooms, room, sizeof(t_room));
	free(room);
	ft_arrdel((void**)split);
	return (1);
}

char		*parse_rooms(t_hex *hex)
{
	char		*line;
	int			i;

	hex->rooms = NULL;
	while((i = get_next_line(0, &line)) > 0)
	{
		if (line[0] == '#')
			continue;
		if (!parse_room(line, hex))
			break;
		free(line);
	}
	li_error(i == -1, "input error", hex);
	return (line);
}
