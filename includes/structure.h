/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 01:35:36 by ommohame          #+#    #+#             */
/*   Updated: 2022/06/12 04:33:05 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H

/*
* linked list of every command
*	- nargs: how many arguments in the line including the function
*	- args: the arguments stored in double array
*	╵---> args[0]: the command
*	- next: the next command
*/
typedef struct s_cmd
{
	int				nargs;
	char			**args;
	struct s_cmd	*next;
}	t_cmd;

/*
* analyzes the line and put it in the struct
*	- ncmds: how many commands
*	- nargs: how many arguments in the line including the function
*	- npipes: how many pipes in the line
*	- infile: input redirection - NULL if there's no redirection
*	- outfile: out redirection - NULL if there's no redirection
*	- errfile: error redirection - NULL if there's no redirection
*/
typedef struct s_line
{
	int		ncmds;
	int		nargs;
	int		npipes;
	char	*infile;
	char	*outfile;
	char	*errfile;
	t_cmd	*cmd;
}	t_line;

#endif