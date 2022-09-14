/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fake_string.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@42abudhabi.ae>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 14:09:54 by ommohame          #+#    #+#             */
/*   Updated: 2022/09/14 21:13:53 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

static int	stopper_finder(char *tok)
{
	int	i;

	i = -1;
	while (!ft_strchr(" $?\'\"\0", tok[++i]))
		;
	if (i == 0)
		i++;
	return (i);
}

static char	*expand_helper(void *cmd, int flag)
{
	int		i;
	char	*var;
	char	*string;

	i = 0;
	if (flag)
		string = (*(t_token **)cmd)->token;
	else
		string = (*(t_redir **)cmd)->file;
	if (!string)
		return (NULL);
	while (string[i] != '\0' && string[i] != '$')
		i++;
	if (string[i] == '\0')
		return (NULL);
	var = ft_substr(string + i + 1, 0, stopper_finder(string + i + 1));
	return (var);
}

// int	fake_string(t_line *line)
// {
// 	size_t	org_i;
// 	size_t	fake_i;
// 	size_t	var_size;
// 	char	*fake;
// 	char	*tmp;
// 	char	*var;
// 	char	*exp;

// 	org_i = 0;
// 	fake_i = 0;
// 	var_size = ft_strlen(line->cmd->token->token) + 1;
// 	fake = (char *)ft_calloc(var_size, sizeof(char));
// 	if (!fake)
// 		return (-1);
// 	while(line->cmd->token->org[org_i])
// 	{
// 		if (line->cmd->token->org[org_i] == '$')
// 		{
// 			tmp = line->cmd->token->token;
// 			line->cmd->token->token = line->cmd->token->org + org_i;
// 			var = expand_helper(&line->cmd->token, 1);
// 			if (!ft_strcmp(var, "?"))
// 				exp = ft_itoa(line->exit);
// 			else
// 				exp = getenv(var);
// 			if (exp)
// 			{
// 				org_i++;
// 				var_size = ft_strlen(exp);
// 				while (var_size--)
// 					fake[fake_i++] = '#';
// 				org_i += ft_strlen(var) + 1;
// 			}
// 			else
// 				org_i += ft_strlen(var) + 1;
// 		}
// 		else
// 		{
// 			fake[fake_i] = line->cmd->token->org[org_i];
// 			org_i++;
// 			fake_i++;
// 		}
// 	}
// 	fake[fake_i] = '\0';
// 	free(line->cmd->token->org);
// 	line->cmd->token->org = ft_strdup(fake);
// 	return (1);
// }

int	fake_string(t_cmd **cmd)
{
	size_t	i;
	size_t	j;
	ssize_t	x;
	char	*exp;
	char	*var;
	char	*fake;
	char	*tmp;

	i = 0;
	j = 0;
	fake = (char *)ft_calloc((ft_strlen((*cmd)->token->token) + 1), sizeof(char));
	if (!fake)
		return (-1);
	while ((*cmd)->token->org[i])
	{
		if ((*cmd)->token->org[i] == '$')
		{
			tmp = (*cmd)->token->token;
			(*cmd)->token->token = (*cmd)->token->org + i;
			var = expand_helper(&(*cmd)->token, 1);
			if (!ft_strcmp(var, "?"))
				exp = ft_itoa(123);
			else
				exp = getenv(var);
			if (exp)
			{
				i++;
				x = ft_strlen(exp);
				while (x > 0)
				{
					fake[j++] = '#';
					x--;
				}
				i += ft_strlen(var);
			}
			else
				i += ft_strlen(var) + 1;
			(*cmd)->token->token = tmp;
		}
		else
		{
			fake[j] = (*cmd)->token->org[i];
			i++;
			j++;
		}
	}
	fake[j] = '\0';
	free((*cmd)->token->org);
	(*cmd)->token->org = ft_strdup(fake);
	return (1);
}
