/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 16:40:53 by ommohame          #+#    #+#             */
/*   Updated: 2022/07/10 16:11:51 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

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
		if (!str[i++])
			return (ret);
	}
	return (ret);
}
