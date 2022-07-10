/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@42abudhabi.ae>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 15:32:30 by kamin             #+#    #+#             */
/*   Updated: 2021/10/09 05:30:42 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i_hay;
	size_t	i_needle;
	int		match;

	i_hay = 0;
	i_needle = 0;
	match = 0;
	if (!needle[i_hay])
		return ((char *)haystack);
	while (haystack[i_hay] && match == 0 && i_hay < len)
	{
		match = 1;
		i_needle = 0;
		while (needle[i_needle] && match == 1 && (i_needle + i_hay) < len)
		{
			if (haystack[i_hay + i_needle] == needle[i_needle])
				i_needle++;
			else
				match = 0;
		}
		i_hay++;
	}
	if (needle[i_needle])
		return (NULL);
	return ((char *)haystack + i_hay - 1);
}
