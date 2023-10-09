/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 09:31:45 by ataboada          #+#    #+#             */
/*   Updated: 2023/10/09 17:46:35 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_cd(t_minishell *ms)
{
	char	currentdir[200];
	char	*old_dir;
	
	old_dir = ft_find_env(ms->env_lst, "OLDPWD");
	getcwd(currentdir, sizeof(currentdir));
	if (ms->cmd_lst->args[1] && ms->cmd_lst->args[1][0] != '~')
	{
		if (ft_strlen(ms->cmd_lst->args[1]) == 1 && ms->cmd_lst->args[1][0] == '-')
		{
			printf("%s\n", old_dir);
			chdir(old_dir);
		}
		else
			chdir(ms->cmd_lst->args[1]);
	}
	else if (!ms->cmd_lst->args[1] || ms->cmd_lst->args[1][0] == '~')
		chdir(ft_find_env(ms->env_lst, "HOME"));
	old_dir = currentdir;
	ft_update_env(&ms->env_lst, "OLDPWD", ft_strdup(currentdir));
	getcwd(currentdir, sizeof(currentdir));
	ft_update_env(&ms->env_lst, "PWD", ft_strdup(currentdir));
	if (ms->n_pipes != 0)
		exit(0);
}
