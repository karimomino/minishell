/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_quotes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 19:58:44 by ommohame          #+#    #+#             */
/*   Updated: 2022/07/10 16:11:29 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

int	skip_quotes(char *str, int i)
{
	char	c;

	c = str[i];
	i++;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	if (str[i] != c)
		return (-1);
	return (i);
}

/*
* trims the outer quotes
*/
static char	*trim_quotes(char *str, int i, int j)
{
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;
	char	*new;

	tmp1 = ft_substr(str, 0, i);
	tmp2 = ft_substr(str, i + 1, j - i - 1);
	tmp3 = ft_substr(str, j + 1, ft_strlen(str) - j);
	new = ft_strjoin(tmp1, tmp2);
	free(tmp1);
	free(tmp2);
	tmp1 = ft_strjoin(new, tmp3);
	free(tmp3);
	free(new);
	free(str);
	return (tmp1);
}

/*
* search for the close of the quotes
*	- returns -1 if it doesn't find the closing quotes
*/
static int	close_quotes(char **str, int i)
{
	int		j;
	char	c;
	char	*new;

	new = *str;
	c = new[i];
	j = i + 1;
	while (new[j])
	{
		if (new[j] == c)
		{
			*str = trim_quotes(new, i, j);
			return (j);
		}
		j++;
	}
	if (new[j] != c)
		return (-1);
	return (i);
}

/*
* remove spaces outside quotes
*	- returns the new trimmed string
*/
static char	*trim_space(char *str, int i)
{
	int		j;
	char	*trim;
	char	*new;

	j = i + 1;
	while (str[j] == ' ')
		j++;
	trim = ft_substr(str, 0, j);
	new = ft_substr(str, j, ft_strlen(str) - j);
	if (!new || !trim)
	{
		free(str);
		free(trim);
		return (NULL);
	}
	new = ft_strjoin(trim, new);
	return (new);
}

/*
* handles quotes
*	- 34: single quote
*	- 39: double quote
*	- 92: backslash
*/
char	*qoutes(char *str)
{
	int		i;
	char	*new;

	i = 0;
	new = ft_strdup(str);
	while (new[i])
	{
		if (new[i] == 34 || new[i] == 39)
			i = close_quotes(&new, i);
		if (new[i] == ' ')
			new = trim_space(new, i);
		if (i == -1)
			return (NULL);
		if (!new)
			return (NULL);
		i++;
	}
	return (new);
}

// #include <stdio.h>
// int	main(void)
// {
// 	int		i;
// 	char	str[10000];
// 	char	*new;

// 	i = 1;
// 	scanf("%99[^\n]", str);
// 	new = qoutes(str);
// 	printf("%s\n", new);
// }