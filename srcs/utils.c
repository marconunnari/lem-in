#include "lem_in.h"

t_room		*get_room(t_hex *hex, char *name)
{
	t_list		*rooms;
	t_room		*room;

	rooms = hex->rooms;
	while (rooms)
	{
		room = (t_room*)rooms->content;
		if (ft_strequ(room->name, name))
			return (room);
		rooms = rooms->next;
	}
	return (NULL);
}
