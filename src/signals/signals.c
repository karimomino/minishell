/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 01:47:45 by ommohame          #+#    #+#             */
/*   Updated: 2022/09/15 14:55:09 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	sig_exit_code(int flag)
{
	static int	exit = -1;

	if (flag == SIGINT)
		exit = 130;
	else if (flag == -69)
		exit = -1;
	return (exit);
}

void	clear_line(int sig)
{
	if (sig == SIGINT)
	{
		sig_exit_code(sig);
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		ft_putchar_fd('\n', 1);
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}
