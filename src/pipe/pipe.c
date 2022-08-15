/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 23:23:04 by ommohame          #+#    #+#             */
/*   Updated: 2022/08/15 11:11:16 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	child(t_line *line, int fd[2], int in)
{	
	if (line->cmd->next)
		dup2(fd[1], STDOUT_FILENO);
	dup2(in, STDIN_FILENO);
	close(fd[0]);
	if (redirection(line) != 1)
		exec_ft(line);
	free_nodes(line);
	free(line);
	exit(0);
}

int	pipes(t_line *line, int n)
{
	int		i;
	int		pid;
	int		fd[2];
	int		in;
	t_cmd	*head;

	in = 0;
	head = line->cmd;
	while (line->cmd)
	{
		pipe(fd);
		pid = fork();
		if (!pid)
			child(line, fd, in);
		else
		{
			close(fd[1]);
			in = fd[0];
			line->cmd = line->cmd->next;
		}
	}
	line->cmd = head;
	i = 0;
	while (i++ < n)
		wait(NULL);
	close(in);
	return (1);
}
