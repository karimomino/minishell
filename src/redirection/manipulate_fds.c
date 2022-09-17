/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulate_fds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 03:37:28 by ommohame          #+#    #+#             */
/*   Updated: 2022/09/17 03:38:07 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	change_fds(t_cmd **cmd)
{
	int	in;
	int	out;

	if ((*cmd)->in != -1)
	{
		in = dup(STDIN_FILENO);
		dup2((*cmd)->in, STDIN_FILENO);
		(*cmd)->in = in;
	}
	if ((*cmd)->out != -1)
	{
		out = dup(STDOUT_FILENO);
		dup2((*cmd)->out , STDOUT_FILENO);
		(*cmd)->out = out;
	}
	return (1);
}

void	reset_fds(int in, int out)
{
	if (in != -1)
		dup2(in, STDIN_FILENO);
	if (out != -1)
		dup2(out, STDOUT_FILENO);
}
