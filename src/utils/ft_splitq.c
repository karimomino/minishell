/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitq.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 21:09:00 by ommohame          #+#    #+#             */
/*   Updated: 2022/07/10 15:38:57 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include <stdio.h>

/*
* counts how many args do I have to use it for malloc
*/
static int	arg_count(char *str)
{
	int		count;
	size_t	i;
	char	c;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] == ' ')
				i++;
		if (str[i] == '\0')
			return (count);
		else if (str[i] == '"' || str[i] == '\'')
		{
			c = str[i++];
			count++;
			while (str[i] != c && str[i])
				i++;
			if (str[i] != c)
				return (-1);
		}
		else if ((str[i - 1] == ' ' && str[i] != ' ')
			|| str[i - 1] == '\'' || str[i - 1] == '"' || i == 0)
			count++;
		i++;
	}
	return (count);
}

static int	arg_len(char *str, int i)
{
	char	c;

	c = str[i++];
	if (c == '"' || c == '\'')
	{
		while (str[i] && str[i] != c)
			i++;
		i++;
	}
	else
	{
		while (str[i] != ' ' && str[i] != '\'' && str[i] != '"' && str[i] && str[i + 1] != ' ')
			i++;
	}
	return (i);
}

static char	**split(char **args, char *str, int args_count)
{
	int		i;
	int		j;
	int		x;

	i = 0;
	x = 0;
	while (x < args_count && str[i])
	{
		if (str[i] == '\'' || str[i] == '"' || str[i] == ' ' || i == 0
			|| str[i - 1] == '\'' || str[i - 1] == '"')
		{
			if (str[i] == ' ')
				while (str[i] == ' ' && str[i + 1] != ' ')
					i++;
			j = arg_len(str, i);
			args[x] = (char *)malloc(sizeof(char) * (j - i + 1));
			if (!args[x])
				return (NULL);
			ft_strlcpy(args[x], str + i, j - i + 1);
			i = j - 1;
			x++;
		}
		i++;
	}
	args[x] = NULL;
	return (args);
}

/*
* 	split by space and quotes
*		- if there's quotes it takes the whole quotes as a string
		- if not it ignores the space
*/
char	**ft_splitq(char *str)
{
	int		args_count;
	char	**args;

	args_count = arg_count(str);
	args = (char **)malloc(sizeof(char *) * (args_count + 1));
	if (!args)
		return (NULL);
	args = split(args, str, args_count);
	return (args);
}
