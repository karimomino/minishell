/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 03:52:57 by ommohame          #+#    #+#             */
/*   Updated: 2022/06/13 05:33:46 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdlib.h>

# include "libft.h"
# include "ft_printf.h"
# include "structure.h"
# include "debug.h"

void	print_line(t_line *line);
size_t	ft_strlenx2(char **str);

int		cmd_node(char *str, t_cmd **cmd);
int		token_node(char *str, t_token **token);

#endif