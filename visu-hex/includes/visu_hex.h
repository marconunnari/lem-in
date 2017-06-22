/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_hex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnunnari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 18:32:00 by mnunnari          #+#    #+#             */
/*   Updated: 2017/06/22 20:27:09 by mnunnari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISU_HEX_H
# define VISU_HEX_H

# include "lem_in.h"
# include "mlx.h"

# define SW 800

typedef	struct	s_move
{
	uintmax_t		ant;
	t_room			*dest;
}				t_move;

typedef	struct	s_hook_moves
{
	void		*mlx;
	void		*win;
	void		*imageptr;
	t_image		image;
	t_hex		*hex;
	t_li_info	*li_info;
	t_list		*turns;
}				t_hook_moves;

void		draw_room(t_image image, t_li_info *li_info, t_room *room);
void		draw_links(t_image image, t_hex *hex);
void		draw_rooms(t_image image, t_hex *hex, t_li_info *li_info);
t_list		*parse_turns();
#endif
