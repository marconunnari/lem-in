/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnunnari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/24 21:11:01 by mnunnari          #+#    #+#             */
/*   Updated: 2017/06/24 21:11:03 by mnunnari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
