#include "lem_in.h"

void		free_room(t_room *room)
{
	free(room->name);
	free(room);
}

void		free_hex(t_hex *hex)
{
	t_room		*room;
	t_link		*link;
	t_list		*tmp;

	while(hex->rooms)
	{
		tmp = hex->rooms;
		room = (t_room*)hex->rooms->content;
		free_room(room);
		hex->rooms = hex->rooms->next;
		free(tmp);
	}
	while(hex->links)
	{
		tmp = hex->links;
		link = (t_link*)hex->links->content;
		free(link);
		hex->links = hex->links->next;
		free(tmp);
	}
	free(hex);
}
