/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 02:15:04 by ommohame          #+#    #+#             */
/*   Updated: 2022/08/02 20:08:39 by ommohame         ###   ########.fr       */
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
		// fd = dup(STDIN_FILENO);
		fd = open("./src/redirection/.heredoc.txt", O_WRONLY | O_TRUNC | O_CREAT, 0644);
	while (1)
	{
		tmp1 = readline(">");
		if (!ft_strncmp(tmp1, redir.file, ft_strlen(tmp1)) && ft_strncmp(tmp1, "", 1)
			&& (ft_strlen(tmp1) == ft_strlen(redir.file)))
		{
			free(tmp1);
			return (fd);
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

int	redirect(t_cmd *cmd, int fd_in, int fd_out)
{
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_in);
	close(fd_out);
	// exec_ft(cmd);
	(void)cmd;
	return (1);
}

int	redirection(t_cmd *cmd)
{
	int		f;
	int		fd_in;
	int		fd_out;
	size_t	i;

	f = 0;
	i = 0;
	fd_in = -1;
	fd_out = -1;
	if (!cmd->redir || cmd->nredir == 0)
		return (0);
	while (i < cmd->nredir && cmd->redir)
	{
		if (check_lastredir(*cmd->redir))
			f = 1;
		if (cmd->redir->fd == 1)
			fd_out = redir_out(*cmd->redir, f);
		else if (cmd->redir->fd == 0)
			fd_in = redir_in(*cmd->redir, f);
		cmd->redir = cmd->redir->next;
		f = 0;
		i++;
	}
	// ft_printf("fd in: %d | fd out: %d\n", fd_in, fd_out);
	redirect(cmd, fd_in, fd_out);
	unlink("./src/redirection/.heredoc.txt");
	return (1);
}
// int	redirection_in(t_cmd *cmd)
// {
// 	int		f;
// 	size_t	i;

// 	f = 0;
// 	i = 0;
// 	if (!cmd->redir || cmd->nredir == 0)
// 		return (0);
// 	while (i < cmd->nredir && cmd->redir)
// 	{
// 		if (check_lastredir(*cmd->redir))
// 			f = 1;
// 		if (cmd->redir->fd == 1)
// 			redir_out(cmd, *cmd->redir, f);
// 		f = 0;
// 		i++;
// 	}
// 	reutn (1);
// }
// int	redirection_out(t_cmd *cmd)
// {
// 	int		f;
// 	int		fd;
// 	size_t	i;

// 	f = 0;
// 	i = 0;
// 	if (!cmd->redir || cmd->nredir == 0)
// 		return (0);
// 	while (i < cmd->nredir && cmd->redir)
// 	{
// 		if (check_lastredir(*cmd->redir))
// 			f = 1;
// 		if (cmd->redir->fd == 1)
// 			redir_out(*cmd->redir, f);
// 		f = 0;
// 		i++;
// 	}
// 	return (1);
// }
// }