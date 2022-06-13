/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 03:52:28 by ommohame          #+#    #+#             */
/*   Updated: 2022/06/13 05:35:12 by ommohame         ###   ########.fr       */
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
	// int		ret;
	size_t	i;
	size_t	x;

	i = 0;
	while (str[i])
	{
		x = 0;
		cmd_node(str[i], &line->cmd);
		while (line->cmd->cmd[x++])
			token_node(line->cmd->cmd[x], &line->cmd->token);
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
	char	**pip_str;
	t_line	*line;

	line = (t_line *)malloc(sizeof(t_line));
	if (!line)
		return (NULL);
	init_values(line);
	pip_str = get_pipes(str, line);
	if (!pip_str)
		return (NULL);
	get_cmds(pip_str, line);
	return (line);
}

int	main(void)
{
	t_line	*line;

	line = parser("echo hi | ls -la >> test");
	if (!line)
		return (-1);
	print_line(line);
	return (1);
}
