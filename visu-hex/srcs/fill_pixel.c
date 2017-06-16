/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_pixel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnunnari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 20:00:34 by mnunnari          #+#    #+#             */
/*   Updated: 2017/06/16 20:04:02 by mnunnari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu_hex.h"

void			fill_pixel(t_image image, int x, int y, int color)
{
	unsigned long long		i;

	i = (image.linesize * y) + 4 * x;
	image.img[i] = color & 0xFF;
	image.img[i + 1] = (color >> 8) & 0xFF;
	image.img[i + 2] = (color >> 16) & 0xFF;
	image.img[i + 3] = (color >> 24) & 0xFF;
}
