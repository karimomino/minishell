/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@42abudhabi.ae>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 08:18:24 by kamin             #+#    #+#             */
/*   Updated: 2022/09/16 05:34:23 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft.h"
# include "./parser.h"

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/ioctl.h>

# define SUCCESS 0
# define ERROR 0
# define MAX_PATH 4096
# define BUFFER_SIZE 1
# define HOMEFLAG 0
# define OLDPWDFLAG 1
# define PROMPT_MSG "\033[1m\033[32mminishell: \033[0m"

extern char	**environ;

int		sig_exit_code(int flag);

void	export_executor(char *name, char *val, int ow, int ac);
void	ft_setenv(const char *name, const char *value, int overwrit);
int		ft_env(t_cmd *in);
int		ft_echo(t_cmd *cmd);
int		exec_ft(t_line **line);
int		exec_bin(t_line **line);
int		exec_builtin(t_line **line);
int		ft_pwd(t_cmd *in);
int		ft_export(t_cmd *cmd, int ow);
int		ft_cd(t_cmd *cmd);
int		ft_exit(t_line **line);
void	ft_expansion(t_line **line);
int		count_env(char **env);
int		ft_set(int i, char *val);
int		ft_unset(int i);
int		free_cmd(t_cmd *cmd);

int		reaser(t_line **line);
int		yalla(t_line **line);

void	init_environment();
int		add_to_env(char *val);
void	do_nothing(int sig);

/*****************EXPANSION*****************/
int		to_expand(char c);
int		stopper_finder(char *tok);
int		check_char(char c,int *dq, int *sq);
int		cpy_sec(int start, char **com, char *tok, char stopper);
int		expansion_free(char **string, char **tmp, char **var, char **env);
char	**select_string(void *cmd, int flag);
char	*get_variable_name(void *cmd, int flag);
char	*combined(char *tok, char *val, char *var, int index);
size_t	calc_malloc_size(char *tok, char *var, char *val);

/*****************EXECUTION*****************/
int		cmd_child(t_line **line, char *path);
void	ms_wait(t_line **line);
void	exec_errors(t_line *line, char *path, int *is_dir);
void	check_access(t_line *line, char *path, int *is_dir);
void	free_paths(char ***paths, char **f_path, int is_file);
void	files_access(int *is, char ***p, char **path, char **f_path);
#endif
