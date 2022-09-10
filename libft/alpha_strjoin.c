/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alpha_strjoin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@42abudhabi.ae>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 21:16:14 by ommohame          #+#    #+#             */
/*   Updated: 2022/09/10 23:45:14 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*alpha_strjoin(size_t n, ...)
{
	size_t		i;
	char		*tmp;
	char		*tmp_two;
	char		*final;
	va_list		ap;

	i = 0;
	final = ft_strdup("");
	va_start(ap, n);
	while (i++ < n)
	{
		tmp_two = va_arg(ap, char *);
		if (tmp_two)
		{
			tmp = ft_strjoin(final, tmp_two);
			free(final);
			final = ft_strdup(tmp);
			if (!final)
				return (NULL);
			free(tmp);
		}
	}
	va_end(ap);
	return (final);
}
