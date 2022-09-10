/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@42abudhabi.ae>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 01:47:45 by ommohame          #+#    #+#             */
/*   Updated: 2022/09/10 18:00:41 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// int		g_sig = 0;
#include <sys/ioctl.h>
void	clear_line(int sig)
{
	if (sig == SIGINT)
	{
		if (g_exitval == -1 || g_exitval == -2)
		{
			// rl_done = 1;
			// rl_pending_input = 'a';
			// ft_putstr_fd("\n", 1);
			ioctl(STDIN_FILENO, TIOCSTI, "\n");
			write(1, "\n", 1);
			rl_replace_line("", 0);
			rl_on_new_line();
			// rl_redisplay();
			//rl_pending_input = rl_line_buffer[0];
			// ft_putstr_fd("\n", 1);
			// rl.setPrompt("");
			// rl_replace_line("", 0);
			// ft_putstr_fd("test", 1);
		}
		else
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
	}
	else if (sig == SIGQUIT)
		return ;
	else if (sig == SIGUSR1)
		exit (0);
}
