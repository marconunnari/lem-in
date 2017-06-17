/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_hex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnunnari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 18:32:00 by mnunnari          #+#    #+#             */
/*   Updated: 2017/06/17 20:00:27 by mnunnari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISU_HEX_H
# define VISU_HEX_H

# include "lem_in.h"
# include "mlx.h"
# include <pthread.h>

# define SW 800

typedef	struct	s_move
{
	uintmax_t		ant;
	t_room			*dest;
}				t_move;

typedef	struct	s_point
{
	int			x;
	int			y;
}				t_point;

typedef	struct	s_rect
{
	int			swap;
	int			dx;
	int			dy;
	int			ix;
	int			iy;
}				t_rect;

typedef	struct	s_image
{
	char		*img;
	int			bpp;
	int			linesize;
	int			endian;
}				t_image;

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

void		fill_square(t_image image, t_point p1, size_t size, int color);
void		fill_rect(t_image image, t_point p1, t_point p2, int color);
void		fill_pixel(t_image img, int x, int y, int color);
void		draw_room(t_image image, t_li_info *li_info, t_room *room);
void		draw_links(t_image image, t_hex *hex);
void		draw_rooms(t_image image, t_hex *hex, t_li_info *li_info);
t_list		*parse_turns();
#endif
