/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:28:47 by kamin             #+#    #+#             */
/*   Updated: 2022/08/27 20:55:50 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_error(char *token)
{
	int		is_file;
	char	*err;
	char	*tmp;

	is_file = access(token, F_OK);
	if (is_file)
		errno = 2;
	else
		errno = 20;
	tmp = ft_strjoin("minishell: cd: ", token);
	err = ft_strjoin(tmp, ": ");
	free(tmp);
	perror(err);
	free(err);
}

static int	update_oldpwd(void)
{
	char	cwd[4096];
	char	*oldpwd;

	if (getcwd(cwd, 4096) == NULL)
		return (ERROR);
	oldpwd = getenv("OLDPWD");
	if (oldpwd)
		ft_setenv("OLDPWD", cwd, 1);
	else
		ft_setenv("OLDPWD", cwd, 0);
	return (SUCCESS);
}

static int	go(int flag)
{
	int		ret;
	char	*go_path;

	if (flag == 0)
	{
		go_path = getenv("HOME");
		if (!go_path)
		{
			ft_putstr_fd("minishell : cd: HOME not set", 2);
			return (ERROR);
		}
		update_oldpwd();
	}
	else if (flag == 1)
	{
		go_path = getenv("OLDPWD");
		if (!go_path)
		{
			ft_putstr_fd("minishell : cd: OLDPWD not set", 2);
			return (ERROR);
		}
		update_oldpwd();
	}
	ret = chdir(go_path);
	return (ret);
}

int	ft_cd(t_cmd *cmd)
{
	int		ret;
	char	cwd[MAX_PATH];

	if (cmd->nargs == 1)
		return (go(HOMEFLAG));
	if (ft_strcmp(cmd->token->next->token, (char *)"-") == 0)
	{
		ret = go(OLDPWDFLAG);
	}
	else
	{
		update_oldpwd();
		ret = chdir(cmd->token->next->token);
		if (ret < 0)
			ret = 1;
		if (ret != 0)
			print_error(cmd->token->next->token);
		if (!ret)
		{
			getcwd(cwd, MAX_PATH);
			ft_setenv("PWD", cwd, 1);
		}
	}
	return (ret);
}
