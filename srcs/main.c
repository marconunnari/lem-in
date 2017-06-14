/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnunnari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/14 20:37:42 by mnunnari          #+#    #+#             */
/*   Updated: 2017/06/14 20:40:58 by mnunnari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		li_error(int cond, char *msg)
{
	if (cond)
		ft_error(msg, 1);
}

uintmax_t	parse_ants()
{
	int	i;
	char	*line;

	i = get_next_line(0, &line);
	li_error(i == -1, "input error");
	while (*line == ' ')
		line++;
	i = 0;
	while (line[i])
	{
		li_error(!ft_isdigit(line[i]), "forbidden character in the number of ants");
		i++;
	}
	li_error(i > 20, "number of ants too big");
	if (i == 20)
		li_error(ft_strcmp(line,"18446744073709551615") > 0, "number of ants too big");
	return (ft_atouimax(line));
}

int			main(int argc, char **argv)
{
	uintmax_t	ants;

	(void)argv;
	li_error(argc > 1, "too many arguments");
	ants = parse_ants();
	ft_printfnl("ants: %ju", ants);
}
