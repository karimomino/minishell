/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 02:15:04 by ommohame          #+#    #+#             */
/*   Updated: 2022/08/24 00:14:03 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	redir_out(t_redir redir, int f)
{
	int		fd;

	if (redir.type == 1)
		fd = open(redir.file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else
		fd = open(redir.file, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (f == 1)
		return (fd);
	else
	{
		close (fd);
		return (-1);
	}
}

static int	check_lastredir(t_redir redir)
{
	int		fd;

	if (redir.next)
	{
		fd = redir.fd;
		redir = *redir.next;
		if (redir.fd == fd)
			return (0);
		while (redir.next)
		{
			redir = *redir.next;
			if (redir.fd == fd)
				return (0);
		}
	}
	return (1);
}

static int	redirect(t_line *line, int fd_in, int fd_out)
{
	int	in;
	int	out;

	in = dup(STDIN_FILENO);
	out = dup(STDOUT_FILENO);
	if (fd_in >= 0)
		dup2(fd_in, STDIN_FILENO);
	if (fd_out >= 0)
		dup2(fd_out, STDOUT_FILENO);
	exec_ft(line);
	if (fd_in >= 0)
	{
		dup2(in, STDIN_FILENO);
		close(fd_in);
	}
	if (fd_out >= 0)
	{
		dup2(out, STDOUT_FILENO);
		close(fd_out);
	}
	close(in);
	close(out);
	return (1);
}

static void	redir_loop(t_line *line)
{	
	int		f;
	int		fd_in;
	int		fd_out;
	t_redir	*redirr;

	f = 0;
	fd_in = -1;
	fd_out = -1;
	while (line->cmd->redir)
	{
		if (check_lastredir(*line->cmd->redir))
			f = 1;
		if (line->cmd->redir->fd == 1)
			fd_out = redir_out(*line->cmd->redir, f);
		else if (line->cmd->redir->fd == 0)
			fd_in = redir_in(*line->cmd->redir, f);
		redirr = line->cmd->redir;
		line->cmd->redir = line->cmd->redir->next;
		free(redirr->file);
		free(redirr);
		f = 0;
	}
	redirect(line, fd_in, fd_out);
}

int	redirection(t_line *line)
{
	if (!line->cmd->redir || line->cmd->nredir == 0)
		return (0);
	redir_loop(line);
	if (access("./src/redirection/.heredoc.txt", F_OK))
		unlink("./src/redirection/.heredoc.txt");
	return (1);
}
