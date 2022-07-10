/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnum.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 21:59:01 by kamin             #+#    #+#             */
/*   Updated: 2021/12/15 00:23:10 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isnum(char *s)
{
	int	valid;
	int	i;

	i = 0;
	valid = 1;
	if ((s[i] == '-' && s[i + 1] == '\0') || s[i] == '\0')
		return (-1);
	else if (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i] && valid)
	{
		if (!ft_isdigit(s[i]))
			valid = -1;
		i++;
	}
	if (valid && (ft_isint(s) > 2147483647 || ft_isint(s) < -2147483648))
		valid = -1;
	return (valid);
}
