/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 04:14:28 by ommohame          #+#    #+#             */
/*   Updated: 2022/09/16 21:05:26 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parser.h"

int	check_charr(char c, int *dq, int *sq)
{
	int	ret;

	ret = 0;
	if (c == '"')
	{
		(*dq)++;
		if (*dq > 1)
			*dq = 0;
		ret = 1;
	}
	else if (c == '\'')
	{
		(*sq)++;
		if (*sq > 1)
			*sq = 0;
		ret = 1;
	}
	return (ret);
}

int	to_expandd(char c, char next)
{
	int			ret;
	static int	dq;
	static int	sq;
	static int	first;

	ret = 0;
	if (c == '\0')
	{
		dq = 0;
		sq = 0;
		first = 0;
		return (ret);
	}
	if (first == 0 && (c == '"' || c == '\''))
		first = c;
	else if (first != 0 && (char)first == c)
		first = 0;
	if (!check_char(c, &dq, &sq) && first != '\''
		&& ((c == '$' && dq == 1 && !ft_strchr("\"\'\0",next))
			|| (c == '$' && sq == 0 && dq == 0)))
			ret = 1;
	return (ret);
}

char	*expand_helper(char *string)
{
	int		i;
	char	*var;

	i = 0;
	if (!string)
		return (NULL);
	while (string[i] != '\0' && string[i] != '$')
		i++;
	if (string[i] == '\0')
		return (NULL);
	var = ft_substr(string + i + 1, 0, stopper_finder(string + i + 1));
	return (var);
}

char	*get_expanded_value(char *var, int exit_code)
{
	if (!ft_strcmp(var, "?"))
		return (ft_itoa(exit_code));
	else
		return (getenv(var));
}

void	replace_fake_string_exp(char **fake, char *exp, size_t *j)
{
	size_t	x;

	x = ft_strlen(exp);
	while (x > 0)
	{
		(*fake)[(*j)++] = '\0';
		x--;
	}
}
