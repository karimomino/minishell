/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@42abudhabi.ae>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 17:57:52 by kamin             #+#    #+#             */
/*   Updated: 2021/10/07 22:15:44 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	final;
	int	sign;

	final = 0;
	sign = 1;
	while (*str == '\t' || *str == '\v' || *str == '\f'
		|| *str == '\r' || *str == '\n' || *str == ' ')
		str++;
	if (*str == '-')
	{
		sign *= -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str > 47 && *str < 58)
	{
		final = (final * 10) + *str - 48;
		str++;
	}
	return (final * sign);
}
