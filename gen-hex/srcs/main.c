/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnunnari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 22:00:10 by mnunnari          #+#    #+#             */
/*   Updated: 2017/06/18 21:23:35 by mnunnari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gen_hex.h"

typedef enum {
	START_ROOM, END_ROOM, ROOMS, LINKS
}			t_mode;
t_mode		g_mode = START_ROOM;

uintmax_t	counter = 1;

t_list		*g_rooms = NULL;

t_room		*get_room_by_coords(t_list *rooms, int x, int y)
{
	t_room		*room;
	int			f;

	while (rooms)
	{
		room = (t_room*)rooms->content;
		f = room->x <= x && room->x + 20 >= x &&
			room->y <= y && room->y + 20 >= y;
		if (f)
			return (room);
		rooms = rooms->next;
	}
	return (NULL);
}

void		do_link(t_hook_param p, t_point point)
{
	static t_room		*old_room;
	t_room		*room;
	t_link		*link;

	room = get_room_by_coords(g_rooms, point.x, point.y);
	if (!room)
		return ;
	//ft_printfnl("room: %s %d %d", room->name, room->x, room->y);
	if (!old_room)
	{
		old_room = room;
		return ;
	}
	link = (t_link*)malloc(sizeof(t_link));
	link->room1 = old_room;
	link->room2 = room;
	ft_printfnl("%s-%s", link->room1->name, link->room2->name);
	draw_link(p.image, link);
	mlx_put_image_to_window(p.mlx, p.win, p.imageptr, 0, 0);
	old_room = NULL;
}

void		do_room(t_hook_param p, t_point point)
{
	int		color;
	t_room	*room;

	if (get_room_by_coords(g_rooms, point.x, point.y) != NULL)
		return ;
	color = 0x00FFFFFF;
	if (g_mode == START_ROOM)
	{
		ft_printfnl("##start");
		color = 0x00FF0000;
		g_mode = END_ROOM;
	}
	else if (g_mode == END_ROOM)
	{
		ft_printfnl("##end");
		color = 0x0000FF00;
		g_mode = ROOMS;
	}
	room = (t_room*)malloc(sizeof(t_room));
	room->name = ft_uimaxtoa_base(counter++, 10);
	room->x = point.x;
	room->y = point.y;
	ft_lstaddnew(&g_rooms, room, sizeof(t_room));
	ft_printfnl("%s %d %d", room->name, room->x, room->y);
	fill_square(p.image, point, 20, color);
	mlx_put_image_to_window(p.mlx, p.win, p.imageptr, 0, 0);
}

int			mouse_handler(int button, int x, int y, void *param)
{
	t_hook_param		p;
	t_point				point;

	(void)button;
	p = *((t_hook_param*)param);
	point.x = x;
	point.y = y;
	if (g_mode != LINKS)
		do_room(p, point);
	else
		do_link(p, point);
	return (0);
}

int			key_handler(int keycode, void *param)
{
	(void)param;
	if (keycode == 53 || keycode == 65307)
		exit(0);
	if ((keycode == 37 || keycode == 108) && g_mode == ROOMS)
		g_mode = LINKS;
	return (0);
}

void		render()
{
	void			*mlx;
	void			*win;
	void			*imageptr;
	t_image			image;
	t_hook_param	hook_param;

	mlx = mlx_init();
	win = mlx_new_window(mlx, SW, SW, "HEX generator");
	imageptr = mlx_new_image(mlx, SW - 1, SW - 1);
	image.img = mlx_get_data_addr(imageptr,
			&image.bpp, &image.linesize, &image.endian);
	hook_param.mlx = mlx;
	hook_param.win = win;
	hook_param.image = image;
	hook_param.imageptr = imageptr;
	mlx_key_hook(win, key_handler, &hook_param);
	mlx_mouse_hook(win, mouse_handler, &hook_param);
	mlx_loop(mlx);
}

int			main(int argc, char **argv)
{
	li_error(argc != 2, "usage: gen-hex ants", NULL);
	ft_printfnl(argv[1]);
	render();
}
