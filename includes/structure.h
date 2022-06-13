/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 01:35:36 by ommohame          #+#    #+#             */
/*   Updated: 2022/06/13 19:17:25 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H

# include "parser.h"

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

#endif