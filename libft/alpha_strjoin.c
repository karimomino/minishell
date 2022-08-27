/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alpha_strjoin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 21:16:14 by ommohame          #+#    #+#             */
/*   Updated: 2022/08/24 15:04:50 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*alpha_strjoin(size_t n, ...)
{
	size_t		i;
	char		*tmp;
	char		*final;
	va_list		ap;

	i = 0;
	final = ft_strdup("");
	va_start(ap, n);
	while (i++ < n)
	{
		tmp = ft_strjoin(final, va_arg(ap, char *));
		if (!tmp)
			return (NULL);
		free(final);
		final = ft_strdup(tmp);
		if (!final)
			return (NULL);
		free(tmp);
	}
	va_end(ap);
	return (final);
}
