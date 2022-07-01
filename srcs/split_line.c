/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 22:49:28 by ommohame          #+#    #+#             */
/*   Updated: 2022/06/30 01:23:17 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

char	*get_quotes(char *str, size_t i);

char	**parse(char *str)
{
	int		i;
	char	**ret;

	i = 0;
	ret = (char **)malloc(sizeof(char *) * 4);
	if (!ret)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '>' || str[i] == '<')
		{
			if (define_redir(str, &ret[2], &i) == -1)
				return (NULL);
		}
		// else if (!ret[0])
		// 	define_cmd(str, &ret[0], &i)
		i++;
	}
	ret[3] = NULL;
	return (ret);
}
