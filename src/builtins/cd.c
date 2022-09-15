/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:28:47 by kamin             #+#    #+#             */
/*   Updated: 2022/09/15 18:46:05 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_error(char *token)
{
	int			is_dir;
	int			exists;
	char		*err;
	struct stat	info;

	stat(token, &info);
	is_dir = S_ISDIR(info.st_mode);
	exists = access(token, F_OK);
	if (!is_dir)
		errno = ENOTDIR;
	else if (exists)
		errno = ENOENT;
	else
		errno = EACCES;
	err = ft_strjoin("minishell: cd: ", token);
	perror(err);
	free(err);
}

static int	update_oldpwd(void)
{
	char	cwd[MAX_PATH];
	char	*oldpwd;

	if (getcwd(cwd, MAX_PATH) == NULL)
		return (ERROR);
	oldpwd = getenv("OLDPWD");
	if (oldpwd)
		ft_setenv("OLDPWD", cwd, 1);
	else
		ft_setenv("OLDPWD", cwd, 0);
	return (SUCCESS);
}

static int	go_special(char **path, int flag)
{
	if (flag == 0)
	{
		*path = getenv("HOME");
		if (!*path)
		{
			ft_putstr_fd("minishell : cd: HOME not set\n", 2);
			return (1);
		}
		update_oldpwd();
	}
	else if (flag == 1)
	{
		*path = getenv("OLDPWD");
		if (!*path)
		{
			ft_putstr_fd("minishell : cd: OLDPWD not set\n", 2);
			return (1);
		}
		ft_putendl_fd(*path, 1);
		update_oldpwd();
	}
	return (0);
}

static int	go(int flag)
{
	int		ret;
	char	*path;
	char	cwd[MAX_PATH];

	ret = go_special(&path, flag);
	if (!ret)
	{
		ret = chdir(path);
		getcwd(cwd, MAX_PATH);
		if (getenv("PWD"))
			ft_setenv("PWD", cwd, 1);
	}
	return (ret);
}

int	ft_cd(t_cmd *cmd)
{
	int		ret;
	char	cwd[MAX_PATH];

	if (cmd->nargs == 1)
		return (go(HOMEFLAG));
	if (ft_strcmp(cmd->token->next->token, (char *)"-") == 0)
		ret = go(OLDPWDFLAG);
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
