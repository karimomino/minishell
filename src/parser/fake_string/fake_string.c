/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fake_string.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@42abudhabi.ae>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 14:09:54 by ommohame          #+#    #+#             */
/*   Updated: 2022/09/17 20:22:39 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parser.h"

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
		if (to_expandd((*org)[i], (*org)[i + 1]) && (*org)[i] == '$')
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
	to_expandd('\0', '\0');
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

static void	loop_helper(t_line **line)
{
	t_token		*head_t;
	t_redir		*head_r;

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
		if ((*line)->cmd->redir->fd == 1
			|| ((*line)->cmd->redir->fd == 0 && (*line)->cmd->redir->type != 2))
			fake_string(&(*line)->cmd->redir->org,
				(*line)->exit, ft_strlen((*line)->cmd->redir->file));
		else
			(*line)->cmd->redir->org = ft_strdup((*line)->cmd->redir->file);
		(*line)->cmd->redir = (*line)->cmd->redir->next;
	}
	(*line)->cmd->token = head_t;
	(*line)->cmd->redir = head_r;
}

void	get_struct_fake_string(t_line **line)
{
	t_cmd		*head;

	head = (*line)->cmd;
	while ((*line)->cmd)
	{
		loop_helper(line);
		(*line)->cmd = (*line)->cmd->next;
	}
	(*line)->cmd = head;
}
