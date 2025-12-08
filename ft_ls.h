/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:59:14 by mradwan           #+#    #+#             */
/*   Updated: 2025/12/08 20:58:47 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H

# include <dirent.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <sys/stat.h>
# include <time.h>
# include "libft/libft.h"

# define FT_LS_H

# define FLAG_L

typedef struct s_options
{
	int l; // long format    (-l)
	int c_r; // recursive      (-R)
	int a; // all/hidden     (-a)
	int r; // reverse        (-r)
	int t; // time sort      (-t)
}	t_options;

typedef struct s_entry
{
    char            *name;
    struct s_entry  *next;
	time_t			mtime;
}   t_entry;

t_entry	*new_entry(char *name, char *path, t_options *opts);
void    add_entry(t_entry **head, t_entry *new);
void sort_entries(t_entry **head);
void sort_entries_by_time(t_entry **head);
void print_entries(t_entry *head);
void free_entries(t_entry *head);
void reverse_entries(t_entry **head);


#endif
