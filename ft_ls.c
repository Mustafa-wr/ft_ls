/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:52:32 by mradwan           #+#    #+#             */
/*   Updated: 2025/12/09 17:30:25 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_error(char *path)
{
	write(2, "ls: cannot access '", 19);
	write(2, path, strlen(path));
	write(2, "': ", 3);
	perror("");
}

int	read_entries(DIR *d, t_entry **head, t_options *opts, char *path)
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

void	print_entries_long(t_entry *head)
{
	t_entry			*current;
	char			*perms;
	char			*time_str;
	struct passwd	*pwd;
	struct group	*grp;

	current = head;
	while (current)
	{
		perms = format_permissions(current->mode);
		time_str = format_time(current->mtime);
		pwd = getpwuid(current->uid);
		grp = getgrgid(current->gid);
		if (perms && time_str && pwd && grp)
			ft_printf("%s %2lu %-8s %-8s %5lld %s %s\n", perms,
				(unsigned long)current->nlink, pwd->pw_name, grp->gr_name,
				(long long)current->size, time_str, current->name);
		free(perms);
		free(time_str);
		current = current->next;
	}
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
