/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@42abudhabi.ae>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 16:13:29 by kamin             #+#    #+#             */
/*   Updated: 2022/09/12 16:15:01 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ms_wait(t_line **line)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	wait(&(*line)->exit);
	(*line)->exit = WEXITSTATUS((*line)->exit);
	signal(SIGINT, clear_line);
	signal(SIGQUIT, clear_line);
}
