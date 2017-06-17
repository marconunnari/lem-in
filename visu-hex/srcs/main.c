/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnunnari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 22:00:10 by mnunnari          #+#    #+#             */
/*   Updated: 2017/06/17 20:58:59 by mnunnari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu_hex.h"

int			key_handler(int keycode, void *param)
{
	(void)param;
	if (keycode == 53 || keycode == 65307)
		exit(0);
	return (0);
}

int			is_special(t_room *room, t_li_info *li_info)
{
	return (room == li_info->start || room == li_info->end);
}

t_room		*get_ant_room(t_hex *hex, t_li_info *li_info, uintmax_t ant)
{
	t_list		*rooms;
	t_room		*room;

	rooms = hex->rooms;
	while(rooms)
	{
		room = (t_room*)rooms->content;
		if (!is_special(room, li_info) && room->ant == ant)
			return (room);
		rooms = rooms->next;
	}
	if (li_info->start->ant >= ant)
		return (li_info->start);
	if (li_info->end->ant >= ant)
		return (li_info->end);
	return (NULL);
}

int			draw_moves(void *param)
{
	t_hook_moves	p;
	t_list			*turns;
	t_list			*turn;
	t_move			*move;
	t_room			*start_room;

	ft_printfnl("debug");
	p = *((t_hook_moves*)(param));
	turns = p.turns;
	while(turns)
	{
		turn = (t_list*)turns->content;
		while (turn)
		{
			move = (t_move*)turn->content;
			ft_printfnl("move ant %ju to room %s", move->ant, move->dest->name);
			if (!is_special(move->dest, p.li_info))
				li_error(move->dest->ant != 0, "destination room must be empty", NULL);
			start_room = get_ant_room(p.hex, p.li_info, move->ant);
			li_error(start_room == NULL, "ant doesn't exist", NULL);
			ft_printfnl("start_room %s", start_room->name);
			start_room->ant -= move->ant;
			//draw_room(p.image, p.li_info, start_room);
			draw_room(p.image, p.li_info, move->dest);
			mlx_put_image_to_window(p.mlx, p.win, p.imageptr, 0, 0);
			move->dest->ant += move->ant;
			turn = turn->next;
			ft_printfnl("debug");
		}
		turns = turns->next;
	}
	return (0);
}
/*
void		draw_turns(t_hook_moves hook_moves)
{
	pthread_t		tid;
	pthread_create(&tid, NULL, draw_moves, &hook_moves);
}
*/

int			hook(void *param)
{
	(void)param;
ft_printfnl("debug");
	return (0);
}

void		render(t_hex *hex, t_li_info *li_info, t_list *turns)
{
	void			*mlx;
	void			*win;
	void			*imageptr;
	t_image			image;
	t_hook_moves	hook_moves;

	mlx = mlx_init();
	win = mlx_new_window(mlx, SW, SW, "HEX Visualizer");
	mlx_key_hook(win, key_handler, NULL);
	imageptr = mlx_new_image(mlx, SW - 1, SW - 1);
	image.img = mlx_get_data_addr(imageptr,
			&image.bpp, &image.linesize, &image.endian);
	draw_rooms(image, hex, li_info);
	draw_links(image, hex);
	mlx_put_image_to_window(mlx, win, imageptr, 0, 0);
	hook_moves.mlx = mlx;
	hook_moves.win = win;
	hook_moves.image = image;
	hook_moves.imageptr = imageptr;
	hook_moves.hex = hex;
	hook_moves.li_info = li_info;
	hook_moves.turns = turns;
//	draw_turns(hook_moves);
	mlx_loop_hook(win, hook, NULL);
	mlx_loop(mlx);
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
	li_info->start->ant = (ants * (ants + 1)) / 2;
	ft_printfnl("debug %ju", li_info->start->ant);
	turns = parse_turns(hex);
	render(hex, li_info, turns);
	free_hex(hex);
}
