/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@42abudhabi.ae>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 01:35:36 by ommohame          #+#    #+#             */
/*   Updated: 2022/09/11 01:53:04 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H

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
*	- type: type of redirection
*	- file: file name
*/
typedef struct s_redir
{
	size_t			i;
	int				fd;
	int				type;
	char			*file;
	struct s_redir	*prev;
	struct s_redir	*next;
}	t_redir;

/*
* linked list of every command
*	- type: type of command
		╵---> 0: exec
		╵---> > 0: built in
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
	int				type;
	size_t			nargs;
	size_t			nredir;
	char			*cmd;
	char			*exec;
	char			**envp;
	struct s_token	*token;
	struct s_redir	*redir;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_history
{
	size_t				i;
	char				*cmd;
	struct s_history	*next;
}	t_history;

typedef struct s_infohis
{
	size_t		total_cmds;
	t_history	*history;
}	t_infohis;

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
	size_t		ncmds;
	size_t		nexec;
	size_t		npipes;
	t_cmd		*cmd;
	int			exit;
	int			end;
}	t_line;

#endif
