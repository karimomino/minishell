/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 16:40:53 by ommohame          #+#    #+#             */
/*   Updated: 2022/07/05 17:36:56 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

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
		else if (str[i] != ' ' && str[i] != '>' && str[i] != '<')
		{
			if (!ret[0])
				get_cmd(str, &ret[0], &i);
			else
				get_args(str, &ret[1], &i);
		}
		i++;
	}
	return (ret);
}
