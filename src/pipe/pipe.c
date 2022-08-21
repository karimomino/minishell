/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 23:23:04 by ommohame          #+#    #+#             */
/*   Updated: 2022/08/21 15:22:08 by ommohame         ###   ########.fr       */
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
	int		in[n];
	t_cmd	*cmdd;

	in[0] = -1;
	i = 1;
	while (line->cmd)
	{
		pipe(fd);
		pid = fork();
		if (!pid)
			child(line, fd, in[i - 1]);
		else
		{
			close(fd[1]);
			cmdd = line->cmd;
			in[i] = fd[0];
			line->cmd = line->cmd->next;
			free_cmd(cmdd);
		}
		i++;
	}
	i = 1;
	while (i < n + 1)
	{
		wait(NULL);
		close(in[i++]);
	}
	return (1);
}
