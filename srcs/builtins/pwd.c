/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 09:34:24 by ataboada          #+#    #+#             */
/*   Updated: 2023/10/12 12:34:12 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


void	ft_pwd(t_minishell *ms)
{
	char	cwd[200];

	(void) ms;
	if (!is_option_valid(ms))
	{
		g_exit_status = 2;
		exit(g_exit_status); 
	}
	if (getcwd(cwd, sizeof(cwd)))
		printf("%s\n", cwd);
	g_exit_status = 0;
	exit(g_exit_status);
}