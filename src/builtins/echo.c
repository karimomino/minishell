/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@42abudhabi.ae>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 10:07:29 by kamin             #+#    #+#             */
/*   Updated: 2022/09/17 16:14:52 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_flag(char *token)
{
	int	not_flag;
	int	i;

	i = 0;
	not_flag = 0;
	i = 0;
	if (token[i] == '-')
		i++;
	else
		not_flag = 1;
	while (token[i] && !not_flag)
	{
		if (token[i] != 'n')
			not_flag = 1;
		i++;
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
			if (ft_strcmp(cmd->token->token, " "))
				ft_putstr_fd(cmd->token->token, 1);
			if (cmd->token->next && ft_strcmp(cmd->token->next->token, " "))
				write(1, " ", 1);
			cmd->token = cmd->token->next;
		}
	}
	if (flag == 0 || cmd->nargs == 1)
		write(1, "\n", 1);
	return (SUCCESS);
}
