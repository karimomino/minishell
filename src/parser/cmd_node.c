/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 22:22:35 by ommohame          #+#    #+#             */
/*   Updated: 2022/08/01 16:35:51 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	cmd_exec(t_cmd **cmd, char **str)
{
	char	*tmp;

	if (str[0] && str[1])
	{
		tmp = ft_strjoin(str[0], " ");
		if (!tmp)
			return (-1);
		(*cmd)->exec = ft_strjoin(tmp, str[1]);
		free(tmp);
	}
	else if (str[0])
		(*cmd)->exec = ft_strdup(str[0]);
	if (!(*cmd)->exec)
		return (-1);
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
	t_cmd	*head;
	char	**parsed;

	head = (*line)->cmd;
	if (cmd_node(str, &(*line)->cmd) == -1)
		return (-1);
	parsed = parse(str);
	if (!parsed)
		return (-1);
	while ((*line)->cmd->next)
		(*line)->cmd = (*line)->cmd->next;
	if (cmd_exec(&(*line)->cmd, parsed) == -1)
	{
		free_2d(parsed);
		return (-1);
	}
	if (last_cmd_node(parsed, &(*line)->cmd, &(*line)) == -1)
	{
		free(parsed);
		return (-1);
	}
	ft_expansion(&*line);
	(*line)->cmd->type = is_builtin((*line)->cmd->token->token);
	if (head)
		(*line)->cmd = head;
	free(parsed);
	return (1);
}
