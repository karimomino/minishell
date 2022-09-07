/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@42abudhabi.ae>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 15:31:24 by kamin             #+#    #+#             */
/*   Updated: 2021/10/09 01:19:39 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	unsigned int	counter;
	unsigned int	tried;

	counter = 0;
	tried = 0;
	while (src[tried] != '\0')
		tried++;
	if (size > 0)
	{
		while (*src != 0 && counter < size - 1)
		{
			*dst = *src;
			dst++;
			src++;
			counter++;
		}
		*dst = '\0';
	}
	return (tried);
}
