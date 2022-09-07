/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 20:25:24 by kamin             #+#    #+#             */
/*   Updated: 2022/09/02 01:11:05 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_num_size(int n)
{
	int	size;

	size = 1;
	if (n < 0)
		size++;
	n /= 10;
	while (n)
	{
		n /= 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	char	*number;
	long	nbr;
	size_t	size;

	nbr = n;
	size = ft_num_size(n);
	number = (char *)malloc((size + 1) * sizeof(char));
	if (nbr == 0)
		number[0] = '0';
	if (nbr < 0)
	{
		number[0] = '-';
		nbr *= -1;
	}
	number[size] = '\0';
	while (nbr)
	{
		number[--size] = '0' + (nbr % 10);
		nbr /= 10;
	}
	return (number);
}
#include <stdio.h>

int main()
{
	int	a = (int)012;
	char *s = ft_itoa(a);
	printf("%s\n", s);
}