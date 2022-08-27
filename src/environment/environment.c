/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 01:54:06 by kamin             #+#    #+#             */
/*   Updated: 2022/08/23 16:11:42 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static void	add_node(t_environ **head, char *var, char *val)
// {
// 	t_environ *new_node;
// 	new_node = (t_environ *) calloc(1, sizeof(t_environ));
// 	t_environ *last;
// 	last = *head;
// 	new_node->val  = ft_strdup(val);
// 	new_node->var  = ft_strdup(var);
// 	new_node->next = NULL;
// 	if (*head == NULL)
// 	{
// 		*head = new_node;
// 		return ;
// 	}
// 	while (last->next != NULL)
// 		last = last->next;
// 	last->next = new_node;
// 	return ;
// }

int	add_to_env(char *val)
{
	char	**env;
	int		c_size;
	int	i;

	i = -1;
	c_size = 0;
	while (environ != NULL && environ[c_size++]);
	env = (char **)malloc((c_size + 2) * sizeof(char *));
	if (!env)
		return (-1);
	while(environ[++i]);
		// env[i] = (environ[i]);
	environ[i++] = ft_strdup(val);
	environ[i] = NULL;
	// free_2d(environ);
	// environ = env;
	return (-1);
}

void	init_environment(void)
{
	char	**env;
	char	buff[MAX_PATH];
	int		c_size;
	int			i;

	c_size = -1;
	i = -1;
	while (environ != NULL && environ[++c_size]);
	if (c_size > 0)
	{
		env = (char **)malloc((c_size + 1) * sizeof(char *));
		while(environ[++i])
			env[i] = (environ[i]);
		env[i] = NULL;
	}
	else
	{
		env = (char **)malloc((3) * sizeof(char *));
		env[0] = ft_strjoin("PWD=", getcwd(buff, MAX_PATH));
		env[1] = ft_strdup("SHLVL=1");
		env[2] = NULL;
	}
	environ = env;
}
