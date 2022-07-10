/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 17:48:18 by ommohame          #+#    #+#             */
/*   Updated: 2022/07/10 16:11:39 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

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
