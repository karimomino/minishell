/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 22:49:28 by ommohame          #+#    #+#             */
/*   Updated: 2022/07/02 00:32:47 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

char	*get_quotes(char *str, size_t i);

char	**parse(char *str)
{
	int		i;
	char	**ret;

	i = 0;
	ret = (char **)ft_calloc(4, sizeof(char *));
	if (!ret)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == '>' || str[i] == '<')
		{
			if (define_redir(str, &ret[2], &i) == -1)
				return (NULL);
		}
		if (!str[i])
			break ;
		// else if (!ret[0])
		// 	define_cmd(str, &ret[0], &i)
		i++;
	}
	return (ret);
}
