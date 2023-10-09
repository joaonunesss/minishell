/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 09:34:24 by ataboada          #+#    #+#             */
/*   Updated: 2023/10/09 16:13:20 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_pwd(t_minishell *ms)
{
	char	cwd[200];

	if (getcwd(cwd, sizeof(cwd)))
		printf("%s\n", cwd);
	if (ms->n_pipes == 0)
		exit(0);
}