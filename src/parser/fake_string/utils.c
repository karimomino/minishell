/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 04:14:28 by ommohame          #+#    #+#             */
/*   Updated: 2022/09/16 04:51:20 by ommohame         ###   ########.fr       */
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

int	to_expandd(char c)
{
	int			ret;
	static int	dqq;
	static int	sqq;
	static int	firstt;

	ret = 0;
	if (c == '\0')
	{
		dqq = 0;
		sqq = 0;
		firstt = 0;
		return (ret);
	}
	if (firstt == 0 && (c == '"' || c == '\''))
		firstt = c;
	else if (firstt != 0 && (char)firstt == c)
		firstt = 0;
	if (firstt != '\'' && !check_charr(c, &dqq, &sqq)
		&& ((c == '$' && dqq == 1)
			|| (c == '$' && sqq == 0 && dqq == 0)))
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
