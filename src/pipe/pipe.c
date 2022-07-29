/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 23:23:04 by ommohame          #+#    #+#             */
/*   Updated: 2022/07/29 22:04:52 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pipes(t_cmd *cmd)
{
	int		pid;
	int		fd[2];
	t_cmd *cmd2;
	// int		tmpin;
	// int		tmpout;

	pid = fork();
	cmd2 = cmd->next;
	if (pipe(fd) == -1)
	{
		ft_printf("minishell: pipe failed m3lsh\n");
		return (-1);
	}
	if (pid == -1)
	{
		ft_printf("minishell: man down, fork is not working\n");
		return (-1);
	}
	else if (pid == 0)
	{
		dup2(fd[1], 1);
		close(fd[0]);
		exec_ft(cmd2);
		exit(0);
	}
	else
	{
		dup2(fd[0], 0);
		close(fd[1]);
		dup2(fd[1], 1);
		exec_ft(cmd);
	}
	return (1);
}
