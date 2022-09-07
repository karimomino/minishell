/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 00:04:27 by ommohame          #+#    #+#             */
/*   Updated: 2022/09/07 11:23:20 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	redir_in1(t_redir redir, int f)
{
	int		fd;

	if (access(redir.file, F_OK) == -1)
	{
		ft_putstr_fd("minihshell: ", 2);
		ft_putstr_fd(redir.file, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		t_infoo.retVal = 2;
		return (-1);
	}
	if (access(redir.file, R_OK) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(redir.file, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		t_infoo.retVal = 126;
		return (-1);
	}
	fd = open(redir.file, O_RDONLY);
	if (f == 1)
		return (fd);
	close (fd);
	return (-1);
}

static int	read_herdoc(t_redir redir, int fd)
{
	char	*tmp1;

	while (1)
	{
		tmp1 = readline(">");
		if (!tmp1)
			return (-2);
		if (!ft_strncmp(tmp1, redir.file, ft_strlen(tmp1))
			&& ft_strncmp(tmp1, "", 1)
			&& (ft_strlen(tmp1) == ft_strlen(redir.file)))
		{
			free(tmp1);
			close(fd);
			break ;
		}
		ft_putstr_fd(tmp1, fd);
		ft_putchar_fd('\n', fd);
		free(tmp1);
	}
	return (1);
}

int	heredoc(t_redir redir, int f)
{
	int		fd;

	fd = -1;
	if (f == 1)
		fd = open("./src/redirection/.heredoc.txt",
				O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (read_herdoc(redir, fd) != 1)
		return (-2);
	close(fd);
	if (f == 1)
		return (open("./src/redirection/.heredoc.txt", O_RDONLY));
	return (-1);
}

int	redir_in(t_redir redir, int f)
{
	if (redir.type == 1)
		return (redir_in1(redir, f));
	else
		return (heredoc(redir, f));
}
