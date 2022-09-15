/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 00:04:27 by ommohame          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/09/15 04:51:51 by ommohame         ###   ########.fr       */
=======
/*   Updated: 2022/09/15 15:01:17 by kamin            ###   ########.fr       */
>>>>>>> 352623a4e00c1c10e9048d0cbf8878c82606dd9b
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
		g_exitval = 2;
		return (-1);
	}
	if (access(redir.file, R_OK) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(redir.file, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		g_exitval = 126;
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
		tmp1 = readline("> ");
		if (!tmp1)
			return (-2);
		if (sig_exit_code(-42) == 130)
		{
			if (tmp1)
				free(tmp1);
			return (-69);
		}
		if (!ft_strncmp(tmp1, redir.file, ft_strlen(tmp1))
			&& ft_strncmp(tmp1, "", 1)
			&& (ft_strlen(tmp1) == ft_strlen(redir.file)))
		{
			free(tmp1);
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
	int		ret;

	fd = -1;
	if (f == 1)
		fd = open("./src/redirection/.heredoc.txt",
				O_WRONLY | O_TRUNC | O_CREAT, 0644);
	ret = read_herdoc(redir, fd);
	close(fd);
	if (ret == -69)
		return (-69);
	else if (ret != 1)
		return (-2);
	if (f == 1)
		return (open("./src/redirection/.heredoc.txt", O_RDONLY));
	close(fd);
	return (-1);
}

int	redir_in(t_redir redir, int f)
{
	if (redir.type == 1)
		return (redir_in1(redir, f));
	else
		return (heredoc(redir, f));
}
