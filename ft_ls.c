/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:52:32 by mradwan           #+#    #+#             */
/*   Updated: 2025/12/08 20:10:18 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_option_error(char c)
{
	write(2, "ls: illegal option -- ", 22);
	write(2, &c, 1);
	write(2, "\n", 1);
}

int	parse_option_string(char *str, t_options *opts)
{
	int	j;

	j = 1;
	while (str[j])
	{
		if (str[j] == 'l')
			opts->l = 1;
		else if (str[j] == 'R')
			opts->c_r = 1;
		else if (str[j] == 'a')
			opts->a = 1;
		else if (str[j] == 't')
			opts->t = 1;
		else if (str[j] == 'r')
			opts->r = 1;
		else
			return (print_option_error(str[j]), 0);
		j++;
	}
	return (1);
}

int	parse_options(int ac, char **av, t_options *opts, int *start_index)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (av[i][0] == '-' && av[i][1] != '\0')
		{
			if (!parse_option_string(av[i], opts))
				return (0);
		}
		else
		{
			*start_index = i;
			return (1);
		}
		i++;
	}
	*start_index = ac;
	return (1);
}

static void print_error(char *path)
{
    write(2, "ls: cannot access '", 19);
    write(2, path, strlen(path));
    write(2, "': ", 3);
    perror("");
}

static int read_entries(DIR *d, t_entry **head, t_options *opts)
{
    struct dirent   *ent;
    t_entry         *new;

    while ((ent = readdir(d)) != NULL)
    {
        if (!opts->a && ent->d_name[0] == '.')
            continue;
        new = new_entry(ent->d_name);
        if (!new)
        {
            free_entries(*head);
            return (0);
        }
        add_entry(head, new);
    }
    return (1);
}

int list_directory(char *path, t_options *opts)
{
    DIR     *d;
    t_entry *head;

    head = NULL;
    d = opendir(path);
    if (!d)
        return (print_error(path), 1);
    if (!read_entries(d, &head, opts))
        return (closedir(d), 1);
    closedir(d);
    sort_entries(&head);
    if (opts->r)
        reverse_entries(&head);
    print_entries(head);
    free_entries(head);
    return (0);
}

int main(int ac, char **av)
{
    int         start_index;
    t_options   opts;
    
    ft_bzero(&opts, sizeof(t_options));
    if (!parse_options(ac, av, &opts, &start_index))
        return (1);
    
    if (start_index < ac)
        return (list_directory(av[start_index], &opts));
    else
        return (list_directory(".", &opts));
}
