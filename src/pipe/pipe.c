/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 23:23:04 by ommohame          #+#    #+#             */
/*   Updated: 2022/08/02 20:07:58 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	child(t_cmd *cmd, int fd[2], int in)
{	
	if (cmd->next)
		dup2(fd[1], STDOUT_FILENO);
	dup2(in, STDIN_FILENO);
	redirection(cmd);
	close(fd[0]);
	exec_ft(cmd);
	exit(0);
}

int	pipes(t_cmd *cmd, int n)
{
	int		i;
	int		pid;
	int		fd[2];
	int		in;

	in = 0;
	while (cmd)
	{
		pipe(fd);
		pid = fork();
		if (pid == 0)
			child(cmd, fd, in);
		close(fd[1]);
		in = fd[0];
		cmd = cmd->next;
	}
	i = 0;
	while (i++ < n * 2)
		wait(NULL);
	// close(in);
	return (1);
}
