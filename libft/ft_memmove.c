/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@42abudhabi.ae>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 07:58:53 by kamin             #+#    #+#             */
/*   Updated: 2021/10/16 01:50:21 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	const char	*source;
	char		*destination;
	size_t		i;

	destination = (char *)dst;
	source = (const char *)src;
	i = 0;
	if ((!dst && !src))
		return (NULL);
	if (source < destination)
	{
		while (len-- > 0)
			destination[len] = source[len];
	}
	else
	{
		i = 0;
		while (i < len)
		{
			destination[i] = source[i];
			i++;
		}
	}
	return (dst);
}
