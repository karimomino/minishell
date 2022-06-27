/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 17:48:18 by ommohame          #+#    #+#             */
/*   Updated: 2022/06/26 00:00:22 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

void	free_2d(char **str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		free (str[i]);
		i++;
	}
	ft_printf("CHECK_1\n");
	free (str);
	ft_printf("CHECK_2\n");
}

void	free_nodes(t_line *line)
{
	t_cmd	*cmd;
	t_redir	*redir;
	t_token	*token;

	while (line->cmd)
	{
		while (line->cmd->token)
		{
			token = line->cmd->token;
			line->cmd->token = line->cmd->token->next;
			free(token->token);
			free (token);
		}
		while (line->cmd->redir)
		{
			redir = line->cmd->redir;
			line->cmd->redir = line->cmd->redir->next;
			free (redir->file);
			free (redir);
		}
		cmd = line->cmd;
		line->cmd = line->cmd->next;
		free (cmd->cmd);
		free (cmd);
	}
}
