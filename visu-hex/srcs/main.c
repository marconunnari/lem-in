/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnunnari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 22:00:10 by mnunnari          #+#    #+#             */
/*   Updated: 2017/06/16 20:20:05 by mnunnari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu_hex.h"

int		key_handler(int keycode, void *param)
{
	(void)param;
	if (keycode == 53 || keycode == 65307)
		exit(0);
	return (0);
}

void		draw_rooms(t_image image, t_hex *hex, t_li_info *li_info)
{
	t_list		*rooms;
	t_room		*room;
	t_point		p;
	int			color;

	(void)li_info;
	rooms = hex->rooms;
	while (rooms)
	{
		room = (t_room*)rooms->content;
		if (room->ant > 0)
			color = 0x00ff0000;
		else if (room == li_info->end)
			color = 0x0000ff00;
		else
			color = 0x00ffff00;
		p.x = room->x * 20;
		p.y = room->y * 20 + 20;
		fill_square(image, p, 20, color);
		rooms = rooms->next;
	}
}

void		render(t_hex *hex, t_li_info *li_info)
{
	void			*mlx;
	void			*win;
	void			*imageptr;
	t_image			image;

	mlx = mlx_init();
	win = mlx_new_window(mlx, SW, SW, "HEX Visualizer");
	imageptr = mlx_new_image(mlx, SW - 1, SW - 1);
	image.img = mlx_get_data_addr(imageptr,
			&image.bpp, &image.linesize, &image.endian);
	draw_rooms(image, hex, li_info);
	draw_links(image, hex);
	mlx_put_image_to_window(mlx, win, imageptr, 0, 0);
	mlx_key_hook(win, key_handler, NULL);
	mlx_loop(mlx);
}

void			print_move(t_list *lst)
{
	t_move *move;

	if (!lst)
		return;
	move = (t_move*)lst->content;
	ft_printfnl("move ant %ju to room %s", move->ant, move->room);
}

void			print_turn(t_list *turn)
{
	ft_lstiter(((t_list*)turn->content), print_move);
	ft_putendl("");
}

int			main(int argc, char **argv)
{
	uintmax_t	ants;
	t_hex		*hex;
	t_li_info	*li_info;
	t_list		*turns;

	(void)argv;
	li_error(argc > 1, "too many arguments", NULL);
	ants = parse_ants();
	hex = (t_hex*)malloc(sizeof(t_hex));
	hex->rooms = NULL;
	hex->links = NULL;
	li_info = (t_li_info*)malloc(sizeof(t_li_info));
	li_info->start = NULL;
	li_info->end = NULL;
	parse_links(hex, parse_rooms(hex, li_info));
	li_info->start->ant = ants;
	turns = parse_turns();
	ft_lstiter(turns, print_turn);
	render(hex, li_info);
	free_hex(hex);
}
