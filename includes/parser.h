/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 03:52:57 by ommohame          #+#    #+#             */
/*   Updated: 2022/07/29 18:16:13 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

// # include <stdlib.h>
// # include <stddef.h>
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
int		redir_node(char *str, t_redir **redir, size_t i);
int		redir_what(char *str);
int		redir_type(char *str);
int		last_cmd_node(char **str, t_cmd **cmd, t_line **line);
char	*get_redir(char *str, int *i);
char	*squeeze_space(char *str);
int		get_cmd(char *str, char **ret, int *i);
int		get_args(char *str, char **ret, int *i);
int		check_pipes(char **cmd, char *str, t_line **line);
int		parser_v3_0(char *str, t_line **line);
int		historyy(char *str);
int		print_history(t_cmd cmd);
int		redirection(t_cmd *cmd);
int		redirection(t_cmd *cmd);
size_t	gnl_strlen(const char *s);
char	*gnl_strchr(const char *s, int c);
char	*gnl_strjoin(char *s1, char *s2);
char	*get_next_line(int fd);
void	clear_line(int sig);
void	signals(void);
int		init_history(void);
int	pipes(t_cmd *cmd);
#endif
