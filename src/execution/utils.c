/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 16:13:29 by kamin             #+#    #+#             */
/*   Updated: 2022/09/15 19:17:11 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ms_wait(t_line **line)
{
	signal(SIGINT, SIG_IGN);
	wait(&(*line)->exit);
	(*line)->exit = WEXITSTATUS((*line)->exit);
	signal(SIGINT, clear_line);
}
