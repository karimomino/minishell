/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 23:23:04 by ommohame          #+#    #+#             */
/*   Updated: 2022/07/29 23:05:32 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pipes(t_cmd *cmd)
{
	int		pid;
	int		fd[2];
	(void)cmd;
	// int		tmpin;
	// int		tmpout;

	if (pipe(fd) == -1)
	{
		ft_printf("minishell: pipe failed m3lsh\n");
		return (-1);
	}
	pid = fork();
	if (pid == -1)
	{
		ft_printf("minishell: man down, fork is not working\n");
		return (-1);
	}
	else if (pid == 0)
	{
		dup2(fd[0], 0);
		close(fd[1]);
		char *grep_args[] = {"grep", "test", NULL};
		execvp("grep", grep_args);
	}
	else
	{
		dup2(fd[1], 1);
		close(fd[0]);
		char *grep_args[] = {"ls", "-la", NULL};
		execvp("ls", grep_args);
	}
	return (1);
}
