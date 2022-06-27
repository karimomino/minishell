/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 03:52:57 by ommohame          #+#    #+#             */
/*   Updated: 2022/06/26 01:02:04 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdlib.h>
# include <stddef.h>
# include "libft.h"
# include "ft_printf.h"
# include "structure.h"

void	print_line(t_line *line);
size_t	ft_strlenx2(char **str);
char	**ft_splitq(char	*str);

t_line	*cmds(char *str, t_line *line);

int		is_builtin(char *str);

char	*qoutes(char *str);

char	**ft_split_sc(char *str, char c);

char	**ft_split_rd(char *str);

char	**ft_splitq(char *str);

int		skip_quotes(char *str, int i);

t_redir	*get_redir(t_cmd *cmd, char **str);

void	free_nodes(t_line *line);

void	free_2d(char **str);

#endif