/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ants.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnunnari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/15 18:31:29 by mnunnari          #+#    #+#             */
/*   Updated: 2017/06/15 18:31:42 by mnunnari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

uintmax_t	parse_ants()
{
	int	i;
	char	*line;

	while((i = get_next_line(0, &line)) > 0)
		if (!(line[0] == '#'))
			break;
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
