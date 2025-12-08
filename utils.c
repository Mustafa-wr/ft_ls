/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 19:53:47 by mradwan           #+#    #+#             */
/*   Updated: 2025/12/08 23:27:30 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_entries(t_entry *head)
{
	while (head)
	{
		write(1, head->name, strlen(head->name));
		write(1, "\n", 1);
		head = head->next;
	}
}

void	free_entries(t_entry *head)
{
	t_entry	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->name);
		free(tmp);
	}
}

void	list_recursively(char *path, t_options *opts, t_entry *head)
{
	t_entry	*current;
	char	*subpath;
	char	*tmp;
	DIR		*test;

	current = head;
	while (current)
	{
		if (current->is_directory && ft_strcmp(current->name, ".") != 0
			&& ft_strcmp(current->name, "..") != 0)
		{
			tmp = ft_strjoin(path, "/");
			subpath = ft_strjoin(tmp, current->name);
			free(tmp);
			if (subpath)
			{
				test = opendir(subpath);
				if (test)
				{
					closedir(test);
					write(1, "\n", 1);
					write(1, subpath, ft_strlen(subpath));
					write(1, ":\n", 2);
					list_directory(subpath, opts, 0, 1);
				}
				free(subpath);
			}
		}
		current = current->next;
	}
}
