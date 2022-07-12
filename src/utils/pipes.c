/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 20:18:22 by ommohame          #+#    #+#             */
/*   Updated: 2022/07/12 00:56:40 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

int	count_pipes(char *str)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '|' && str[i - 1] != '|' && str[i + 1] != '|')
			count++;
		else if (str[i] == '\'' || str[i] == '\"')
			i = skip_quotes(str, i);
		i++;
	}
	return (count);
}

int	count_cmds(char **cmd)
{
	int		i;
	int		count;
	char	*tmp;

	i = 0;
	count = 0;
	while (cmd[i])
	{
		tmp = ft_strtrim(cmd[i], " ");
		if (tmp[0] && tmp != NULL)
			count++;
		free(tmp);
		i++;
	}
	return (count);
}

int	check_pipes(char **cmd, char *str, t_line **line)
{
	int		p_count;
	int		c_count;

	p_count = count_pipes(str);
	c_count = count_cmds(cmd);
	if (p_count != c_count - 1 && c_count > 0)
		return (0);
	else if (c_count == 0 && p_count == 0)
		return (-1);
	else
	{
		(*line)->ncmds = c_count;
		(*line)->npipes = p_count;
		return (1);
	}
}
