/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_quotes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 19:58:44 by ommohame          #+#    #+#             */
/*   Updated: 2022/06/17 03:19:19 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

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
	new = ft_strjoin(new, tmp3);
	free(tmp1);
	free(tmp2);
	free(tmp3);
	free(str);
	return (new);
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

	new = ft_strdup(*str);
	c = new[i];
	j = i + 1;
	while (new[j])
	{
		if (new[j] == c && new[j - 1] != 92)
		{
			*str = trim_quotes(new, i, j);
			return (j);
		}
		else if (new[j] == 39 && new[j - 1] == 92)
		{
			new = ft_substr(*str, 0, j - 1);
			new = ft_strjoin(new, *str + j);
			j--;
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

	j = i;
	while (str[j] == ' ')
		j++;
	trim = ft_substr(str, 0, i + 1);
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
		if ((new[i] == 34 || new[i] == 39) && (i == 0 || new[i - 1] != 92))
			i = close_quotes(&new, i);
		if (i == -1)
			return (NULL);
		if (new[i] == ' ')
			new = trim_space(new, i);
		if (!new)
			return (NULL);
		i++;
	}
	return (new);
}

// #include <stdio.h>
// int	main(void)
// {
// 	char	str[10000];
// 	char	*new;

// 	scanf("%99[^\n]", str);
// 	new = qoutes(str);
// 	printf("%s\n", new);
// }
