/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 02:15:04 by ommohame          #+#    #+#             */
/*   Updated: 2022/07/20 21:13:58 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	redir_out(t_redir redir, int f, char *str)
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

int		redir_in(t_redir redir, char **str, int f)
{
	int		fd;
	char	*tmp1;
	char	*tmp2;

	if (redir.type == 1)
	{
		fd = open(redir.file, O_RDONLY);
		if (fd < 0)
		{
			ft_printf("minishell: no such file or directory: %s\n",
				redir.file);
			return (-1);
		}
		if (f == 1)
			*str = get_next_line(fd);
	}
	else if (redir.type == 2)
	{
		while (1)
		{
			tmp1 = readline("> ");
			if (!ft_strncmp(tmp1, redir.file, ft_strlen(tmp1)) && ft_strncmp(tmp1, "", 1)
			&& (ft_strlen(tmp1) == ft_strlen(redir.file)))
			{
				free(tmp1);
				if (!*str)
					return (1);
				tmp2 = ft_strtrim(*str, "\n");
				free(*str);
				*str = tmp2;
				return (1);
			}
			tmp2 = ft_strjoin(tmp1, "\n");
			if (!*str)
				*str = ft_strdup(tmp2);
			else
				*str = ft_strjoin(*str, tmp2);
			free(tmp1);
			free(tmp2);
		}
	}
	return (1);
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

int		redirection(t_cmd cmd, char *str, char **in)
{
	int		f;
	size_t	i;

	f = 0;
	i = 0;
	*in = NULL;
	if (!cmd.redir || cmd.nredir == 0)
		return (0);
	while (i < cmd.nredir && cmd.redir)
	{
		if (check_lastredir(*cmd.redir))
			f = 1;
		if (cmd.redir->fd == 1)
			redir_out(*cmd.redir, f, str);
		else if (cmd.redir->fd == 0)
		{
			if (redir_in(*cmd.redir, &(*in), f) == -1)
				return (-1);
			if (*in)
				ft_printf("redir in: %s\n", *in);
		}
		f = 0;
		cmd.redir = cmd.redir->next;
		i++;
	}
	return (1);
}