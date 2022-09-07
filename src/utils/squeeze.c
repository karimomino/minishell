/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   squeeze.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 03:35:45 by ommohame          #+#    #+#             */
/*   Updated: 2022/08/23 16:01:37 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

char	*squeeze_space(char *str)
{
	int		i;
	int		j;
	char	*tmp1;
	char	*tmp2;
	char	*new;

	i = 0;
	while ((str[i] == '>' || str[i] == '<') && str[i])
		i++;
	j = i;
	if (str[i] == ' ')
		i++;
	tmp1 = ft_substr(str, 0, i);
	tmp2 = ft_strtrim(str + j, " ");
	new = ft_strjoin(tmp1, tmp2);
	free(tmp1);
	free(tmp2);
	return (new);
}
