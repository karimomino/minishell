/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 10:07:29 by kamin             #+#    #+#             */
/*   Updated: 2022/06/19 11:14:46 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_flag(char *token)
{
	int	notFlag;

	notFlag = 0;
	if (*token == '-')
		token++;
	else
		notFlag = 1;
	while (*token && !notFlag)
	{
		if (*token != 'n')
			notFlag = 1;
		token++;
	}
	return (notFlag);
}

int			ft_echo(t_cmd *cmd)
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
	if (flag == 1 || cmd->nargs == 1)
		write(1, "\n", 1);
	return (SUCCESS);
}
