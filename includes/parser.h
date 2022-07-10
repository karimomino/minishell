/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 03:52:57 by ommohame          #+#    #+#             */
/*   Updated: 2022/07/11 02:06:40 by ommohame         ###   ########.fr       */
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

int		skip_quotes(char *str, int i);

void	free_nodes(t_line *line);

void	free_2d(char **str);

char	**parse(char *str);

int		define_redir(char *str, char **ret, int *i);

int		define_cmd(char *str, char **ret, int *i);

int		redir_node(char *str, t_redir **redir);

char	*get_redir(char *str, int *i);

char	*squeeze_space(char *str);

int		get_cmd(char *str, char **ret, int *i);

int		get_args(char *str, char **ret, int *i);

int		check_pipes(char **cmd, char *str, t_line **line);

int		parser_v3_0(char *str, t_line **line);

#endif
