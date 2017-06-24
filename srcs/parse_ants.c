/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ants.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnunnari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/15 18:31:29 by mnunnari          #+#    #+#             */
/*   Updated: 2017/06/24 22:05:33 by mnunnari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

uintmax_t	parse_ants(void)
{
	int			i;
	char		*line;
	uintmax_t	ants;

	while ((i = get_next_line(0, &line)) > 0)
	{
		if (!(line[0] == '#'))
			break ;
		free(line);
	}
	li_error(i == -1, "input error", NULL);
	while (*line == ' ')
		line++;
	li_error(!(*line) || ft_strequ(line, "0"), "ants must be more than 0", NULL);
	li_error(!ft_isuintmax(line), "ants not numeric or too many", NULL);
	ants = (ft_atouimax(line));
	free(line);
	return (ants);
}
