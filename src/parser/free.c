/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 17:48:18 by ommohame          #+#    #+#             */
/*   Updated: 2022/08/12 20:00:56 by ommohame         ###   ########.fr       */
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
		cmdd = line->cmd;
		if (line->cmd->token)
			free_tokens(line->cmd->token);
		if (line->cmd->redir)
			free_redirs(line->cmd->redir);
		line->cmd = line->cmd->next;
		free(cmdd->exec);
		free (cmdd->cmd);
		free (cmdd);
	}
}
