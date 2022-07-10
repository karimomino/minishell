/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 23:52:05 by ommohame          #+#    #+#             */
/*   Updated: 2022/07/10 16:09:58 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

int	ft_putchar_len(char c, int len)
{
	write(1, &c, 1);
	len++;
	return (len);
}

int	ft_putstr_len(char *str, int len)
{
	if (!str)
		str = "(null)";
	while (*str)
	{
		len = ft_putchar_len(*str, len);
		str++;
	}
	return (len);
}
