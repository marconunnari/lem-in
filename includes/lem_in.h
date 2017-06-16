/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnunnari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/15 18:32:12 by mnunnari          #+#    #+#             */
/*   Updated: 2017/06/16 17:26:02 by mnunnari         ###   ########.fr       */
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

typedef struct	s_li_info
{
	t_room		*start;
	t_room		*end;
}				t_li_info;

typedef enum	e_cmd
{
	NONE, START, END
}				t_cmd;

void		free_hex(t_hex *hex);
void		li_error(int cond, char *msg, t_hex *hex);
uintmax_t	parse_ants();
char		*parse_rooms(t_hex *hex, t_li_info *li_info);
void		parse_links(t_hex *hex, char *line);
t_room		*get_room(t_hex *hex, char *name);
#endif
