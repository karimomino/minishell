/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 15:16:50 by ommohame          #+#    #+#             */
/*   Updated: 2022/06/12 15:29:35 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexar.h"

void	print_line(t_line *line)
{
	ft_printf("ncmds: %d\n", line->ncmds);
	ft_printf("nargs: %d\n", line->nargs);
	ft_printf("npipes: %d\n", line->npipes);
	ft_printf("infile: %s\n", line->infile);
	ft_printf("outfile: %s\n", line->outfile);
	ft_printf("errfile: %s\n", line->errfile);
	ft_printf("cmd: %s\n", line->cmd);
}