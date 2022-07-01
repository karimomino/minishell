/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 17:48:18 by ommohame          #+#    #+#             */
/*   Updated: 2022/06/28 20:09:15 by ommohame         ###   ########.fr       */
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
	free (str);
}

void	free_nodes(t_line *line)
{
	t_cmd	*cmd;
	t_redir	*redir;
	t_token	*token;

	while (line->cmd)
	{
		if (line->cmd->token)
		{
			while (line->cmd->token)
			{
				token = line->cmd->token;
				line->cmd->token = line->cmd->token->next;
				free(token->token);
				free (token);
			}
		}
		if (line->cmd->redir)
		{
			while (line->cmd->redir)
			{
				redir = line->cmd->redir;
				line->cmd->redir = line->cmd->redir->next;
				free (redir->file);
				free (redir);
			}
		}
		cmd = line->cmd;
		line->cmd = line->cmd->next;
		free (cmd->cmd);
		free (cmd);
	}
}
