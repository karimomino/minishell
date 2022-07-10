/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 18:54:47 by ommohame          #+#    #+#             */
/*   Updated: 2022/07/09 20:05:33 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/quotes.h"
#include <stdio.h>

char	*quotes(char *str)
{
	ft_printf("%s\n", str);
	return (str);
}

int	main(void)
{
	char	str[100000];

 	scanf("%99[^\n]", str);
	quotes(str);
	return (EXIT_SUCCESS);
}
