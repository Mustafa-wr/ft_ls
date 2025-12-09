/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:52:32 by mradwan           #+#    #+#             */
/*   Updated: 2025/12/09 15:34:26 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	print_error(char *path)
{
	write(2, "ls: cannot access '", 19);
	write(2, path, strlen(path));
	write(2, "': ", 3);
	perror("");
}

static int	read_entries(DIR *d, t_entry **head, t_options *opts, char *path)
{
	struct dirent	*ent;
	t_entry			*new;

	ent = readdir(d);
	while (ent)
	{
		if (!opts->a && ent->d_name[0] == '.')
		{
			ent = readdir(d);
			continue ;
		}
		new = new_entry(ent->d_name, path, opts);
		if (!new)
		{
			free_entries(*head);
			return (0);
		}
		add_entry(head, new);
		ent = readdir(d);
	}
	return (1);
}

int	list_directory(char *path, t_options *opts, int print_newline, int silent)
{
	DIR		*d;
	t_entry	*head;

	head = NULL;
	d = opendir(path);
	if (!d)
	{
		if (!silent)
			print_error(path);
		return (1);
	}
	if (!read_entries(d, &head, opts, path))
		return (closedir(d), 1);
	closedir(d);
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

int	main(int ac, char **av)
{
	int			i;
	int			start_index;
	int			path_count;
	t_options	opts;

	ft_bzero(&opts, sizeof(t_options));
	if (!parse_options(ac, av, &opts, &start_index))
		return (1);
	path_count = ac - start_index;
	if (path_count == 0)
		return (list_directory(".", &opts, 0, 0));
	i = start_index;
	while (i < ac)
	{
		if (path_count > 1)
		{
			write(1, av[i], strlen(av[i]));
			write(1, ":\n", 2);
		}
		list_directory(av[i], &opts, i < ac - 1, 0);
		i++;
	}
	return (0);
}
