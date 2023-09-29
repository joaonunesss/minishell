/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 14:33:14 by jmarinho          #+#    #+#             */
/*   Updated: 2023/09/28 15:22:01 by jmarinho         ###   ########.fr       */
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
