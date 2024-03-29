/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@42abudhabi.ae>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 17:48:17 by ommohame          #+#    #+#             */
/*   Updated: 2022/09/17 20:26:13 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

int	cmd_cmd(char *str, t_token **token, t_cmd **cmd, t_line **line)
{
	t_token		*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (-1);
	new->i = 0;
	new->token = ft_strtrim(str, " ");
	new->org = ft_strdup(new->token);
	(*cmd)->nargs = 1;
	if ((*cmd)->type > 0)
		(*line)->nexec++;
	new->next = NULL;
	new->prev = NULL;
	*token = new;
	return (1);
}

int	cmd_arg(char *str, t_token **token, int i)
{
	t_token		*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (-1);
	new->i = i;
	new->next = NULL;
	new->token = ft_strdup(str);
	new->org = ft_strdup(new->token);
	while ((*token)->next)
		*token = (*token)->next;
	new->prev = (*token);
	(*token)->next = new;
	return (1);
}

int	split_args(char *str, t_token **token, t_cmd **cmd)
{
	int			i;
	char		*tmp;
	char		**new;
	t_token		*head;

	i = -1;
	tmp = ft_strtrim(str, " ");
	if (!tmp[0])
	{
		free(tmp);
		return (0);
	}
	new = ft_split_q(tmp, ' ');
	free(tmp);
	head = *token;
	while (new && new[++i])
	{
		if (cmd_arg(new[i], &(*token), i + 1) == -1)
			return (-1);
		*token = head;
	}
	(*cmd)->nargs = ft_strlenx2(new) + 1;
	free_2d(new);
	return (1);
}

int	cmd_red(char *str, t_redir **redir, t_cmd **cmd)
{
	int		i;
	char	*red;
	t_redir	*head;

	i = 0;
	while (i != -1)
	{
		red = get_redir(str, &i);
		if (!red)
			return (-1);
		if (redir_node(red, &(*redir), (*cmd)->nredir) == -1)
		{
			free(red);
			ft_putstr_fd(
				"minishell: syntax error near unexpected token \'newline\'\n", 2);
			return (-1);
		}
		if (*redir && !(*redir)->prev)
			head = *redir;
		*redir = head;
		(*cmd)->nredir++;
		free(red);
	}
	return (1);
}

int	last_cmd_node(char **str, t_cmd **cmd, t_line **line)
{
	int	ret;

	if (str[0])
	{
		ret = cmd_cmd(str[0], &(*cmd)->token, &(*cmd), &(*line));
		free(str[0]);
		if (ret == -1)
			return (-1);
	}
	if (str[1])
	{
		ret = split_args(str[1], &(*cmd)->token, &(*cmd));
		free(str[1]);
		if (ret == -1)
			return (-1);
	}
	if (str[2])
	{
		ret = cmd_red(str[2], &(*cmd)->redir, &(*cmd));
		free(str[2]);
		if (ret == -1)
			return (-1);
	}
	return (1);
}
