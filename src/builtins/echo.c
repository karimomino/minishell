/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 10:07:29 by kamin             #+#    #+#             */
/*   Updated: 2022/08/05 23:23:06 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_flag(char *token)
{
	int	not_flag;

	not_flag = 0;
	if (*token == '-')
		token++;
	else
		not_flag = 1;
	while (*token && !not_flag)
	{
		if (*token != 'n')
			not_flag = 1;
		token++;
	}
	return (not_flag);
}

int	ft_echo(t_cmd *cmd)
{
	int		flag;

	flag = 0;
	if (cmd->nargs > 1)
	{
		cmd->token = cmd->token->next;
		if (!check_flag(cmd->token->token))
		{
			flag = 1;
			cmd->token = cmd->token->next;
		}
		while (cmd->token)
		{
			ft_putstr_fd(cmd->token->token, 1);
			if (cmd->token->next != NULL)
				write(1, " ", 1);
			cmd->token = cmd->token->next;
		}
	}
	if (flag == 0 || cmd->nargs == 1)
		write(1, "\n", 1);
	return (SUCCESS);
}
