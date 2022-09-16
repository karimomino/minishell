/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 22:22:35 by ommohame          #+#    #+#             */
/*   Updated: 2022/09/16 17:22:53 by ommohame         ###   ########.fr       */
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
	new->exec = NULL;
	new->token = NULL;
	new->next = NULL;
	if (!*cmd)
	{
		new->prev = NULL;
		*cmd = new;
		return (1);
	}
	while ((*cmd)->next)
		(*cmd) = (*cmd)->next;
	new->prev = (*cmd);
	(*cmd)->next = new;
	return (1);
}

int	cmds_thesecond(t_line **line, char **parsed)
{
	while ((*line)->cmd->next)
		(*line)->cmd = (*line)->cmd->next;
	if (last_cmd_node(parsed, &(*line)->cmd, &(*line)) == -1)
	{
		free(parsed);
		return (-1);
	}
	if ((*line)->cmd->token)
		(*line)->cmd->type = is_builtin((*line)->cmd->token->token);
	return (1);
}

/*
* fill the linked lists
* - first fill the cmd linked list
* - gets the linked list of tokens and links it to the cmd
*/
int	cmds(char *str, t_line **line)
{
	t_cmd	*head;
	char	**parsed;

	head = (*line)->cmd;
	if (cmd_node(str, &(*line)->cmd) == -1)
		return (-1);
	parsed = parse(str);
	// printf("parsed[2]: %s\n", parsed[2]);
	if (!parsed)
		return (-1);
	if (cmds_thesecond(line, parsed) != 1)
		return (-1);
	free(parsed);
	if (head)
		(*line)->cmd = head;
	return (1);
}
