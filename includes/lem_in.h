/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnunnari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/15 18:32:12 by mnunnari          #+#    #+#             */
/*   Updated: 2017/06/15 19:42:04 by mnunnari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"

typedef struct	s_room
{
	char		*name;
	int			x;
	int			y;
	t_list		*ants;
}				t_room;

typedef struct	s_link
{
	t_room		*room1;
	t_room		*room2;
	uintmax_t	weight;
}				t_link;

typedef struct	s_hex
{
	t_list		*rooms;
	t_list		*links;
	t_room		start;
	t_room		end;
}				t_hex;

uintmax_t	parse_ants();
void		li_error(int cond, char *msg);
#endif
