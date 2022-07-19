/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 01:47:45 by ommohame          #+#    #+#             */
/*   Updated: 2022/07/19 21:58:26 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// int		g_sig = 0;

void	clear_line(int sig)
{
	(void)sig;
	g_sig = 1;
	ft_putchar_fd(10, 0);
	// printf("\n"); // Move to a new line
	rl_on_new_line(); // Regenerate the prompt on a newline
	rl_replace_line("", 0); // Clear the previous text
	rl_redisplay();
}

void	signals(void)
{
	// char	*str;

	// str = NULL;
	printf("g_sig before: %d\n", g_sig);
	signal(SIGINT, clear_line);
	printf("g_sig after: %d\n", g_sig);
	// str = readline("\033[1m\033[32menter a fucking command: \033[0m");
	if (g_sig == 1)
	{
		g_sig = 0;
		// str = readline("\033[1m\033[32menter a fucking command: \033[0m");
		// return (str);
	}
	// else
	// if (!str)
	// 	exit (0);
	// return (str);
}