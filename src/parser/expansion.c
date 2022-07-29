/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 17:19:33 by kamin             #+#    #+#             */
/*   Updated: 2022/07/27 13:56:04 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*expand_helper(t_token **cmd)
{
	int		i;
	int		tmp;
	char	*var;

	i = 0;
	tmp = 0;
	while ((*cmd)->token && (*cmd)->token[i] != '\0' && (*cmd)->token[i] != '$')
		i++;
	if ((*cmd)->token[i++] == '$')
	{
		while (!ft_strchr(" $\"\'\0", (*cmd)->token[i + tmp]))
			tmp++;
	}
	i--;
	var = (char *)malloc(sizeof(char) * tmp);
	tmp = 0;
	if ((*cmd)->token[i++] == '$')
	{
		while (!ft_strchr(" $\"\'\0", (*cmd)->token[i]))
			var[tmp++] = (*cmd)->token[i++];
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

static void	expand(t_token **cmd)
{
	char	*var;
	char	*env;

	var = expand_helper(cmd);
	env = getenv(var);
	if (var)
		free(var);
	if (env != NULL)
		(*cmd)->token = combined(&(*cmd)->token, env);
}

void	ft_expansion(t_line **line)
{
	int		sq;
	int		dq;
	int		i;
	t_token	**token;
	t_cmd	**cmd;
	t_cmd	*head;
	t_token	*head_t;

	head = (*line)->cmd;
	head_t = head->token;
	cmd = &(*line)->cmd;
	sq = 0;
	dq = 0;
	while (*cmd)
	{
		token = &(*cmd)->token;
		*token = (*token)->next;
		while (*token)
		{
			i = -1;
			while ((*token) && (*token)->token[++i])
			{
				if ((*token)->token[i] == '"')
				{
					dq++;
					if (dq > 1)
						dq = 0;
				}
				else if (((*token)->token[i] == '$' && dq == 1)
					|| ((*token)->token[i] == '$' && sq == 0 && dq == 0))
					expand(token);
			}
				(*token) = (*token)->next;
		}
		(*cmd) = (*cmd)->next;
	}
	(*cmd) = head;
	(*token) = head_t;
}
