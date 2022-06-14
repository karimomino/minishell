/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 22:22:35 by ommohame          #+#    #+#             */
/*   Updated: 2022/06/14 04:59:35 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

/*
* creates the new command node
*	- cmd: is 2d array of the whole line
*/
t_cmd	*cmd_node(char *str, t_cmd **cmd)
{
	struct s_cmd	*new;
	struct s_cmd	*tmp;

	new = (struct s_cmd *)malloc(sizeof(struct s_cmd));
	if (!new)
		return (NULL);
	new->cmd = ft_split(str, ' ');
	if (!new)
		return (NULL);
	new->nargs = ft_strlenx2(new->cmd);
	new->next = NULL;
	if (!*cmd)
	{
		new->prev = NULL;
		*cmd = new;
	}
	else
	{
		tmp = *cmd;
		while (tmp->next)
			tmp = tmp->next;
		new->prev = tmp;
		tmp->next = new;
	}
	return (new);
}

/*
* creates one node for a new token
* returns the new node
*/
t_token	*new_token(t_token **token, char *str, int x)
{
	struct s_token	*new;
	struct s_token	*tmp;

	new = (struct s_token *)malloc(sizeof(struct s_token));
	if (!new)
		return (NULL);
	new->i = x;
	new->next = NULL;
	new->token = str;
	if (!*token)
		new->prev = NULL;
	else
	{
		tmp = *token;
		while (tmp->next)
			tmp = tmp->next;
		new->prev = tmp;
		tmp->next = new;
	}
	return (new);
}

/*
* links all the tokens nodes
* return linked list of tokens
*/
t_token	*get_tokens(t_cmd *cmd)
{
	size_t		x;
	t_token		*head;

	x = 0;
	cmd->token = new_token(&cmd->token, cmd->cmd[x], x);
	head = cmd->token;
	cmd->token = cmd->token->next;
	while (cmd->cmd[++x])
	{
		cmd->token = head;
		cmd->token = new_token(&cmd->token, cmd->cmd[x], x);
		cmd->token = cmd->token->next;
	}
	return (head);
}

/*
* fill the linked lists
* - first fill the cmd linked list
* - gets the linked list of tokens and links it to the cmd
* --> wip - link the redirections
*/
t_line	*cmds(char *str, t_line *line)
{
	t_cmd		*head;

	head = line->cmd;
	if (line->cmd)
		while (line->cmd->next)
			line->cmd = line->cmd->next;
	line->cmd = cmd_node(str, &line->cmd);
	line->cmd->token = get_tokens(line->cmd);
	if (head)
		line->cmd = head;
	return (line);
}
