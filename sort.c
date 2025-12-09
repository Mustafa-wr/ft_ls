/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 19:48:50 by mradwan           #+#    #+#             */
/*   Updated: 2025/12/09 17:19:42 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	insertion(t_entry *entry, struct stat *sb)
{
	entry->mtime = sb->st_mtime;
	entry->is_directory = S_ISDIR(sb->st_mode);
	entry->mode = sb->st_mode;
	entry->nlink = sb->st_nlink;
	entry->uid = sb->st_uid;
	entry->gid = sb->st_gid;
	entry->size = sb->st_size;
}

t_entry	*new_entry(char *name, char *path, t_options *opts)
{
	t_entry		*entry;
	struct stat	sb;
	char		*tmp;
	char		*fullpath;

	entry = malloc(sizeof(t_entry));
	if (!entry)
		return (NULL);
	entry->name = strdup(name);
	if (!entry->name)
		return (free(entry), NULL);
	entry->mtime = 0;
	entry->is_directory = 0;
	if (opts->t || opts->c_r || opts->l)
	{
		tmp = ft_strjoin(path, "/");
		fullpath = ft_strjoin(tmp, name);
		free(tmp);
		if (fullpath && stat(fullpath, &sb) == 0)
			insertion(entry, &sb);
		free(fullpath);
	}
	entry->next = NULL;
	return (entry);
}

void	add_entry(t_entry **head, t_entry *new)
{
	t_entry	*tmp;

	if (!*head)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
