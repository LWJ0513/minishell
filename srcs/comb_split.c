/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comb_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 17:59:47 by wonlim            #+#    #+#             */
/*   Updated: 2023/02/09 18:00:02 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char * comb_split(char **split, int i)
{
	char *str;
	char *tmp;

	str = malloc(0);
	while (split[i])
	{

		tmp = ft_strjoin(str, split[i]);
		if (str)
			free(str);
		str = ft_strjoin(tmp, " ");
		free(tmp);
		i++;
	}
	return (str);
}