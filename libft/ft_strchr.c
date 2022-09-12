/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@42abudhabi.ae>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 02:22:29 by kamin             #+#    #+#             */
/*   Updated: 2022/09/12 21:16:53 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		len;
	char	*string;

	len = ft_strlen(s) + 1;
	string = (char *)s;
	if (c < 0)
		return (string);
	while (len-- > 0)
	{
		if (*string == c)
			return (string);
		string++;
	}
	return (NULL);
}
