/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_links.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnunnari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 19:49:15 by mnunnari          #+#    #+#             */
/*   Updated: 2017/06/18 21:48:31 by mnunnari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu_hex.h"

void		draw_link(t_image image, t_link *link)
{
	t_point		p1;
	t_point		p2;

	p1.x = link->room1->x + 10;
	p1.y = link->room1->y + 10;
	p2.x = link->room2->x + 10;
	p2.y = link->room2->y + 10;
	fill_rect(image, p1, p2, 0x00FFFFFF);
	return ;
}

void		draw_links(t_image image, t_hex *hex)
{
	t_list		*links;
	t_link		*link;

	links = hex->links;
	while (links)
	{
		link = (t_link*)links->content;
		draw_link(image, link);
		links = links->next;
	}
}
