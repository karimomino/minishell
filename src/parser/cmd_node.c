/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 22:22:35 by ommohame          #+#    #+#             */
/*   Updated: 2022/07/22 15:08:20 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

int	cmd_node(char *str, t_cmd **cmd)
{
	t_cmd	*new;

	new = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (!new)
		return (-1);
	new->cmd = ft_strtrim(str, " ");
	new->nargs = 0;
	new->nredir = 0;
	new->type = 0;
	new->redir = NULL;
	new->token = NULL;
	new->next = NULL;
	if (!*cmd)
	{
		new->prev = NULL;
		*cmd = new;
	}
	else
	{
		while ((*cmd)->next)
			(*cmd) = (*cmd)->next;
		new->prev = (*cmd);
		(*cmd)->next = new;
	}
	return (1);
}

/*
* fill the linked lists
* - first fill the cmd linked list
* - gets the linked list of tokens and links it to the cmd
* --> wip - link the redirections
*/
int	cmds(char *str, t_line **line)
{
	char	**parsed;
	t_cmd	*head;

	head = (*line)->cmd;
	if (cmd_node(str, &(*line)->cmd) == -1)
		return (-1);
	parsed = parse(str);
	if (!parsed)
		return (-1);
	while ((*line)->cmd->next)
		(*line)->cmd = (*line)->cmd->next;
	if (last_cmd_node(parsed, &(*line)->cmd, &(*line)) == -1)
	{
		free(parsed);
		return (-1);
	}
	if (head)
		(*line)->cmd = head;
	free(parsed);
	return (1);
}
