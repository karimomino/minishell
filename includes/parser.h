/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 03:52:57 by ommohame          #+#    #+#             */
/*   Updated: 2022/06/30 22:20:10 by ommohame         ###   ########.fr       */
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

int		cmds(char *str, t_line **line);

int		is_builtin(char *str);

char	*qoutes(char *str);

char	**ft_split_sc(char *str, char c);

char	**ft_split_rd(char *str);

char	**ft_splitq(char *str);

long	skip_quotes(char *str, size_t i);


void	free_nodes(t_line *line);

void	free_2d(char **str);

char	**parse(char *str);

int		define_redir(char *str, char **ret, int *i);

int		define_cmd(char *str, char **ret, int *i);

int		redir_node(char *str, t_redir **redir);

char	*get_redir(char *str, int *i);

char	*squeeze_space(char *str);
// int		get_redirs(char *str, char **ret, size_t *i);

#endif