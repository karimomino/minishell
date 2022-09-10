/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 17:19:33 by kamin             #+#    #+#             */
/*   Updated: 2022/09/09 18:28:10 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	stopper_finder(char *tok)
{
	int	i;

	i = -1;
	while (!ft_strchr(" $?\'\"\0", tok[++i]))
		;
	if (i == 0)
		i++;
	return (i);
}

static char	*expand_helper(void *cmd, int flag)
{
	int		i;
	// int		tmp;
	char	*var;
	char	*string;
	// int		qm;

	i = 0;
	// tmp = 0;
	// qm = 0;
	if (flag)
		string = (*(t_token **)cmd)->token;
	else
		string = (*(t_redir **)cmd)->file;
	if (!string)
		return (NULL);
	while (string[i] != '\0' && string[i] != '$')
		i++;
	if (string[i] == '\0')
		return (NULL);
	// while (!ft_strchr(" $\"\'\0", string[i + tmp]))
	// 	tmp++;
	var = ft_substr(string + i + 1, 0, stopper_finder(string + i + 1));
	// if (string[i + tmp] != '?')
	// 	i--;
	// var = (char *)malloc(sizeof(char) * (tmp + 1));
	// tmp = 0;
	// if (string[i++] == '$')
	// {
	// 	while (!ft_strchr(" $\"\'\0", string[i]) && !qm)
	// 	{
	// 		if (string[i] == '?')
	// 			qm = 1;
	// 		var[tmp++] = string[i++];
	// 	}
	// 	var[tmp] = '\0';
	// }
	return (var);
}

static int	cpy_sec(int start, char **com, char *tok, char stopper)
{
	int	i;
	int	j;

	i = start;
	j = -1;
	while (tok[++j] != stopper)
	{
		if (i < 0)
			i = 0;
		(*com)[i] = (tok)[j];
		i++;
	}
	return (i);
}

static size_t	calc_malloc_size(char *tok, char *var, char *val)
{
	// int		i;
	// int		val;

	size_t	size;

	size = ft_strlen(tok) + ft_strlen(val) - ft_strlen(var);
	// i = -1;
	// val = -1;
	// size = 0;
	// while (tok[++i] != '$' && tok[i] != '\0')
	// 	size++;
	// while (var[++val] != '\0')
	// 	size++;
	// while (!ft_strchr(" ?\"\'\0",tok[++i]))
	// 	;
	// while ((size_t)i < ft_strlen(tok) && tok[++i] != '\0')
	// 	size++;
	return (size);
}

static char	*combined(char *tok, char *val, char *var)
{
	ssize_t		tok_i;
	int		i;
	char	*com;

	i = -1;
	tok_i = 0;
 	com = (char *)ft_calloc((calc_malloc_size(tok, var, val) + 1), 1);
	i = cpy_sec(i, &com, tok, '$');
	i = cpy_sec(i, &com, val, '\0');
	tok_i += ft_strlen(var) + i + 1 - ft_strlen(val);
	if (tok_i < (ssize_t)ft_strlen(tok))
		i = cpy_sec(i, &com, tok + tok_i , '\0');
	com[i] = '\0';
	return (com);
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

static void	expand(void *cmd, int *i, int flag)
{
	char		*var;
	char		*env;
	char		**string;
	char		*tmp;
	static int	dq;
	static int	sq;

	tmp = NULL;
	if (flag)
		string = (char **)&((*(t_token **)cmd)->token);
	else
		string = (char **)&((*(t_redir **)cmd)->file);
	if (!check_char((*string)[*i], &dq, &sq)
		&& (((*string)[*i] == '$' && dq == 1)
			|| ((*string)[*i] == '$' && sq == 0 && dq == 0)))
	{
		var = expand_helper(cmd, flag);
		env = getenv(var);
		// if (var && ft_strcmp(var, "?"))
		// 	free(var);
		if (!ft_strcmp(var, "?"))
			tmp = combined(*string, ft_itoa(t_infoo.retVal), var);
		if (env != NULL && flag)
			tmp = combined(*string, env, var);
		else if (env != NULL && !flag)
			(*(t_redir **)cmd)->file = combined(*string, env, var);
		if (tmp != NULL)
		{
			free((*(t_token **)cmd)->token);
			(*(t_token **)cmd)->token = ft_strdup(tmp);
		}
		if (var != NULL && env != NULL)
			free(tmp);
	}
}

void	ft_expansion(t_line **line)
{
	int		i;
	t_cmd	*head;
	t_token	*head_t;
	t_redir	*head_r;

	head = (*line)->cmd;
	while ((*line)->cmd)
	{
		head_t = (*line)->cmd->token;
		head_r = (*line)->cmd->redir;
		while ((*line)->cmd->token)
		{
			i = -1;
			while (((*line)->cmd->token) && ((*line)->cmd->token)->token[++i])
				expand(&((*line)->cmd->token), &i, 1);
			((*line)->cmd->token) = ((*line)->cmd->token)->next;
		}
		while ((*line)->cmd->redir && (*line)->cmd->redir->type != 2)
		{
			i = -1;
			while (((*line)->cmd->redir) && ((*line)->cmd->redir)->file[++i])
				expand(&((*line)->cmd->redir), &i, 0);
			((*line)->cmd->redir) = ((*line)->cmd->redir)->next;
		}
		((*line)->cmd->token) = head_t;
		((*line)->cmd->redir) = head_r;
		((*line)->cmd) = ((*line)->cmd)->next;
	}
	((*line)->cmd) = head;
}
