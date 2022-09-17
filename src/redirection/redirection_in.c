/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 03:42:30 by ommohame          #+#    #+#             */
/*   Updated: 2022/09/17 16:35:24 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	redirect_into_file(t_cmd **cmd, int *exit_code, int f)
{
	int		fd;

	if (access((*cmd)->redir->file, F_OK) == -1)
	{
		ft_putstr_fd("minihshell: ", 2);
		ft_putstr_fd((*cmd)->redir->file, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		*exit_code = 1;
		return (0);
	}
	else if (access((*cmd)->redir->file, R_OK) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd((*cmd)->redir->file, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		*exit_code = 1;
		return (0);
	}
	fd = open((*cmd)->redir->file, O_RDONLY);
	if (fd == -1)
		return (0);
	if (f == 1)
		(*cmd)->in = fd;
	else
		close (fd);
	return (1);
}

int	heredoc_child(t_cmd **cmd, int fd[2])
{
	char	*tmp;

	close(fd[0]);
	while (1)
	{
		tmp = readline("> ");
		if (!tmp)
			return (0);
		if (sig_exit_code(-42) == 130)
		{
			if (tmp)
				free(tmp);
			return (0);
		}
		if (!ft_strcmp(tmp, (*cmd)->redir->file))
		{
			free(tmp);
			break ;
		}
		ft_putstr_fd(tmp, fd[1]);
		ft_putchar_fd('\n', fd[1]);
		free(tmp);
	}
	return (1);
}

int	heredoc(t_cmd **cmd, int *exit_code, int f)
{
	int		ret;
	pid_t	pid;
	int		fd[2];

	pipe(fd);
	pid = fork();
	if (!pid)
		exit(heredoc_child(cmd, fd));
	else
	{
		close(fd[1]);
		wait(&ret);
		if (!WEXITSTATUS(ret))
		{
			close(fd[0]);
			*exit_code = 130;
			sig_exit_code(-69);
			return (0);
		}
		if (f == 1)
			(*cmd)->in = fd[0];
		else
			close(fd[0]);
	}
	return (1);
}

int	redirection_in(t_cmd **cmd, int *exit_code, int f)
{

	if ((*cmd)->redir->type == 1)
	{
		if (!redirect_into_file(cmd, exit_code, f))
			return (0);
	}
	else
	{
		if (!heredoc(cmd, exit_code, f))
			return (0);
	}
	return (1);
}