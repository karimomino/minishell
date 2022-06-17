/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 22:22:35 by ommohame          #+#    #+#             */
/*   Updated: 2022/06/18 02:00:39 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

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
	new->cmd = ft_strtrim(str, " ");
	if (!new)
		return (NULL);
	new->nargs = 2;
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
* get the tokens as a string
*	- if flag is 0 it looks for the command token which is gonna be the first one
*	- else it takes the rest of the line as a token except redirections
*/
char	*define_token(t_cmd *cmd, int flag)
{
	size_t	i;
	char	*token;

	i = 0;
	while (cmd->cmd[i] != ' ' && cmd->cmd[i])
		i++;
	if (flag == 0)
		token = ft_substr(cmd->cmd, 0, i);
	else
		token = ft_substr(cmd->cmd, i, ft_strlen(cmd->cmd) - i);
	if (!token)
		return (NULL);
	token = ft_strtrim(token, " ");
	token = qoutes(token);
	i = 0;
	if (flag == 0)
	{
		while (token[i])
		{
			token[i] = ft_tolower(token[i]);
			i++;
		}
		cmd->type = is_builtin(token);
	}
	return (token);
}

/*
* links all the tokens nodes
* return linked list of tokens
*/
t_token	*get_tokens(t_cmd *cmd)
{
	int			flag;
	size_t		i;
	char		*token;
	t_token		*head;

	i = 0;
	flag = 0;
	while (i < 2)
	{
		token = define_token(cmd, flag);
		cmd->token = new_token(&cmd->token, token, i);
		if (flag == 0)
			head = cmd->token;
		cmd->token = cmd->token->next;
		cmd->token = head;
		flag++;
		i++;
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
