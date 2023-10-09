/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 14:33:14 by jmarinho          #+#    #+#             */
/*   Updated: 2023/10/09 17:41:13 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char *ft_find_env(t_env *env_lst, char *find)
{
	t_env	*current;

	current = env_lst;
	while (current)
	{
		if (!ft_strncmp(current->key, find, ft_strlen(current->key) + 1))
			return (current->value);
		current = current->next;
	}
	return (NULL);
}


void	ft_update_env(t_env **env_lst, char *key, char *update)
{
	t_env	*current;

	current = *env_lst;
	while (current)
	{
		if (!ft_strncmp(current->key, key, ft_strlen(current->key)))
		{
			free(current->value);
			current->value = update;
			break ;
		}
		current = current->next;
	}
}

char ft_strchr2(const char *str, char c)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == c)
			return (str[i]);
	}
	if (str[i] == c)
		return (str[i]);
	return (0);
}

void	ft_lstadd_back2(t_env *env_lst, t_env *new_envi)
{
	t_env	*ptr;

	ptr = env_lst;
	if (env_lst)
	{
		if (!(env_lst))
		{
			env_lst = new_envi;
		}
		else
		{
			while (ptr->next != NULL)
			{
				ptr = ptr->next;
			}
			ptr->next = new_envi;
		}
	}
}

bool ft_not_forkable(t_minishell *ms)
{
    	if (ft_strncmp(ms->cmd_lst->cmd, "export", 7) == 0)
		{
			ft_export(ms);
			return (TRUE);
		}
		else if (ft_strncmp(ms->cmd_lst->cmd, "unset", 6) == 0)
		{
			ft_unset(ms);
			return (TRUE);
		}
		else if (ft_strncmp(ms->cmd_lst->cmd, "cd", 3) == 0)
		{
			ft_cd(ms);
			return (TRUE);
		}
		else if (ft_strncmp(ms->cmd_lst->cmd, "exit", 5) == 0)
		{
			ft_exit(ms);
			return (TRUE);
		}
		return(FALSE);
}
