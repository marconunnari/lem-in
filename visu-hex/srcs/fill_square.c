/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_square.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnunnari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 20:06:50 by mnunnari          #+#    #+#             */
/*   Updated: 2017/06/16 20:11:00 by mnunnari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu_hex.h"

void		fill_square(t_image image, t_point p1, size_t size, int color)
{
	size_t		i;
	int			x;
	int			y;
	t_point		p2;

	x = p1.x;
	y = p1.y;
	i = 0;
	while (i < size)
	{
		p1.x = x + i;
		p2.x = x + i;
		p2.y = y + size;
		fill_rect(image, p1, p2, color);
		i++;
	}
}
