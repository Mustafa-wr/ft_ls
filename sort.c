/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 19:48:50 by mradwan           #+#    #+#             */
/*   Updated: 2025/12/08 20:03:55 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_entry *new_entry(char *name)
{
    t_entry *entry;
    
    entry = malloc(sizeof(t_entry));
    if (!entry)
        return (NULL);
    entry->name = ft_strdup(name);  // Or use your ft_strdup
    if (!entry->name)
    {
        free(entry);
        return (NULL);
    }
    entry->next = NULL;
    return (entry);
}

void    add_entry(t_entry **head, t_entry *new)
{
    t_entry *tmp;
    
    if (!*head)
    {
        *head = new;
        return;
    }
    tmp = *head;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}

static int ft_strcmp(const char *s1, const char *s2)
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
    t_entry *i;
    t_entry *j;
    char    *tmp;
    
    if (!*head)
        return;
    i = *head;
    while (i)
    {
        j = i->next;
        while (j)
        {
            if (ft_strcmp(i->name, j->name) > 0)
            {
                tmp = i->name;
                i->name = j->name;
                j->name = tmp;
            }
            j = j->next;
        }
        i = i->next;
    }
}

void reverse_entries(t_entry **head)
{
    t_entry *prev;
    t_entry *curr;
    t_entry *next;

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