/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnunnari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 22:00:10 by mnunnari          #+#    #+#             */
/*   Updated: 2017/06/15 18:19:22 by mnunnari         ###   ########.fr       */
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

static void		render()
{
	void			*mlx;
	void			*win;

	mlx = mlx_init();
	win = mlx_new_window(mlx, SW, SW, "HEX Visualizer");
	mlx_string_put (mlx, win, 0, 0, 0x00FFFFFF, "hello visu-hex");
	mlx_key_hook(win, key_handler, NULL);
	mlx_loop(mlx);
}

int				main()
{
	render();
}
