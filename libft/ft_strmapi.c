/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@42abudhabi.ae>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 22:43:43 by kamin             #+#    #+#             */
/*   Updated: 2021/10/14 04:09:15 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*s_f;
	int		counter;

	s_f = ft_strdup(s);
	counter = 0;
	if (!s || !f || !s_f)
		return (NULL);
	while (*(s_f + counter))
	{
		*(s_f + counter) = f(counter, *(s_f + counter));
		counter++;
	}
	return (s_f);
}
