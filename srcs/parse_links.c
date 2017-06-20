/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_links.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnunnari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 18:03:40 by mnunnari          #+#    #+#             */
/*   Updated: 2017/06/20 22:26:39 by mnunnari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	add_link_to_roomlinks(t_room *room, t_link *link)
{
	t_list	*new;

	new = (t_list*)malloc(sizeof(t_list));
	new->content = link;
	ft_lstadd(&room->links, new);
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
	link->cinnamon = 0;
	ft_lstaddnew(&hex->links, link, sizeof(t_link));
	add_link_to_roomlinks(room1, (t_link*)hex->links->content);
	add_link_to_roomlinks(room2, (t_link*)hex->links->content);
	free(link);
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
