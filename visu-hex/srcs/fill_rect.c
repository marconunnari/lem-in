/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_rect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnunnari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/11 23:26:40 by mnunnari          #+#    #+#             */
/*   Updated: 2017/06/16 20:02:45 by mnunnari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu_hex.h"

t_rect		get_rect(t_point p1, t_point p2)
{
	t_rect	rect;

	rect.dx = p2.x - p1.x;
	rect.dy = p2.y - p1.y;
	rect.swap = 0;
	if (abs(rect.dx) < abs(rect.dy))
	{
		ft_swap_ints(&rect.dx, &rect.dy);
		rect.swap = 1;
	}
	rect.dx = abs(rect.dx);
	rect.dy = abs(rect.dy);
	rect.ix = p2.x >= p1.x ? 1 : -1;
	rect.iy = p2.y >= p1.y ? 1 : -1;
	return (rect);
}

t_point		next(t_point point, t_rect rect, int *d)
{
	point.x = point.x + rect.ix;
	if (*d > 0)
	{
		point.y = point.y + rect.iy;
		*d = *d + 2 * (rect.dy - rect.dx);
	}
	else
	{
		if (rect.swap)
		{
			point.y = point.y + rect.iy;
			point.x = point.x - rect.ix;
		}
		*d = *d + 2 * rect.dy;
	}
	return (point);
}

void		fill_rect(t_image image, t_point p1, t_point p2, int color)
{
	t_rect		rect;
	t_point		point;
	int			d;
	int			i;

	rect = get_rect(p1, p2);
	i = 0;
	point.x = p1.x;
	point.y = p1.y;
	d = 2 * rect.dy - rect.dx;
	while (i <= rect.dx)
	{
		fill_pixel(image, point.x, point.y, color);
		point = next(point, rect, &d);
		i++;
	}
}
