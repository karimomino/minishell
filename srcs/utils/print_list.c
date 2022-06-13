/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 23:04:42 by ommohame          #+#    #+#             */
/*   Updated: 2022/06/14 03:52:16 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

void	print_token(t_cmd cmd)
{
	while (cmd.token)
	{
		ft_printf("token[%u]: %s\n", cmd.token->i, cmd.token->token);
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
		ft_printf("cmd nargs: %u\n\n", line.cmd->nargs);
		while (line.cmd->cmd[x])
		{
			ft_printf("cmd[%u]: %s\n", x, line.cmd->cmd[x]);
			x++;
		}
		ft_printf("\n");
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
