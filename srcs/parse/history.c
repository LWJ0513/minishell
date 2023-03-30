/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonlim <wonlim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 00:09:52 by wonlim            #+#    #+#             */
/*   Updated: 2023/03/10 00:51:01 by wonlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	history(t_mini *mini)
{
	if (!mini->pipe_flag)
		add_history(mini->line);
	else
		add_history(mini->line2);
}
