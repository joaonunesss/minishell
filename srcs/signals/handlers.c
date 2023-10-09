/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:01:57 by jmarinho          #+#    #+#             */
/*   Updated: 2023/10/06 17:12:45 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_handler_sigint(int signum)
{
	if (signum != SIGINT)
		return ;
	rl_replace_line("", 0);
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
	g_exit_status = 130;
}

void	ft_handler_heredoc(int signum)
{
	if (signum != SIGINT)
		return ;
	printf("\n");
	g_exit_status = 130;
}

void	ft_handler_child(int signum)
{
	if (signum == SIGINT)
		return ;
	else if (signum == SIGQUIT)
		ft_exit(NULL);
	g_exit_status = 128 + signum;
}
