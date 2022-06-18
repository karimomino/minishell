/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 08:18:24 by kamin             #+#    #+#             */
/*   Updated: 2022/06/18 13:41:45 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef STRUCTURE_H
# define STRUCTURE_H

#include "libft.h"

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <errno.h>

extern char **environ;

struct s_info
{
	int	retVal;
} t_infoo;

/*
* toekns structure
*	- i: index of token
*		╵---> 0: is gonna be the command to excute
*	- token: the token saved as string
*	- prev: previous token
*	- next: next token
*/
typedef struct s_token
{
	size_t			i;
	char			*token;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

/*
* linked list of redirections
*	- fd: define what to redirect
*		╵---> 0: stdin
*		╵---> 1: stdout
*		╵---> 2: stderr
*	- file: file name
*/
typedef struct s_redir
{
	int				fd;
	char			*file;
	struct s_redir	*prev;
	struct s_redir	*next;
}	t_redir;

/*
* linked list of every command
*	- nargs: how many arguments in the function including the function
*	- cmd: the command line splited by space
*		╵---> gonna have an issue with quotes
*	- token: tokens linked list
*	- redir: redirections
*	- next: the next command
*	- prev: the prev command
*/
typedef struct s_cmd
{
	size_t			nargs;
	char			**cmd;
	char			**envp;
	int				type;
	struct s_token	*token;
	struct s_redir	*redir;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}	t_cmd;

/*
* analyzes the line and put it in the struct
*	- ncmds: how many commands
*	- nexec: number of execu tion commands
*		╵---> -1: line is empty or error
*		╵---> 0: built in commands
*		╵---> > 0: number of commands to execute
*	- npipes: how many pipes in the line
*	- cmd: ptr to the the first command node
*/
typedef struct s_line
{
	size_t	ncmds;
	size_t	nexec;
	size_t	npipes;
	t_cmd	*cmd;
}	t_line;

void	ft_setenv(const char* name, const char *value, int overwrite);

#endif
