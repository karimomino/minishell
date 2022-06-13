/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 22:22:35 by ommohame          #+#    #+#             */
/*   Updated: 2022/06/13 05:34:44 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

// int	token_node_v2(t_cmd **tmp, size_t x)
// {
// 	struct s_token	*new;
// 	struct s_cmd	*tmp2;

// 	new = (struct s_token *)malloc(sizeof(struct s_token));
// 	if (!new)
// 		return (-1);
// 	tmp2 = *tmp;
// 	new->i = x;
// 	new->token = tmp2->cmd[x];
// 	new->next = NULL;
// 	if (!tmp2->token)
// 	{
// 		new->prev = NULL;
// 		tmp2->token = new;
// 	}
// 	else
// 	{
// 		while (tmp2->token->next)
// 			tmp2->token = tmp2->token->next;
// 		new->prev = tmp2->token;
// 		tmp2->token = new;
// 	}
// 	return (1);
// }

struct s_token	*token_node_v2(char *str, t_token *token, size_t x)
{
	struct s_token	*new;
	struct s_token	*tmp2;

	new = (struct s_token *)malloc(sizeof(struct s_token));
	if (!new)
		return (NULL);
	tmp2 = token;
	new->i = x;
	new->token = str;
	new->next = NULL;
	if (!tmp2)
	{
		new->prev = NULL;
		// tmp2 = new;
	}
	else
	{
		while (tmp2->next)
			tmp2 = tmp2->next;
		new->prev = tmp2;
		// tmp2 = new;
	}
	return (new);
}

int	token_node(char *str, t_token **token)
{
	size_t			x;
	struct s_token	*tmp;
	struct s_token	*new;

	x = 0;
	tmp = *token;

	new = (struct s_token *)malloc(sizeof(struct s_token));
	if (!new)
		return (-1);
	new->i = x;
	new->token = str;
	new->next = NULL;
	tmp = *token;
	if (!tmp)
	{
		new->prev = NULL;
		tmp = new;
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp = token_node_v2(str, tmp, x);
	}
	x++;
	return (1);
}

int	cmd_node(char *str, t_cmd **cmd)
{
	struct s_cmd	*new;
	struct s_cmd	*tmp;

	new = (struct s_cmd *)malloc(sizeof(struct s_cmd));
	if (!new)
		return (-1);
	new->cmd = ft_split(str, ' ');
	if (!new)
		return (-1);
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
	return (1);
}
