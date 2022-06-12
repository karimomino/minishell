/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 03:52:28 by ommohame          #+#    #+#             */
/*   Updated: 2022/06/12 15:35:52 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexar.h"

int	analyze_line(char *str, t_line *line)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '|')
		{
			line->ncmds++;
			line->npipes++;
		}
		else if (str[i] == ' ')
			line->nargs++;
		i++;
	}
	return (1);
}

void	init_values(t_line *line)
{
	line->ncmds = 0;
	line->nargs = 0;
	line->npipes = 0;
	line->infile = NULL;
	line->outfile = NULL;
	line->errfile = NULL;
	line->cmd = NULL;
}

/*
*	returns -1 if for an error
*/
t_line	*lexar(char *str)
{
	t_line	*line;

	line = (t_line *)malloc(sizeof(t_line));
	init_values(line);
	analyze_line(str, line);

	return (line);
}

int	main(void)
{
	t_line	*line;

	line = lexar("echo hi | ls -la");
	print_line(line);
}
