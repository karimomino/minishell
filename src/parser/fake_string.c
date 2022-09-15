/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fake_string.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 14:09:54 by ommohame          #+#    #+#             */
/*   Updated: 2022/09/15 18:31:22 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

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

static char	*expand_helper(char *string)
{
	int		i;
	char	*var;

	i = 0;
	if (!string)
		return (NULL);
	while (string[i] != '\0' && string[i] != '$')
		i++;
	if (string[i] == '\0')
		return (NULL);
	var = ft_substr(string + i + 1, 0, stopper_finder(string + i + 1));
	return (var);
}

char	*get_expanded_value(char *var, int exit_code)
{
	if (!ft_strcmp(var, "?"))
		return (ft_itoa(exit_code));
	else
		return (getenv(var));
}

void	replace_fake_string_exp(char **fake, char *exp, size_t *j)
{
	size_t	x;

	x = ft_strlen(exp);
	while (x > 0)
	{
		(*fake)[(*j)++] = '\0';
		x--;
	}
}

void	replace_fake_string_norm(char **fake, char *org, size_t *i, size_t *j)
{
	(*fake)[*j] = org[*i];
	(*i)++;
	(*j)++;
}

void	get_fake_exp_string(char **org, char **fake, int exit_code)
{
	size_t	i;
	size_t	j;
	char	*var;
	char	*tmp;
	char	*exp;

	i = 0;
	j = 0;
	while ((*org)[i])
	{
		if (to_expand((*org)[i]) && (*org)[i] == '$')
		{
			tmp = ((*org)) + i;
			var = expand_helper(tmp);
			exp = get_expanded_value(var, exit_code);
			i++;
			if (exp)
				replace_fake_string_exp(fake, exp, &j);
			i += ft_strlen(var);
		}
		else
			replace_fake_string_norm(fake, *org, &i, &j);
	}
	(*fake)[j] = '\0';
}

void	fake_string(char **org, int exit_code, size_t len)
{
	char	*fake;

	fake = (char *)ft_calloc((len + 1), sizeof(char));
	get_fake_exp_string(org, &fake, exit_code);
	free(*org);
	*org = fake;
}

void	get_struct_fake_string(t_line **line)
{
	t_cmd		*head;
	t_token		*head_t;
	t_redir		*head_r;

	head = (*line)->cmd;
	while ((*line)->cmd)
	{
		head_t = (*line)->cmd->token;
		head_r = (*line)->cmd->redir;
		while ((*line)->cmd->token)
		{
			fake_string(&(*line)->cmd->token->org,
				(*line)->exit, ft_strlen((*line)->cmd->token->token));
			(*line)->cmd->token = (*line)->cmd->token->next;
		}
		while ((*line)->cmd->redir)
		{
			fake_string(&(*line)->cmd->redir->org,
				(*line)->exit, ft_strlen((*line)->cmd->redir->file));
			(*line)->cmd->redir = (*line)->cmd->redir->next;
		}
		(*line)->cmd->token = head_t;
		(*line)->cmd->redir = head_r;
		(*line)->cmd = (*line)->cmd->next;
	}
	(*line)->cmd = head;
}
