/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 02:15:04 by ommohame          #+#    #+#             */
/*   Updated: 2022/08/20 12:44:07 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	redir_out(t_redir redir, int f)
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

int		redir_in1(t_redir redir, int f)
{
	int		fd;

	if (access(redir.file, F_OK) == -1)
	{
		ft_printf("minishell: %s: No such file or directory\n", redir.file);
		return (-1);
	}
	if (access(redir.file, R_OK) == -1)
	{
		ft_printf("minishell: %s: Permission denied\n", redir.file);
		return (-1);
	}
	fd = open(redir.file, O_RDONLY);
	if (f == 1)
		return (fd);
	close (fd);
	return (-1);
}

int		heredoc(t_redir redir, int f)
{
	int		fd;
	char 	*tmp1;

	fd = -1;
	if (f == 1)
		fd = open("./src/redirection/.heredoc.txt", O_WRONLY | O_TRUNC | O_CREAT, 0644);
	while (1)
	{
		tmp1 = readline(">");
		if (!tmp1)
			return (-2);
		if (!ft_strncmp(tmp1, redir.file, ft_strlen(tmp1)) && ft_strncmp(tmp1, "", 1)
			&& (ft_strlen(tmp1) == ft_strlen(redir.file)))
		{
			free(tmp1);
			close(fd);
			if (f == 1)
			{
				fd = open("./src/redirection/.heredoc.txt", O_RDONLY);
				return (fd);
			}
			else
				return (-1);
		}
		ft_putstr_fd(tmp1, fd);
		ft_putchar_fd('\n', fd);
		free(tmp1);
	}
	if (f == 1)
		return (fd);
	return (-1);
}

int		redir_in(t_redir redir, int f)
{
	if (redir.type == 1)
		return (redir_in1(redir, f));
	else
		return (heredoc(redir, f));
}

int		check_lastredir(t_redir redir)
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

int	redirect(t_line *line, int fd_in, int fd_out)
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

int	redirection(t_line *line)
{
	int		f;
	int		fd_in;
	int		fd_out;
	size_t	i;
	t_redir	*redirr;

	f = 0;
	i = 0;
	fd_in = -1;
	fd_out = -1;
	if (!line->cmd->redir || line->cmd->nredir == 0)
		return (0);
	while (i < line->cmd->nredir && line->cmd->redir)
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
		i++;
	}
	redirect(line, fd_in, fd_out);
	unlink("./src/redirection/.heredoc.txt");
	return (1);
}
