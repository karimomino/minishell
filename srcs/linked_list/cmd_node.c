/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 22:22:35 by ommohame          #+#    #+#             */
/*   Updated: 2022/06/13 00:24:20 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

int	cmd_node(char *str, t_cmd **cmd)
{
	struct s_cmd	*new;
	struct s_cmd	*tmp;

	new = (struct s_cmd *)malloc(sizeof(struct s_cmd));
	if (!new)
		return (-1);
	new->cmd = ft_split(str, ' ');
	if (!new)
		return (-1);
	new->nargs = ft_strlenx2(new->cmd);
	new->next = NULL;
	if (!*cmd)
	{
		new->prev = NULL;
		*cmd = new;
	}
	else
	{
		tmp = *cmd;
		while (tmp->next)
		{
			new->prev = tmp;
			tmp = tmp->next;
		}
		tmp->next = new;
	}
	return (1);
}

