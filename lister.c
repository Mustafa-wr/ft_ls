/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lister.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 17:24:51 by mradwan           #+#    #+#             */
/*   Updated: 2025/12/15 18:39:00 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	open_and_read(char *path, DIR **d, t_entry **head, t_options *opts)
{
	*d = opendir(path);
	if (!*d)
	{
		print_error(path);
		return (0);
	}
	if (!read_entries(*d, head, opts, path))
		return (closedir(*d), 0);
	closedir(*d);
	return (1);
}

int	list_directory(char *path, t_options *opts, int print_newline, int silent)
{
	DIR		*d;
	t_entry	*head;

	head = NULL;
	(void)silent;
	if (!open_and_read(path, &d, &head, opts))
		return (1);
	if (opts->t)
		sort_entries_by_time(&head);
	else
		sort_entries(&head);
	if (opts->r)
		reverse_entries(&head);
	if (opts->l)
		print_entries_long(head);
	else
		print_entries(head);
	if (opts->c_r)
		list_recursively(path, opts, head);
	free_entries(head);
	if (print_newline)
		write(1, "\n", 1);
	return (0);
}
