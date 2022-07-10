/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 22:22:35 by ommohame          #+#    #+#             */
/*   Updated: 2022/07/10 18:08:23 by kamin            ###   ########.fr       */
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
	new->nargs = 2;
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

int	cmd_cmd(char *str, t_token **token, t_cmd **cmd, t_line **line)
{
	int			i;
	t_token		*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (-1);
	new->i = 0;
	new->token = ft_strtrim(str, " ");
	i = 0;
	while (new->token[i])
	{
		new->token[i] = ft_tolower(new->token[i]);
		i++;
	}
	(*cmd)->type = is_builtin(new->token);
	if ((*cmd)->type > 0)
		(*line)->nexec++;
	new->next = NULL;
	new->prev = NULL;
	*token = new;
	return (1);
}

int	cmd_arg(char *str, t_token **token)
{
	t_token		*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (-1);
	new->i = 1;
	new->next = NULL;
	new->prev = *token;
	new->token = ft_strdup(str);
	(*token)->next = new;
	return (1);
}

int	cmd_red(char *str, t_redir **redir)
{
	int		i;
	int		f;
	char	*red;
	t_redir	*head;

	i = 0;
	f = 0;
	while (i != -1)
	{
		red = get_redir(str, &i);
		if (!red)
			return (-1);
		if (redir_node(red, &(*redir)) == -1)
		{
			free(red);
			ft_printf(
				"minishell: syntax error near unexpected token \'newline\'\n");
			return (-1);
		}
		if (f++ == 0)
			head = *redir;
		*redir = head;
		free(red);
	}
	return (1);
}

int	last_cmd_node(char **str, t_cmd **cmd, t_line **line)
{
	int	ret;

	while ((*cmd)->next)
		(*cmd) = (*cmd)->next;
	if (str[0])
	{
		ret = cmd_cmd(str[0], &(*cmd)->token, &(*cmd), &(*line));
		free(str[0]);
		if (ret == -1)
			return (-1);
	}
	if (str[1])
	{
		ret = cmd_arg(str[1], &(*cmd)->token);
		free(str[1]);
		if (ret == -1)
			return (-1);
	}
	if (str[2])
	{
		ret = cmd_red(str[2], &(*cmd)->redir);
		free(str[2]);
		if (ret == -1)
			return (-1);
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
