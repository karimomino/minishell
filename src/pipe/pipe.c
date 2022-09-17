/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 23:23:04 by ommohame          #+#    #+#             */
/*   Updated: 2022/09/17 16:34:21 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	child(t_line **line, int fd[2], int in)
{
	int		inn;
	int		out;

	if ((*line)->cmd->next)
		dup2(fd[1], STDOUT_FILENO);
	dup2(in, STDIN_FILENO);
	close(fd[0]);
	if ((*line)->cmd->in != -2
		&& (*line)->cmd->out != -2)
	{
		change_fds(&(*line)->cmd);
		inn = (*line)->cmd->in;
		out = (*line)->cmd->out;
		exec_ft(line);
		reset_fds(inn, out);
	}
	free_nodes(*line);
	free(*line);
	exit(0);
}

static int	pipe_norm(t_line **line, int **in)
{
	int		i;
	int		pid;
	int		fd[2];
	t_cmd	*cmdd;

	i = 1;
	while ((*line)->cmd)
	{
		pipe(fd);
		pid = fork();
		if (!pid)
			child(line, fd, (*in)[i - 1]);
		else
		{
			close(fd[1]);
			cmdd = (*line)->cmd;
			(*in)[i] = fd[0];
			(*line)->cmd = (*line)->cmd->next;
			free_cmd(cmdd);
		}
		i++;
	}
	return (1);
}

int	pipes(t_line **line, int n)
{
	int		i;
	int		*in;

	in = (int *)malloc(sizeof(int) * (n + 1));
	in[0] = -1;
	pipe_norm(line, &in);
	i = 0;
	while (i++ < n)
	{
		ms_wait(line);
		close(in[i]);
	}
	free(in);
	return (1);
}
