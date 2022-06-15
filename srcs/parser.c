/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 03:52:28 by ommohame          #+#    #+#             */
/*   Updated: 2022/06/15 23:18:41 by ommohame         ###   ########.fr       */
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
	char	*tmp;

	i = 0;
	while (str[i])
	{
		tmp = ft_strdup(str[i++]);
		tmp = ft_strjoin(tmp, " ");
		while (str[i] && ft_strncmp(str[i], "|", 1))
		{
			tmp = ft_strjoin(tmp, str[i++]);
			tmp = ft_strjoin(tmp, " ");
		}
		line = cmds(tmp, line);
		free(tmp);
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
	char	**splitq;
	t_line	*line;

	line = (t_line *)malloc(sizeof(t_line));
	if (!line)
		return (NULL);
	init_values(line);
	splitq = ft_splitq(str);
	if (!splitq)
		return (NULL);
	get_cmds(splitq, line);
	return (line);
}

int	main(int ac, char **av)
{
	// t_line	*line;
	(void)ac;
	(void)av;

	// ft_printf("%s\n", av[1]);
	char	*str;
	char **new = ft_splitq(av[1]);
	for (int i = 0; new[i]; i++)
	{
		str = ft_strdup(new[i]);
		// if (str[0] == '"')
		// 	str = ft_strtrim(str, "\"");
		// else if (str[0] == '\'')
		// 	str = ft_strtrim(str, "'");
		if (new[i + 1])
			str = ft_strjoin(str, " ");
		ft_printf("%s", str);
	}
	// line = parser("\"one\" is \"less\" \'\"than\"  \'five\'\' ");
	// if (!line)
	// 	return (-1);
	// print_line(line);1
	return (1);
}
