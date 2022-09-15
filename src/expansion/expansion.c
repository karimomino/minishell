/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 17:19:33 by kamin             #+#    #+#             */
/*   Updated: 2022/09/15 18:07:03 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	expand(void *cmd, int *i, int flag, int exit)
{
	char		*var;
	char		*env;
	char		**string;
	char		*tmp;

	tmp = NULL;
	string = select_string(cmd, flag);
	if (to_expand((*string)[*i]))
	{
		var = get_variable_name(cmd, flag);
		env = getenv(var);
		if (env == NULL)
			env = ft_strdup("");
		if (!ft_strcmp(var, "?"))
			tmp = combined(*string, ft_itoa(exit), var);
		else if (flag && ft_strcmp(var, ""))
			tmp = combined(*string, env, var);
		else if (!flag && ft_strcmp(var, ""))
			tmp = combined(*string, env, var);
		if (!expansion_free(string, &tmp, &var, &env))
			return (0);
	}
	return (1);
}

static void	navigate_token(t_token **token, int exit)
{
	int	i;

	i = -1;
	while (*token)
	{
		i = -1;
		while ((*token) && (*token)->token[++i])
		{
			if (!expand(token, &i, 1, exit))
				i = -1;
		}
		if (!(*token)->token[i])
			to_expand((*token)->token[i]);
		(*token) = (*token)->next;
	}
}

static void	navigate_redir(t_redir **redir, int exit)
{
	int	i;

	i = -1;
	while (*redir)
	{
		i = -1;
		while ((*redir) && (*redir)->file[++i])
		{
			if (!expand(redir, &i, 1, exit))
				i = -1;
		}
		if (!(*redir)->file[i])
			to_expand((*redir)->file[i]);
		(*redir) = (*redir)->next;
	}
}

void	ft_expansion(t_line **line)
{
	t_cmd	*head;
	t_token	*head_t;
	t_redir	*head_r;

	head = (*line)->cmd;
	while ((*line)->cmd)
	{
		head_t = (*line)->cmd->token;
		head_r = (*line)->cmd->redir;
		navigate_token(&(*line)->cmd->token, (*line)->exit);
		navigate_redir(&(*line)->cmd->redir, (*line)->exit);
		((*line)->cmd->token) = head_t;
		((*line)->cmd->redir) = head_r;
		((*line)->cmd) = ((*line)->cmd)->next;
	}
	((*line)->cmd) = head;
}
