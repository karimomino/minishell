/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@42abudhabi.ae>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 19:26:47 by kamin             #+#    #+#             */
/*   Updated: 2021/10/15 00:13:43 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;

	if (start > ft_strlen(s))
	{
		sub = (char *)malloc(1 * sizeof(char));
		if (!sub)
			return (NULL);
		*sub = '\0';
		return (sub);
	}
	if (len > ft_strlen(s) || len > ((size_t)ft_strlen(s) - (size_t)start))
		len = (size_t)ft_strlen(s) - (size_t)start;
	sub = (char *)malloc((1 + len) * sizeof(char));
	if (sub == NULL)
		return (NULL);
	ft_strlcpy(sub, (s + start), len + 1);
	return (sub);
}
