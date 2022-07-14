/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 02:15:04 by ommohame          #+#    #+#             */
/*   Updated: 2022/07/14 20:50:00 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		redir_out(t_redir redir, int f, char *str)
{
	int		fd;

	if (redir.type == 1)
		fd = open(redir.file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else
		fd = open(redir.file, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (f == 1)
		write(fd, &*str, ft_strlen(str));
	close(fd);
	return (1);
}

int		check_lastredir(t_redir redir)
{
	int		fd;

	fd = redir.fd;
	while (redir.fd)
	{
		if (redir.fd == fd)
			return (0);
		redir = *redir.next;
	}
	return (1);
}

int		redirection(t_cmd cmd, char *str)
{
	int		f;
	size_t	i;

	f = 0;
	i = 0;
	if (!cmd.redir || cmd.nredir == 0)
		return (0);
	while (i < cmd.nredir && cmd.redir)
	{
		if (i == cmd.nredir - 1 || check_lastredir(*cmd.redir))
			f = 1;
		if (cmd.redir->fd == 1)
			redir_out(*cmd.redir, f, str);
		cmd.redir = cmd.redir->next;
		i++;
	}
	return (1);
}