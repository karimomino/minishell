/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 01:47:45 by ommohame          #+#    #+#             */
/*   Updated: 2022/09/07 21:08:38 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// int		g_sig = 0;

void	clear_line(int sig)
{
	if (sig == SIGINT)
	{
		if (g_exitval != -1 || g_exitval != -2)
		{
			ft_putstr_fd("\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		if (g_exitval == -1 || g_exitval == -2)
			g_exitval = -2;
		else
			g_exitval = 130;
		return ; 
	}
	else if (sig == SIGQUIT)
		return ;
	else if (sig == SIGUSR1)
		exit (0);
}

// void	signals(void)
// {
// 	signal(SIGINT, clear_line);
// }
