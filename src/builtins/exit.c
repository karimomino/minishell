/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 20:33:43 by kamin             #+#    #+#             */
/*   Updated: 2022/09/13 23:20:31 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int is_num(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		if (!ft_isdigit(str[i++]))
			return (0);
	return (1);
}

static int	exit_help(t_line **line)
{
	if ((*line)->cmd->nargs > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		(*line)->exit = 1;
		return (1);
	}
	if ((*line)->cmd->nargs == 2 && !is_num((*line)->cmd->token->next->token))
	{
		ft_putstr_fd("minishell: exit: lkmasd: numeric argument required\n", 2);
		(*line)->exit = 255;
	}
	else if ((*line)->cmd->token->next != NULL)
		(*line)->exit = ft_atoi((*line)->cmd->token->next->token);
	return (2);
}

int	ft_exit(t_line **line)
{
	int		ret;

	ret = exit_help(line);
	free_nodes(*line);
	if (ret == 1)
		return (-1);
	free(*line);
	ret = (*line)->exit;
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	exit(ret);
}
