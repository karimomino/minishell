/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 17:48:18 by ommohame          #+#    #+#             */
/*   Updated: 2022/09/13 22:09:25 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

void	free_2d(char **str)
{
	size_t	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			free (str[i]);
			i++;
		}
	}
	free (str);
}

void	free_tokens(t_token *token)
{
	t_token	*tokenn;

	while (token)
	{
		tokenn = token;
		token = token->next;
		free(tokenn->token);
		free (tokenn);
	}
}

void	free_redirs(t_redir *redir)
{
	t_redir	*redirr;

	while (redir)
	{
		redirr = redir;
		redir = redir->next;
		free (redirr->file);
		free (redirr);
	}
}

void	free_nodes(t_line *line)
{
	t_cmd	*cmdd;

	while (line->cmd)
	{
		if (line->cmd)
		{
			cmdd = line->cmd;
			if (line->cmd->token)
				free_tokens(line->cmd->token);
			if (line->cmd->redir)
				free_redirs(line->cmd->redir);
			line->cmd = line->cmd->next;
			free_2d(cmdd->exec);
			free (cmdd->cmd);
			free (cmdd);
		}
	}
}

int	free_cmd(t_cmd *cmd)
{
	t_token		*tokenn;
	t_cmd		*cmdd;

	while (cmd->token)
	{
		tokenn = cmd->token;
		cmd->token = cmd->token->next;
		free(tokenn->token);
		free(tokenn);
	}
	cmdd = cmd;
	cmd = cmd->next;
	free_2d(cmdd->exec);
	free(cmdd->cmd);
	free(cmdd);
	return (1);
}
