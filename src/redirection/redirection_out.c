/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_out.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 03:38:31 by ommohame          #+#    #+#             */
/*   Updated: 2022/09/17 03:39:35 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	redirection_out(t_cmd **cmd, int *exit_code, int f)
{
	int		fd;

	if ((!access((*cmd)->redir->file, F_OK)
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
