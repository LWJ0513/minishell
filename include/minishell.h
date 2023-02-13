/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 21:36:54 by wonlim            #+#    #+#             */
/*   Updated: 2023/02/09 21:23:05 by wonlim           ###   ########.fr       */
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

typedef struct s_node
{
	struct	s_node *next;
	char	**command;
	int		result;
}	t_node;

typedef struct s_list
{
	pid_t pid;
	t_node *head;	
}	t_list;

int    ft_pwd();
int    ft_cd(char *str);
void	free_split(char **split);
char * comb_split(char **split, int i);
int	ft_strcmp(char *s1, char *s2);


#endif