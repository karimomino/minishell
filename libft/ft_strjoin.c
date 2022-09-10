/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@42abudhabi.ae>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 20:06:40 by kamin             #+#    #+#             */
/*   Updated: 2022/09/10 23:38:07 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joined;
	int		len1;
	int		len2;

	if (!s1 || !s2)
		return(NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	joined = (char *)malloc(len1 + len2 + 1);
	if (joined == NULL)
		return (NULL);
	while (*s1)
	{
		*joined = *s1;
		joined++;
		s1++;
	}
	while (*s2)
	{
		*joined = *s2;
		joined++;
		s2++;
	}
	*joined = '\0';
	return (joined - (len1 + len2));
}
