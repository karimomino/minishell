/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 21:09:00 by ommohame          #+#    #+#             */
/*   Updated: 2022/06/15 00:54:16 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include <stdio.h>

/*
* counts how many words do I have to use it for malloc
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
		if ((str[i - 1] == ' ' && str[i] != ' ') || i == 0)
			count++;
		if (str[i] == '"' || str[i] == '\'')
		{
			c = str[i++];
			count++;
			while (str[i] != c && str[i])
				i++;
			if (str[i] != c)
				return (-1);
		}
		i++;
	}
	return (count);
}

static int	arg_len(char *str, int i)
{
	char	c;

	c = str[i];
	i++;
	if (c == '"' || c == '\'')
		while (str[i] && str[i] != c)
			i++;
	else
		while (str[i] != ' ' || str[i + 1] == '\'' || str[i + 1] == '"')
			i++;
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
		if (str[i] == ' ' || i == 0 || str[i] == '\'' || str[i] == '"')
		{
			j = i + arg_len(str, i);
			while (str[i] == ' ')
				i++;
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

char	**ft_splitq(char	*str)
{
	int		args_count;
	char	**args;

	args_count = arg_count(str);
	args = (char **)malloc(sizeof(char *) * (args_count + 1));
	if (!args_count)
		return (NULL);
	args = split(args, str, args_count);
	if (!args_count)
		return (NULL);
	return (args);

}


int	main(void)
{
	char 	*str = "111'222 \"  333'444 55";
	char	**args;

	args = ft_splitq(str);
	for (int i = 0; args[i]; i++)
		printf("%s\n", args[i]);
}
