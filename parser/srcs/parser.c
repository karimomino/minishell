/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 03:52:28 by ommohame          #+#    #+#             */
/*   Updated: 2022/07/08 22:05:02 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

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
t_line	*parser_v3_0(char *str)
{
	char	**cmd;
	t_line	*line;

	cmd = ft_split_sc(str, '|');
	if (!cmd)
		return (NULL);
	line = (t_line *)ft_calloc(1, sizeof(t_line));
	if (!line)
		return (NULL);
	init_values(line);
	if (check_pipes(cmd, str, &line) == -1)
	{
		free_2d(cmd);
		free(line);
		return (NULL);
	}
	line = get_cmds(cmd, line);
	free_2d(cmd);
	if (!line)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

#include <stdio.h>

int	main(void)
{
	char	str[100000];
	t_line	*line;

 	scanf("%99[^\n]", str);
	line = parser_v3_0(str);
	if (!line)
		return (EXIT_FAILURE);
	print_line(line);
	free_nodes(line);
	free(line);
	return (EXIT_SUCCESS);
}
