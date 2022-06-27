/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 19:16:23 by ommohame          #+#    #+#             */
/*   Updated: 2022/06/23 22:02:58 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

char	*redir_file(char *str)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	while (str[i] == '>' || str[i] == '<')
		i++;
	while (str[i] == ' ')
		i++;
	if (str[i] == 34 || str[i] == 39)
	{
		j = skip_quotes(str, i);
		new = ft_substr(str, i + 1, j - i);
	}
	else
	{
		j = i;
		while (str[j] != ' ' && str[j] != 34 && str[j] != 39)
			j++;
		new = ft_substr(str, i, j);
	}
	return (new);
}

int	redir_type(char *str)
{
	int		i;
	int		in;
	int		out;

	i = 0;
	in = 0;
	out = 0;
	while (str[i] == '>')
	{
		if (str[i] == '<')
			in++;
		else if (str[i] == '>')
			out++;
		i++;
	}
	if (in <= 2 && out == 0)
		return (in);
	else if (out <= 2 && in == 0)
		return (out);
	else
		return (-1);
}

t_redir	*new_redir(t_redir **rd, char *str)
{
	struct s_redir	*new;
	struct s_redir	*tmp;

	new = (struct s_redir *)malloc(sizeof(struct s_token));
	if (!new)
		return (NULL);
	new->type = redir_type(str);
	if (ft_strncmp(str, "<", 1) == 0)
		new->fd = 0;
	else if (ft_strncmp(str, ">", 1) == 0)
		new->fd = 1;
	new->file = redir_file(str);
	new->next = NULL;
	if (!*rd)
		new->prev = NULL;
	else
	{
		tmp = *rd;
		while (tmp->next)
			tmp = tmp->next;
		new->prev = tmp;
		tmp->next = new;
	}
	return (new);
}

t_redir	*get_redir(t_cmd *cmd, char **str)
{
	size_t	i;
	t_redir	*head;

	i = 0;
	while (str[i])
	{
		ft_printf("i: %d\n", i);
		cmd->redir = new_redir(&cmd->redir, str[i]);
		if (cmd->redir->type == -1 || !cmd->redir->file)
			return (NULL);
		if (i == 1)
			head = cmd->redir;
		cmd->redir = cmd->redir->next;
		cmd->redir = head;
		i++;
	}
	return (head);
}