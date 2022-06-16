/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 03:52:57 by ommohame          #+#    #+#             */
/*   Updated: 2022/06/17 03:15:57 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdlib.h>

# include "libft.h"
# include "ft_printf.h"
# include "structure.h"

void	print_line(t_line *line);
size_t	ft_strlenx2(char **str);
char	**ft_splitq(char	*str);

t_line	*cmds(char *str, t_line *line);

int		is_builtin(char *str);

char	*qoutes(char *str);

#endif