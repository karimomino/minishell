/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 17:51:33 by kamin             #+#    #+#             */
/*   Updated: 2022/08/23 16:05:57 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ret_err(t_cmd in)
{
	char	*err;

	err = ft_strdup("minishell: ");
	err = ft_strlcat(err, in.cmd[0]);
}
