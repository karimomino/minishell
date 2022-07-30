/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 17:19:33 by kamin             #+#    #+#             */
/*   Updated: 2022/07/30 15:34:22 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*expand_helper(void *cmd, int flag)
{
	int		i;
	int		tmp;
	char	*var;
	char	**string;

	i = 0;
	tmp = 0;
	if (flag)
		string = (char **)&((*(t_token **)cmd)->token);
	else
		string = (char **)&((*(t_redir **)cmd)->file);
	while ((*string) && (*string)[i] != '\0' && (*string)[i] != '$')
		i++;
	if ((*string)[i++] == '$')
	{
		while (!ft_strchr(" $\"\'\0", (*string)[i + tmp]))
			tmp++;
	}
	i--;
	var = (char *)malloc(sizeof(char) * tmp);
	tmp = 0;
	if ((*string)[i++] == '$')
	{
		while (!ft_strchr(" $\"\'\0", (*string)[i]))
			var[tmp++] = (*string)[i++];
		var[tmp] = '\0';
	}
	return (var);
}

static int	norm_comb(int tok_size, int i, char **com, char *tok)
{
	while (tok_size < i)
	{
		(*com)[tok_size] = (tok)[tok_size];
		tok_size++;
	}
	return (tok_size);
}

static char	*combined(char **tok, char *var)
{
	int		tok_size;
	int		var_size;
	int		i;
	int		s;
	char	*com;

	i = 0;
	s = 0;
	var_size = ft_strlen(var);
	while ((*tok)[i] != '$')
		i++;
	i++;
	while (!ft_strchr(" $\"\'\0", (*tok)[i + s]))
		s++;
	com = (char *)malloc(ft_strlen((*tok)) + var_size + 1);
	i--;
	tok_size = norm_comb(0, i, &com, (*tok));
	i = 0;
	while (tok_size < tok_size + var_size && !ft_strchr(" \"\'\0", var[i]))
		com[tok_size++] = var[i++];
	var_size = tok_size - i + s + 1;
	while ((*tok)[var_size] != '\0')
		com[tok_size++] = (*tok)[var_size++];
	com[tok_size] = '\0';
	return (com);
}

static void	expand(void *cmd, int flag)
{
	char	*var;
	char	*env;

	var = expand_helper(cmd, flag);
	env = getenv(var);
	if (var)
		free(var);
	if (env != NULL && flag)
		(*(t_token **)cmd)->token = combined(& (*(t_token **)cmd)->token, env);
	else if (env != NULL && !flag)
		(*(t_redir **)cmd)->file = combined(&(*(t_redir **)cmd)->file, env);
}

static int	check_char(char c, int *dq, int *sq)
{
	int	ret;

	ret = 0;
	if (c == '"')
	{
		(*dq)++;
		if (*dq > 1)
			*dq = 0;
		ret = 1;
	}
	else if (c == '\'')
	{
		(*sq)++;
		if (*sq > 1)
			*sq = 0;
		ret = 1;
	}
	return (ret);
}

static void	check_expand_t(void *c, int *i, int *dq, int *sq, int flag)
{
	t_token	**t;
	t_redir	**r;

	if (flag)
	{
		t = (t_token **)c;
		if (!check_char((*t)->token[*i], dq, sq)
			&& (((*t)->token[*i] == '$' && *dq == 1)
				|| ((*t)->token[*i] == '$' && *sq == 0 && *dq == 0)))
			expand(t, flag);
	}
	else
	{
		r = (t_redir **)c;
		if (!check_char((*r)->file[*i], dq, sq)
			&& (((*r)->file[*i] == '$' && *dq == 1)
				|| ((*r)->file[*i] == '$' && *sq == 0 && *dq == 0)))
			expand(r, flag);
	}
}

void	ft_expansion(t_line **line)
{
	int		sq;
	int		dq;
	int		i;
	t_cmd	*head;
	t_token	*head_t;
	t_redir	*head_r;

	head = (*line)->cmd;
	sq = 0;
	dq = 0;
	while ((*line)->cmd)
	{
		head_t = (*line)->cmd->token;
		head_r = (*line)->cmd->redir;
		while ((*line)->cmd->token)
		{
			i = -1;
			while (((*line)->cmd->token) && ((*line)->cmd->token)->token[++i])
				check_expand_t(&((*line)->cmd->token), &i, &dq, &sq, 1);
			((*line)->cmd->token) = ((*line)->cmd->token)->next;
		}
		while ((*line)->cmd->redir)
		{
			i = -1;
			while (((*line)->cmd->redir) && ((*line)->cmd->redir)->file[++i])
				check_expand_t(&((*line)->cmd->redir), &i, &dq, &sq, 0);
			((*line)->cmd->redir) = ((*line)->cmd->redir)->next;
		}
		((*line)->cmd->token) = head_t;
		((*line)->cmd->redir) = head_r;
		((*line)->cmd) = ((*line)->cmd)->next;
	}
	((*line)->cmd) = head;
}
