/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlenx2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 23:02:24 by ommohame          #+#    #+#             */
/*   Updated: 2022/06/12 23:18:00 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

/*
* strlen but x2
*/
size_t	ft_strlenx2(char **str)
{
	size_t	x;

	x = 0;
	while (str[x])
		x++;
	return (x);
}
