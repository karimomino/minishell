/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 03:28:06 by ommohame          #+#    #+#             */
/*   Updated: 2022/07/11 15:39:42 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	history_node(char *str, t_history **history, int i)
{
	t_history	*new;

	new = (t_history *)malloc(sizeof(t_history));
	if (!new)
		return (-1);
	new->i = i;
	new->cmd = ft_strdup(str);
	new->next = NULL;
	if (!(*history))
		*history = new;
	else
	{
		while ((*history)->next)
			*history = (*history)->next;
		(*history)->next = new;
	}
	return (1);
}

int	historyy(char *str, t_infohis **info)
{
	static int	i = 1;
	t_history	*head;


	head = (*info)->history;
	add_history(str);
	if (history_node(str, &(*info)->history, i) == -1)
		return (-1);
	if (head)
		(*info)->history = head;
	(*info)->total_cmds = i;
	i++;
	return (1);
}

int	print_history(t_infohis info, t_cmd cmd)
{
	size_t		num;
	(void)cmd;
	if (cmd.nargs > 2)
		return (-1);
	if (cmd.nargs == 2)
	{
		num = ft_atoi(cmd.token->next->token);
		num = info.total_cmds - num;
		if (num < info.total_cmds)
			while (num-- > 0 && info.history)
				info.history = info.history->next;
	}
	while (info.history)
	{
		ft_printf("%d %s\n", info.history->i, info.history->cmd);
		info.history = info.history->next;
	}
	return (1);
}
