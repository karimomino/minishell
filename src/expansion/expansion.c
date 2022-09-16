/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@42abudhabi.ae>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 05:26:12 by kamin             #+#    #+#             */
/*   Updated: 2022/09/16 05:26:15 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	expand(void *cmd, int *i, int flag, int exit)
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
			tmp = combined(*string, ft_itoa(exit), var, *i);
		else if (flag && ft_strcmp(var, ""))
			tmp = combined(*string, env, var, *i);
		else if (!flag && ft_strcmp(var, ""))
			tmp = combined(*string, env, var, *i);
		*i += ft_strlen(env);
		expansion_free(string, &tmp, &var, &env);
	}
}

static void	navigate_token(t_token **token, int exit)
{
	int	i;

	i = -1;
	while (*token)
	{
		i = -1;
		while ((*token) && (*token)->token[++i])
			expand(token, &i, 1, exit);
		to_expand('\0');
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
			expand(redir, &i, 1, exit);
		to_expand('\0');
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
