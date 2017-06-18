/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_hex.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnunnari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/18 19:23:20 by mnunnari          #+#    #+#             */
/*   Updated: 2017/06/18 21:13:28 by mnunnari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GEN_HEX_H
# define GEN_HEX_H

# include "lem_in.h"
# include "mlx.h"

# define SW 800

typedef	struct	s_hook_param
{
	void		*mlx;
	void		*win;
	void		*imageptr;
	t_image		image;
}				t_hook_param;

void		draw_link(t_image image, t_link *link);
#endif
