/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 22:29:44 by ommohame          #+#    #+#             */
/*   Updated: 2022/07/20 22:36:55 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

int	init_redir_node(char *str, t_redir **new, size_t i)
{
	(*new) = (t_redir *)malloc(sizeof(t_redir));
	if (!(*new))
		return (-1);
	(*new)->fd = redir_what(str);
	(*new)->type = redir_type(str);
	(*new)->file = ft_strtrim(str, "> <");
	(*new)->next = NULL;
	(*new)->i = i;
	return (1);
}

int	redir_node(char *str, t_redir **redir, size_t i)
{
	t_redir	*new;

	if (init_redir_node(str, &new, i) == -1 || new->fd == -1
		|| new->type == -1 || ft_strncmp(new->file, "", 1) == 0)
	{
		if (new->file)
			free(new->file);
		if (new)
			free(new);
		return (-1);
	}
	if (!*redir)
	{
		new->prev = NULL;
		*redir = new;
		return (1);
	}
	while ((*redir)->next)
		(*redir) = (*redir)->next;
	new->prev = (*redir);
	(*redir)->next = new;
	return (1);
}
