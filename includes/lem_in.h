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
}				t_hex;

void		free_hex(t_hex *hex);
void		li_error(int cond, char *msg, t_hex *hex);
uintmax_t	parse_ants();
char		*parse_rooms(t_hex *hex);
void		parse_links(t_hex *hex, char *line);
t_room		*get_room(t_hex *hex, char *name);
#endif
