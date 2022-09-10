/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@42abudhabi.ae>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 01:47:45 by ommohame          #+#    #+#             */
/*   Updated: 2022/09/11 03:36:40 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#include <sys/ioctl.h>
void	clear_line(int sig)
{
	if (sig == SIGINT)
	{
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
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

void	do_nothing(int sig)
{
	(void)sig;
	return ;
}
