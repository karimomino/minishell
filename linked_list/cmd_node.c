/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 22:22:35 by ommohame          #+#    #+#             */
/*   Updated: 2022/07/02 00:40:28 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

int	cmd_node(char *str, t_cmd **cmd)
{
	t_cmd	*new;

	new = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (!new)
		return (-1);
	new->cmd = ft_strtrim(str, " ");
	new->nargs = 0;
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

int	cmd_red(char *str, t_redir **redir)
{
	int		i;
	int		f;
	char	*red;
	t_redir	*head;

	i = 0;
	f = 0;
	if (str)
	{
		while (i != -1)
		{
			red = get_redir(str, &i);
			if (redir_node(str, &(*redir)) == -1)
				return (-1);
			if (f++ == 0)
				head = *redir;
			*redir = head;
			free(red);
		}
	}
	return (1);
}

int	last_cmd_node(char **str, t_cmd **cmd)
{
	while ((*cmd)->next)
		(*cmd) = (*cmd)->next;
	if (str[2])
	{
		if (cmd_red(str[2], &(*cmd)->redir) == -1)
			return (-1);
		free(str[2]);
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
	last_cmd_node(parsed, &(*line)->cmd);
	if (head)
		(*line)->cmd = head;
	free(parsed);
	return (1);
}
