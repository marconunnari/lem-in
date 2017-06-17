/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_links.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnunnari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 19:49:15 by mnunnari          #+#    #+#             */
/*   Updated: 2017/06/16 20:15:21 by mnunnari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu_hex.h"

void		draw_links(t_image image, t_hex *hex)
{
	t_list		*links;
	t_link		*link;
	t_point		p1;
	t_point		p2;
	int			x1;
	int			y1;
	int			x2;
	int			y2;

	links = hex->links;
	while (links)
	{
		link = (t_link*)links->content;
		x1 = link->room1->x * 20;
		y1 = link->room1->y * 20 + 20;
		x2 = link->room2->x * 20;
		y2 = link->room2->y * 20 + 20;
		//ft_printfnl("%s: x1 %d y1 %d %s x2 %d y2 %d",
		//		link->room1->name, x1, y1, link->room2->name, x2, y2);
		if ((x1 <= x2 && x1 + 20 >= x2) && y1 > y2)
		{
			p1.x = x1 + 10;
			p1.y = y1;
			p2.x = x2 + 10;
			p2.y = y2 + 20;
		}
		else if ((x1 <= x2 && x1 + 20 >= x2) && y1 < y2)
		{
			p1.x = x1 + 10;
			p1.y = y1 + 20;
			p2.x = x2 + 10;
			p2.y = y2;
		}
		else if (x1 < x2)
		{
			p1.x = x1 + 20;
			p1.y = y1 + 10;
			p2.x = x2;
			p2.y = y2 + 10;
		}
		else if (x1 > x2)
		{
			p1.x = x1;
			p1.y = y1 + 10;
			p2.x = x2 + 20;
			p2.y = y2 + 10;
		}
		fill_rect(image, p1, p2, 0x00FFFFFF);
		links = links->next;
	}
}
