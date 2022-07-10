/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 03:52:28 by ommohame          #+#    #+#             */
/*   Updated: 2022/07/11 02:05:24 by ommohame         ###   ########.fr       */
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
	char	**cmd;

	cmd = ft_split_sc(str, '|');
	if (!cmd)
		return (-1);
	(*line) = (t_line *)ft_calloc(1, sizeof(t_line));
	if (!(*line))
		return (-1);
	init_values((*line));
	if (check_pipes(cmd, str, &(*line)) == -1)
	{
		free_2d(cmd);
		free((*line));
		return (0);
	}
	(*line) = get_cmds(cmd, (*line));
	free_2d(cmd);
	if (!(*line))
	{
		free((*line));
		return (-1);
	}
	return (1);
}
