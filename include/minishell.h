/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 21:36:54 by wonlim            #+#    #+#             */
/*   Updated: 2023/02/09 20:32:06 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "readline/history.h"
# include "readline/readline.h"
# include "../libft/libft.h"
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>


typedef struct s_mini
{
	int last_result;
}	t_mini;

int    ft_pwd();
int    ft_cd(char *str);
void	free_split(char **split);
char * comb_split(char **split, int i);


#endif