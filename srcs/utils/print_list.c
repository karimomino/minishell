/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 23:04:42 by ommohame          #+#    #+#             */
/*   Updated: 2022/06/13 19:21:37 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

void	print_token(t_cmd cmd)
{
	size_t	i;

	i = 0;
	while (cmd.token)
	{
		ft_printf("\n-------T-%u-T-------\n", i);
		ft_printf("|  %s  |\n", cmd.token->token);
		// if (cmd.token->prev->prev)
			// ft_printf("|  %s  |\n", cmd.token->prev->token);
		ft_printf("-------------------\n\n");
		cmd.token = cmd.token->next;
	}
}

void	print_cmd(t_line line)
{
	size_t	i;
	size_t	x;

	i = 0;
	while (line.cmd)
	{
		x = 0;
		ft_printf("-------%u-------\n", i);
		ft_printf("cmd nargs: %u\n", line.cmd->nargs);
		while (line.cmd->cmd[x])
		{
			ft_printf("| ");
			ft_printf("%s", line.cmd->cmd[x]);
			ft_printf(" |\n");
			x++;
		}
		print_token(*line.cmd);
		ft_printf("----------------\n\n");
		i++;
		line.cmd = line.cmd->next;
	}
}

/*
* prints the main struct - line -
*/
void	print_line(t_line *line)
{
	ft_printf("ncmds: %d\n", line->ncmds);
	ft_printf("nexec: %d\n", line->nexec);
	ft_printf("npipes: %d\n\n", line->npipes);
	print_cmd(*line);
}
