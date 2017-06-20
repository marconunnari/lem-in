/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   li_solve.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnunnari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/20 21:13:56 by mnunnari          #+#    #+#             */
/*   Updated: 2017/06/20 23:21:02 by mnunnari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			put_cinnamon(t_room *root, uintmax_t cinnamon)
{
	t_list		*links;
	t_link		*link;
	int			new;

	ft_printfnl("root: name: %s cinnamon %ju", root->name, cinnamon);
	links = root->links;
	while (links)
	{
		link = (t_link*)links->content;
		new = link->cinnamon == 0;
		if (new || link->cinnamon > cinnamon)
			link->cinnamon = cinnamon;
		if (new || link->cinnamon > cinnamon)
		{
		ft_printfnl("link: room1: %s room2 %s", link->room1->name, link->room2->name);
			if (link->room1 != root)
				put_cinnamon(link->room1, cinnamon + 1);
			else
				put_cinnamon(link->room2, cinnamon + 1);
		}
		links = links->next;
	}
}

void			li_solve(t_hex *hex, t_li_info *li_info)
{
	(void)hex;
	put_cinnamon(li_info->end, 1);
}
