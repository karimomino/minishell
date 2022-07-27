/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 02:15:04 by ommohame          #+#    #+#             */
/*   Updated: 2022/07/27 05:01:06 by ommohame         ###   ########.fr       */
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
		return (0);
	}
}

// int		redir_in(t_redir redir, int f)
// {
// 	int		fd;
// 	int		tmp;
// 	char	*tmp1;
// 	char	*tmp2;

// 	if (redir.type == 1)
// 	{
// 		fd = open(redir.file, O_RDONLY);
// 		if (fd < 0)
// 		{
// 			ft_printf("minishell: no such file or directory: %s\n",
// 				redir.file);
// 			return (-1);
// 		}
// 		// if (f == 1)
// 		// 	*str = get_next_line(fd);
// 	}
// 	else if (redir.type == 2)
// 	{
// 		while (1)
// 		{
// 			tmp1 = readline("> ");
// 			if (!ft_strncmp(tmp1, redir.file, ft_strlen(tmp1)) && ft_strncmp(tmp1, "", 1)
// 			&& (ft_strlen(tmp1) == ft_strlen(redir.file)))
// 			{
// 				free(tmp1);
// 				if (!*str)
// 					return (1);
// 				tmp2 = ft_strtrim(*str, "\n");
// 				free(*str);
// 				*str = tmp2;
// 				return (1);
// 			}
// 			tmp2 = ft_strjoin(tmp1, "\n");
// 			if (!*str)
// 				*str = ft_strdup(tmp2);
// 			else
// 				*str = ft_strjoin(*str, tmp2);
// 			free(tmp1);
// 			free(tmp2);
// 		}
// 	}
// 	if (f == 1)
// 	{
// 		tmp = dup(STDIN_FILENO);
// 		dup2(fd, STDIN_FILENO);
// 		exec_ft(cmd);
// 		dup2(tmp, STDIN_FILENO);
// 	}
// 	close (fd);
// 	return (1);
// }

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

int	redirect(t_cmd *cmd, int fd_out)
{
	int		tmp_out;

	tmp_out = dup(STDOUT_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	exec_ft(cmd);
	dup2(tmp_out, STDOUT_FILENO);
	close(fd_out);
	return (1);
}

int	redirection(t_cmd *cmd)
{
	int		f;
	int		fd_out;
	size_t	i;

	f = 0;
	i = 0;
	if (!cmd->redir || cmd->nredir == 0)
		return (0);
	while (i < cmd->nredir && cmd->redir)
	{
		if (check_lastredir(*cmd->redir))
			f = 1;
		if (cmd->redir->fd == 1)
			fd_out = redir_out(*cmd->redir, f);
		// else if (cmd->redir->fd == 0)
		// 	redir_in(*cmd->redir, f);
		f = 0;
		i++;
	}
	redirect(cmd, fd_out);
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