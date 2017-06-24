/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   li_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnunnari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 17:52:57 by mnunnari          #+#    #+#             */
/*   Updated: 2017/06/24 22:11:10 by mnunnari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		li_error(int cond, char *msg, t_hex *hex)
{
	(void)msg;
	if (!cond)
		return ;
	if (hex)
		free_hex(hex);
	ft_error("ERROR", 1);
}
