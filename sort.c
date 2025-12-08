/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 19:48:50 by mradwan           #+#    #+#             */
/*   Updated: 2025/12/08 23:26:14 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_entry *new_entry(char *name, char *path, t_options *opts)
{
    t_entry     *entry;
    struct stat sb;
    char        *tmp;
    char        *fullpath;

    entry = malloc(sizeof(t_entry));
    if (!entry)
        return (NULL);
    entry->name = strdup(name);
    if (!entry->name)
        return (free(entry), NULL);
    entry->mtime = 0;
    entry->is_directory = 0;
    if (opts->t || opts->c_r)
    {
        tmp = ft_strjoin(path, "/");
        fullpath = ft_strjoin(tmp, name);
        free(tmp);
        if (fullpath && stat(fullpath, &sb) == 0)
        {
            entry->mtime = sb.st_mtime;
            entry->is_directory = S_ISDIR(sb.st_mode);
        }
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

void sort_entries(t_entry **head)
{
    t_entry *i, *j;
    char    *tmp_name;
    time_t  tmp_mtime;
    int     tmp_isdir;

    if (!head || !*head)
        return;
    i = *head;
    while (i)
    {
        j = i->next;
        while (j)
        {
            if (ft_strcmp(i->name, j->name) > 0)
            {
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
            j = j->next;
        }
        i = i->next;
    }
}


// static void swap(t_entry *i, t_entry *j, time_t *tmp_time, char	**tmp_name)
// {
// 	*tmp_name = i->name;
// 	i->name = j->name;
// 	j->name = *tmp_name;
// 	*tmp_time = i->mtime;
// 	i->mtime = j->mtime;
// 	j->mtime = *tmp_time;
// }

void sort_entries_by_time(t_entry **head)
{
    t_entry *i, *j;
    char    *tmp_name;
    time_t  tmp_mtime;
    int     tmp_isdir;

    if (!head || !*head)
        return;
    i = *head;
    while (i)
    {
        j = i->next;
        while (j)
        {
            if (i->mtime < j->mtime)
            {
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
            j = j->next;
        }
        i = i->next;
    }
}


void reverse_entries(t_entry **head)
{
    t_entry *prev, *curr, *next;

    if (!head || !*head)
        return;
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
