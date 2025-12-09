/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:59:14 by mradwan           #+#    #+#             */
/*   Updated: 2025/12/09 17:37:47 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft/libft.h"
# include <dirent.h>
# include <stdio.h>
# include <string.h>
# include <sys/stat.h>
# include <time.h>
# include <unistd.h>
# include <pwd.h>
# include <grp.h>


typedef struct s_options
{
	int l;   // long format    (-l)
	int c_r; // recursive      (-R)
	int a;   // all/hidden     (-a)
	int r;   // reverse        (-r)
	int t;   // time sort      (-t)
}					t_options;

typedef struct s_entry
{
	char			*name;
	struct s_entry	*next;
	time_t			mtime;
	int				is_directory;
	mode_t			mode;
	nlink_t			nlink;
	uid_t			uid;
	gid_t			gid;
	off_t			size;
	int				silent;
}					t_entry;

t_entry				*new_entry(char *name, char *path, t_options *opts);
void				add_entry(t_entry **head, t_entry *new);
void				print_error(char *path);
int					read_entries(DIR *d, t_entry **head, t_options *opts, char *path);
void				sort_entries(t_entry **head);
void				sort_entries_by_time(t_entry **head);
void				print_entries(t_entry *head);
void				free_entries(t_entry *head);
void				reverse_entries(t_entry **head);
int					parse_options(int ac, char **av, t_options *opts,
						int *start_index);
void				list_recursively(char *path, t_options *opts,
						t_entry *head);
int					ft_strcmp(const char *s1, const char *s2);
int					list_directory(char *path, t_options *opts,
						int print_newline, int silent);
void				print_entries_long(t_entry *head);
char				*format_permissions(mode_t mode);
void				format_time_string(char *buffer, struct tm *tm_info);
void				get_month(int mon, char *dest);
void				format_day(char *buffer, int *pos, int day);
void				format_hour_min(char *buffer, int *pos, int hour, int min);
void				format_time_string(char *buffer, struct tm *tm_info);
char				*format_time(time_t mtime);
int					list_directory(char *path, t_options *opts, int print_newline, int silent);

#endif
