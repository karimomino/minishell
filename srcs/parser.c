/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 03:52:28 by ommohame          #+#    #+#             */
/*   Updated: 2022/07/05 19:00:05 by ommohame         ###   ########.fr       */
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
			return (NULL);
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

	line = (t_line *)ft_calloc(1, sizeof(t_line));
	if (!line)
		return (NULL);
	init_values(line);
	cmd = ft_split(str, '|');
	ft_printf("cmd[2]: %s\n", cmd[2]);
	if (!cmd)
		return (NULL);
	line = get_cmds(cmd, line);
	free_2d(cmd);
	return (line);
}

#include <stdio.h>

int	main(void)
{
	char	str[1000];
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
