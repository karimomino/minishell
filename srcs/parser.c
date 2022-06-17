/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 03:52:28 by ommohame          #+#    #+#             */
/*   Updated: 2022/06/18 02:08:16 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

char	**get_pipes(char *str, t_line *line)
{
	char	**array;

	array = ft_split(str, '|');
	if (!array)
		return (NULL);
	line->npipes = ft_strlenx2(array) - 1;
	line->ncmds = line->npipes + 1;
	return (array);
}

void	get_cmds(char **str, t_line *line)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		line = cmds(str[i], line);
		i++;
	}
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
t_line	*parser(char *str)
{
	char	**cmd;
	t_line	*line;

	line = (t_line *)malloc(sizeof(t_line));
	if (!line)
		return (NULL);
	init_values(line);
	cmd = ft_split_sc(str, '|');
	if (!cmd)
		return (NULL);
	get_cmds(cmd, line);
	return (line);
}

#include <stdio.h>

int	main(void)
{
	char	str[1000];
	t_line	*line;

	scanf("%99[^\n]", str);
	line = parser(str);
	if (!line)
		return (-1);
	print_line(line);
	return (1);
}
