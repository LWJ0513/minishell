/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 15:20:38 by wonlim            #+#    #+#             */
/*   Updated: 2023/02/09 21:22:46 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strcmp(char *s1, char *s2)
{
	int	i;
	int	size;

	size = 0;
	while (s1[size])
		size++;
	++size;
	i = 0;
	while (i < size)
	{
		if (s1[i] == s2[i])
		{
			if (s1[i] == '\0')
				return (0);
			i++;
		}
		else
			return (s1[i] - s2[i]);
	}
	return (0);
}