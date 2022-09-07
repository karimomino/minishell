/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 23:04:42 by ommohame          #+#    #+#             */
/*   Updated: 2022/08/01 16:11:11 by ommohame         ###   ########.fr       */
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

void	print_redir(t_cmd cmd)
{
	while (cmd.redir)
	{
		ft_printf("redir[%d]: %s - std: %d type: %d\n",
			cmd.redir->i, cmd.redir->file, cmd.redir->fd, cmd.redir->type);
		cmd.redir = cmd.redir->next;
	}
}

void	print_cmd(t_line line)
{
	size_t	i;

	i = 0;
	while (line.cmd)
	{
		ft_printf("-------%u-------\n", i);
		ft_printf("cmd type: %u\n\n", line.cmd->type);
		ft_printf("cmd: %s\n", line.cmd->cmd);
		ft_printf("cmd exec: %s\n", line.cmd->exec);
		ft_printf("nargs: %d\n", line.cmd->nargs);
		ft_printf("nredir: %d\n", line.cmd->nredir);
		ft_printf("\n");
		print_token(*line.cmd);
		print_redir(*line.cmd);
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
