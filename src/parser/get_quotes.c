/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_quotes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 19:58:44 by ommohame          #+#    #+#             */
/*   Updated: 2022/09/11 21:30:34 by ommohame         ###   ########.fr       */
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

static int	trim_quotes(char **str, int i, int j)
{
	int		ret;
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;
	char	*new;

	tmp1 = ft_substr(*str, 0, i);
	tmp2 = ft_substr(*str, i + 1, j - i - 1);
	tmp3 = ft_substr(*str, j + 1, ft_strlen(*str) - j);
	ret = ft_strlen(tmp1) + ft_strlen(tmp2) - 1;
	new = alpha_strjoin(3, tmp1, tmp2, tmp3);
	free(tmp1);
	free(tmp2);
	free(tmp3);
	free(*str);
	*str = new;
	return (ret);
}

static int	close_quotes(char **str, int i)
{
	int		j;
	char	c;

	c = (*str)[i];
	j = i + 1;
	while ((*str)[j])
	{
		if ((*str)[j] == c)
		{
			return (trim_quotes(str, i, j) - 1);
		}
		j++;
	}
	return (i);
}

void	quotes(char **str)
{
	int		i;

	i = 0;
	if (!*str)
		return ;
	while ((*str)[i])
	{
		if ((*str)[i] == 34 || (*str)[i] == 39)
			i = close_quotes(str, i);
		i++;
	}
}

void	remove_all_quotes(t_line **line)
{
	t_cmd		*head;
	t_token		*head_t;
	t_redir		*head_r;

	head = (*line)->cmd;
	while ((*line)->cmd)
	{
		head_t = (*line)->cmd->token;
		head_r = (*line)->cmd->redir;
		while ((*line)->cmd->token)
		{
			quotes(&(*line)->cmd->token->token);
			(*line)->cmd->token = (*line)->cmd->token->next;
		}
		while ((*line)->cmd->redir)
		{
			quotes(&(*line)->cmd->redir->file);
			(*line)->cmd->redir = (*line)->cmd->redir->next;
		}
		(*line)->cmd->token = head_t;
		(*line)->cmd->redir = head_r;
		(*line)->cmd = (*line)->cmd->next;
	}
	(*line)->cmd = head;
}

// # include <readline/readline.h>
// # include <readline/history.h>
// #include <stdio.h>
// int	main(void)
// {
// 	char	*str;
// 	char	*new;

// 	ft_strlen(NULL);
// 	while (1)
// 	{
// 		str = readline("hi: ");
// 		new = qoutes(str);
// 		printf("%s\n", new);
// 		free(new);
// 	}
// }
