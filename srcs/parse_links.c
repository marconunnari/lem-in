/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_links.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnunnari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 18:03:40 by mnunnari          #+#    #+#             */
/*   Updated: 2017/06/21 17:04:34 by mnunnari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	already_neighbours(t_room *room1, t_room *room2)
{
	t_list		*neighbours;
	t_room		*room;

	neighbours = room1->neighbours;
	while (neighbours)
	{
		room = (t_room*)neighbours->content;
		if (room == room2)
			return (1);
		neighbours = neighbours->next;
	}
	return (0);
}

static void	make_neighbours(t_room *room1, t_room *room2)
{
	t_list	*new;

	if (already_neighbours(room1, room2))
		return ;
	new = (t_list*)malloc(sizeof(t_list));
	new->content = room2;
	ft_lstadd(&room1->neighbours, new);
	new = (t_list*)malloc(sizeof(t_list));
	new->content = room1;
	ft_lstadd(&room2->neighbours, new);
}

static void	parse_link(char *line, t_hex *hex)
{
	char	**split;
	t_link	*link;
	t_room	*room1;
	t_room	*room2;

	split = ft_strsplit(line, '-');
	li_error(ft_arrlen((void**)split) != 2, "wrong number of infos for link", hex);
	li_error((room1 = get_room(hex, split[0])) == NULL, "room specified by link doesnt't exits", hex);
	li_error((room2 = get_room(hex, split[1])) == NULL, "room specified by link doesnt't exits", hex);
	link = (t_link*)malloc(sizeof(t_link));
	link->room1 = room1;
	link->room2 = room2;
	ft_lstaddnew(&hex->links, link, sizeof(t_link));
	free(link);
	make_neighbours(room1, room2);
	ft_arrdel((void**)split);
}

void		parse_links(t_hex *hex, char *line)
{
	int			i;

	parse_link(line, hex);
	free(line);
	while((i = get_next_line(0, &line)) > 0)
	{
		if (line[0] == '#')
			continue;
		parse_link(line, hex);
		free(line);
	}
	free(line);
	li_error(i == -1, "input error", hex);
}
