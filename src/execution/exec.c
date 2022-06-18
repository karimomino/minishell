/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 08:17:33 by kamin             #+#    #+#             */
/*   Updated: 2022/06/18 14:46:25 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_builtin(t_cmd in)
{
	int	ret;
	
	ret = 0;
	if (in.type == 0)
	{}
		//CALL TO ECHO FUNCTION
	if (in.type == 1)
	{}
		//CALL TO CD FUNCTION
	if (in.type == 2){}
		//CALL TO PWD FUNCTION
	if (in.type == 3){}
		//CALL TO ENV FUNCTION
	if (in.type == 4){}
		//CALL TO EXPORT FUNCTION
	if (in.type == 5){}
		//CALL TO UNSET FUNCTION
	if (in.type == 6){}
		//CALL TO EXIT FUNCTION
	return (ret);
}

int	exec_bin(t_cmd in)
{
	int	ret;
	pid_t	pid;

	//for testing only, this should be retrieved from environment variable
	char *path = strdup("/usr/bin/");
	path = strncat(path, in.cmd[0], strlen(in.cmd[0]));
	pid = fork();
	ret = 0;
	if (pid == -1)
	{
		return (errno);
	}
	else if (!pid)
	{
		ret = execve(path, in.cmd, in.envp);
		printf("minishell: %s: command not found\n", in.cmd[0]);
		t_infoo.retVal = 127;
		return(t_infoo.retVal);
	}
	else
	{
		wait(&t_infoo.retVal);
	}

	return (ret);
}

int	exec_ft(t_cmd in)
{
	int	ret;
	// char	**cmd;

	in.type = 0;

	//TODO: Exapnd before running the command

	if (in.type)
		ret = exec_builtin(in);
	else
		ret = exec_bin(in);

	return (ret);
}

int main(int ac, char **av, char **envp)
{
	// t_cmd cmd;

	(void)ac;
	(void)av;
	(void)envp;
	// cmd.envp = (char **)malloc(1 * sizeof(char *));
	// cmd.envp = envp;
	// cmd.cmd = (char **)malloc(1 * sizeof(char *));
	// cmd.cmd = ++av;
	// t_infoo.retVal = 0;
	ft_setenv("test", "karim", 0);
	printf("This is test env: %s\n", getenv("test"));
	ft_setenv("test", "amin", 1);
	printf("This is test env: %s\n", getenv("USER"));
	for (int i = 0;environ[i] != NULL;i++)
	{
		printf("%s\n", environ[i]);
	}
	ft_setenv("test",NULL, 2);
	for (int i = 0;environ[i] != NULL;i++)
	{
		printf("%s\n", environ[i]);
	}
	// exec_ft(cmd);
	return (t_infoo.retVal);
}
