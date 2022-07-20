/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 16:40:53 by ommohame          #+#    #+#             */
/*   Updated: 2022/07/20 20:02:48 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

void	free_ret(char **ret)
{
	int		j;

	j = 0;
	while (j < 3)
	{
		if (ret[j])
			free(ret[j]);
		j++;
	}
	free (ret);
}

int	ramadan_redir(char *str, char ***ret, int *i)
{
	if (define_redir(str, &(*ret)[2], &*i) == -1)
	{
		free_ret(*ret);
		return (-1);
	}
	if (str[*i] == '>' || str[*i] == '<')
		*i = *i - 1;
	return (1);
}

int	ramadan_cmd(char *str, char ***ret, int *i)
{
	if (get_cmd(str, &(*ret)[0], &*i) == -1)
	{
		free_ret(*ret);
		return (-1);
	}
	return (1);
}

int	ramadan_args(char *str, char ***ret, int *i)
{
	if (get_args(str, &(*ret)[1], &*i) == -1)
	{
		free_ret(*ret);
		return (-1);
	}
	return (1);
}

char	**parse(char *str)
{
	int		i;
	char	**ret;

	i = 0;
	ret = (char **)ft_calloc(4, sizeof(char *));
	if (!ret)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '>' || str[i] == '<')
		{
			if (ramadan_redir(str, &ret, &i) == -1)
				return (NULL);
		}
		else if (str[i] != ' ' && str[i] != '>' && str[i] != '<')
		{
			if (!ret[0])
			{
				if (ramadan_cmd(str, &ret, &i) == -1)
					return (NULL);
			}
			else
			{
				if (ramadan_args(str, &ret, &i) == -1)
					return (NULL);
			}
		}
		if (!str[i++])
			return (ret);
	}
	return (ret);
}
