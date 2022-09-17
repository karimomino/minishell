/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_engine.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@42abudhabi.ae>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 00:13:06 by ommohame          #+#    #+#             */
/*   Updated: 2022/09/17 19:41:11 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_if_last(t_redir redir, int f)
{
	if (redir.next)
	{
		while (redir.next)
		{
			redir = *redir.next;
			if (redir.fd == f)
				return (0);
		}
	}
	return (1);
}

int	check_if_directory(char *str, int *exit_code)
{
	struct stat	info;

	stat(str, &info);
	if (S_ISDIR(info.st_mode) != 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd((":Is a directory\n"), 2);
		*exit_code = 1;
		return (0);
	}
	return (1);
}

int	loop_redir_nodes(t_cmd **cmd, int *exit_code)
{
	t_redir	*tmp;

	while ((*cmd)->redir)
	{
		if ((*cmd)->redir->fd == 0)
		{
			if (!redirection_in(cmd, exit_code,
					check_if_last(*(*cmd)->redir, 0)))
				return (0);
		}
		else if ((*cmd)->redir->fd == 1)
		{
			if (!redirection_out(cmd, exit_code,
					check_if_last(*(*cmd)->redir, 1)))
				return (0);
		}
		tmp = (*cmd)->redir;
		(*cmd)->redir = (*cmd)->redir->next;
		free(tmp->file);
		free(tmp);
	}
	return (1);
}

int	redirection_engine(t_line **line)
{
	if (!loop_redir_nodes(&(*line)->cmd, &(*line)->exit))
		return (0);
	return (1);
}

int	start_redir_engine(t_line **line)
{
	t_cmd	*head;

	head = (*line)->cmd;
	while ((*line)->cmd)
	{
		(*line)->cmd->in = -1;
		(*line)->cmd->out = -1;
		if (!redirection_engine(line))
		{
			(*line)->cmd->in = -2;
			(*line)->cmd->out = -2;
			free_nodes(*line);
			return (0);
		}
		(*line)->cmd = (*line)->cmd->next;
	}
	(*line)->cmd = head;
	return (1);
}
