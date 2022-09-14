/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fake_string.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 14:09:54 by ommohame          #+#    #+#             */
/*   Updated: 2022/09/14 17:23:34 by ommohame         ###   ########.fr       */
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

int	fake_string(t_cmd **cmd)
{
	size_t	i;
	size_t	j;
	size_t	x;
	char	*exp;
	char	*var;
	char	*fake;
	char	*tmp;

	i = 0;
	j = 0;
	fake = (char *)malloc(sizeof(char) * (ft_strlen((*cmd)->token->token) + 1));
	if (!fake)
		return (-1);
	while ((*cmd)->token->org[i])
	{
		if ((*cmd)->token->org[i] == '$')
		{
			tmp = (*cmd)->token->token;
			(*cmd)->token->token = (*cmd)->token->org + i;
			var = expand_helper(&(*cmd)->token, 1);
			exp = getenv(var);
			if (exp)
			{
				i++;
				x = ft_strlen(exp) + j;
				while (j < x)
					fake[j++] = ' ';
				i += ft_strlen(var);
			}
			(*cmd)->token->token = tmp;
		}
		fake[j] = (*cmd)->token->org[i];
		i++;
		j++;
	}
	free((*cmd)->token->org);
	(*cmd)->token->org = fake;
	return (1);
}
