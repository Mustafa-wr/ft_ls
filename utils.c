/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 19:53:47 by mradwan           #+#    #+#             */
/*   Updated: 2025/12/08 20:38:08 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void print_entries(t_entry *head)
{
    while (head)
    {
        write(1, head->name, strlen(head->name));
        write(1, "\n", 1);
        head = head->next;
    }
}

void free_entries(t_entry *head)
{
    t_entry *tmp;
    
    while (head)
    {
        tmp = head;
        head = head->next;
        free(tmp->name);
        free(tmp);
    }
}