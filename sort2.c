/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 17:19:21 by mradwan           #+#    #+#             */
/*   Updated: 2025/12/09 17:19:35 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	swap_entries(t_entry *i, t_entry *j)
{
	char	*tmp_name;
	time_t	tmp_mtime;
	int		tmp_isdir;

	tmp_name = i->name;
	i->name = j->name;
	j->name = tmp_name;
	tmp_mtime = i->mtime;
	i->mtime = j->mtime;
	j->mtime = tmp_mtime;
	tmp_isdir = i->is_directory;
	i->is_directory = j->is_directory;
	j->is_directory = tmp_isdir;
}

void	sort_entries(t_entry **head)
{
	t_entry	*i;
	t_entry	*j;

	if (!head || !*head)
		return ;
	i = *head;
	while (i)
	{
		j = i->next;
		while (j)
		{
			if (ft_strcmp(i->name, j->name) > 0)
				swap_entries(i, j);
			j = j->next;
		}
		i = i->next;
	}
}

void	sort_entries_by_time(t_entry **head)
{
	t_entry	*i;
	t_entry	*j;

	if (!head || !*head)
		return ;
	i = *head;
	while (i)
	{
		j = i->next;
		while (j)
		{
			if (i->mtime < j->mtime)
				swap_entries(i, j);
			j = j->next;
		}
		i = i->next;
	}
}

void	reverse_entries(t_entry **head)
{
	t_entry	*prev;
	t_entry	*curr;
	t_entry	*next;

	if (!head || !*head)
		return ;
	prev = NULL;
	curr = *head;
	while (curr)
	{
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	*head = prev;
}