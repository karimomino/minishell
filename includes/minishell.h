/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 08:18:24 by kamin             #+#    #+#             */
/*   Updated: 2022/07/26 03:41:17 by ommohame         ###   ########.fr       */
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

extern char	**environ;

pid_t	pid;

struct s_info
{
	int	retVal;
} t_infoo;

void	ft_setenv(const char *name, const char *value, int overwrite);
void	ft_env(void);
int		ft_echo(t_cmd *cmd);
int		exec_ft(t_cmd *in);
int		exec_bin(t_cmd *in);
int		exec_builtin(t_cmd *in);
int		ft_pwd(void);

#endif
