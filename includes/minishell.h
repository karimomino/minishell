/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 08:18:24 by kamin             #+#    #+#             */
/*   Updated: 2022/08/05 18:45:47 by kamin            ###   ########.fr       */
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
#include <signal.h>

# define SUCCESS 0
# define ERROR 0
# define MAX_PATH 4096
# define BUFFER_SIZE 1
# define HOMEFLAG 0
# define OLDPWDFLAG 1

extern char	**environ;

struct s_info
{
	int	retVal;
} t_infoo;

typedef int	(*f)();


void	ft_setenv(const char *name, const char *value, int overwrite);
int		ft_env(t_cmd *in);
int		ft_echo(t_cmd *cmd);
int		exec_ft(t_cmd *in, f *builtins);
int		exec_bin(t_cmd *in);
int		exec_builtin(t_cmd *in, f *builtins);
int		ft_pwd(t_cmd *in);
int		ft_export(t_cmd *cmd, int ow);
int		ft_cd(t_cmd *cmd);
int		ft_exit(t_cmd *cmd);
void	ft_expansion(t_line **line);

#endif
