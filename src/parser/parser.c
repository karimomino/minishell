/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 03:52:28 by ommohame          #+#    #+#             */
/*   Updated: 2022/08/24 00:42:39 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

t_line	*get_cmds(char **str, t_line *line)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (cmds(str[i], &line) == -1)
		{
			free_nodes(line);
			return (NULL);
		}
		i++;
	}
	ft_expansion(&line);
	return (line);
}

void	init_values(t_line *line)
{
	line->ncmds = 0;
	line->nexec = 0;
	line->npipes = 0;
	line->cmd = NULL;
}

/*
*	returns -1 if for an error
*/
int	parser_v3_0(char *str, t_line **line)
{
	int		ret;
	char	**cmd;

	cmd = ft_split_sc(str, '|');
	if (!cmd)
		return (-1);
	(*line) = (t_line *)ft_calloc(1, sizeof(t_line));
	if (!(*line))
		return (-1);
	init_values((*line));
	(*line) = get_cmds(cmd, (*line));
	if (!(*line))
	{
		free_2d(cmd);
		free((*line));
		return (-1);
	}
	ret = check_pipes(cmd, str, &(*line));
	free_2d(cmd);
	if (ret == 0 || ret == -1)
		return (ret);
	return (1);
}
