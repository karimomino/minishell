/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@42abudhabi.ae>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 18:01:50 by kamin             #+#    #+#             */
/*   Updated: 2021/10/11 18:27:14 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	const char	*source;
	char		*destination;

	source = (const char *)src;
	destination = (char *)dst;
	if (dst == NULL && src == NULL && n > 0)
		return (NULL);
	while (n-- > 0)
	{
		*destination = *source;
		destination++;
		source++;
	}
	return (dst);
}
