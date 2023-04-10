/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remake_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 20:34:15 by wonlim            #+#    #+#             */
/*   Updated: 2023/04/10 21:38:34 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*remake_str(t_cmd *node)
{
	char	*str;
	int		len;
	int		i;
	int		j;
	int		k;

	len = 0;
	i = 0;
	if (!node->content)
		return (0);
	while (node->content[i])
		len += ft_strlen(node->content[i++]) + 1;
	str = malloc(len);
	i = 0;
	k = 0;
	while (node->content[i])
	{
		j = 0;
		while (node->content[i][j])
			str[k++] = node->content[i][j++];
		i++;
	}
	str[k] = '\0';
	return (str);
}
