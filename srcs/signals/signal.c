/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:57:17 by jmarinho          #+#    #+#             */
/*   Updated: 2023/10/12 16:44:47 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_signals_heredoc(void)
{
	signal(SIGINT, ft_handler_heredoc);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_signals_child(void)
{
	signal(SIGINT, ft_handler_child);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_signals(void)
{
	signal(SIGINT, ft_handler_sigint);
	signal(SIGQUIT, SIG_IGN);
}

// void	ft_signals_ignore(void)
// {
// 	signal(SIGINT, SIG_IGN);
// 	signal(SIGQUIT, SIG_IGN);
// }
