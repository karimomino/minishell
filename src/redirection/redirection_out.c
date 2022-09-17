/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_out.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@42abudhabi.ae>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 03:38:31 by ommohame          #+#    #+#             */
/*   Updated: 2022/09/17 19:49:58 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	redirection_out(t_cmd **cmd, int *exit_code, int f)
{
	int		fd;

	if (!check_if_directory((*cmd)->redir->file, exit_code))
		return (0);
	else if ((!access((*cmd)->redir->file, F_OK)
			&& !access((*cmd)->redir->file, W_OK))
		|| (access((*cmd)->redir->file, F_OK)))
	{
		if ((*cmd)->redir->type == 1)
			fd = open((*cmd)->redir->file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		else
			fd = open((*cmd)->redir->file, O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (fd == -1)
			return (0);
	}
	else
	{
		ft_putendl_fd("minishell: redirection error: permission denied", 2);
		*exit_code = 1;
		return (0);
	}
	if (f)
		(*cmd)->out = fd;
	else
		close (fd);
	return (1);
}
