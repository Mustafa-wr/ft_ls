/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 12:00:00 by mradwan           #+#    #+#             */
/*   Updated: 2025/12/09 15:29:05 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	set_file_type(char *perms, mode_t mode)
{
	if (S_ISDIR(mode))
		perms[0] = 'd';
	else
		perms[0] = '-';
}

static void	set_owner_perms(char *perms, mode_t mode)
{
	if (mode & S_IRUSR)
		perms[1] = 'r';
	else
		perms[1] = '-';
	if (mode & S_IWUSR)
		perms[2] = 'w';
	else
		perms[2] = '-';
	if (mode & S_IXUSR)
		perms[3] = 'x';
	else
		perms[3] = '-';
}

static void	set_group_perms(char *perms, mode_t mode)
{
	if (mode & S_IRGRP)
		perms[4] = 'r';
	else
		perms[4] = '-';
	if (mode & S_IWGRP)
		perms[5] = 'w';
	else
		perms[5] = '-';
	if (mode & S_IXGRP)
		perms[6] = 'x';
	else
		perms[6] = '-';
}

static void	set_other_perms(char *perms, mode_t mode)
{
	if (mode & S_IROTH)
		perms[7] = 'r';
	else
		perms[7] = '-';
	if (mode & S_IWOTH)
		perms[8] = 'w';
	else
		perms[8] = '-';
	if (mode & S_IXOTH)
		perms[9] = 'x';
	else
		perms[9] = '-';
}

char	*format_permissions(mode_t mode)
{
	char	*perms;

	perms = malloc(11);
	if (!perms)
		return (NULL);
	set_file_type(perms, mode);
	set_owner_perms(perms, mode);
	set_group_perms(perms, mode);
	set_other_perms(perms, mode);
	perms[10] = '\0';
	return (perms);
}

static void	get_month(int mon, char *dest)
{
	if (mon == 0)
		ft_strlcpy(dest, "Jan", 4);
	else if (mon == 1)
		ft_strlcpy(dest, "Feb", 4);
	else if (mon == 2)
		ft_strlcpy(dest, "Mar", 4);
	else if (mon == 3)
		ft_strlcpy(dest, "Apr", 4);
	else if (mon == 4)
		ft_strlcpy(dest, "May", 4);
	else if (mon == 5)
		ft_strlcpy(dest, "Jun", 4);
	else if (mon == 6)
		ft_strlcpy(dest, "Jul", 4);
	else if (mon == 7)
		ft_strlcpy(dest, "Aug", 4);
	else if (mon == 8)
		ft_strlcpy(dest, "Sep", 4);
	else if (mon == 9)
		ft_strlcpy(dest, "Oct", 4);
	else if (mon == 10)
		ft_strlcpy(dest, "Nov", 4);
	else
		ft_strlcpy(dest, "Dec", 4);
}

static void	format_day(char *buffer, int *pos, int day)
{
	if (day < 10)
		buffer[(*pos)++] = ' ';
	else
		buffer[(*pos)++] = '0' + (day / 10);
	buffer[(*pos)++] = '0' + (day % 10);
}

static void	format_hour_min(char *buffer, int *pos, int hour, int min)
{
	buffer[(*pos)++] = ' ';
	buffer[(*pos)++] = '0' + (hour / 10);
	buffer[(*pos)++] = '0' + (hour % 10);
	buffer[(*pos)++] = ':';
	buffer[(*pos)++] = '0' + (min / 10);
	buffer[(*pos)++] = '0' + (min % 10);
}

static void	format_time_string(char *buffer, struct tm *tm_info)
{
	char	month[4];
	int		day;
	int		hour;
	int		min;
	int		pos;

	get_month(tm_info->tm_mon, month);
	day = tm_info->tm_mday;
	hour = tm_info->tm_hour;
	min = tm_info->tm_min;
	pos = 0;
	buffer[pos++] = month[0];
	buffer[pos++] = month[1];
	buffer[pos++] = month[2];
	buffer[pos++] = ' ';
	format_day(buffer, &pos, day);
	format_hour_min(buffer, &pos, hour, min);
	buffer[pos] = '\0';
}

char	*format_time(time_t mtime)
{
	char		*time_str;
	struct tm	*tm_info;

	time_str = malloc(13);
	if (!time_str)
		return (NULL);
	tm_info = localtime(&mtime);
	format_time_string(time_str, tm_info);
	return (time_str);
}

static void	print_entry_info(t_entry *entry, char *perms, char *time_str,
		struct passwd *pwd, struct group *grp)
{
	ft_printf("%s %2lu %-8s %-8s %5lld %s %s\n", perms,
		(unsigned long)entry->nlink, pwd->pw_name, grp->gr_name,
		(long long)entry->size, time_str, entry->name);
}

void	print_entries_long(t_entry *head)
{
	t_entry *current;
	char *perms;
	char *time_str;
	struct passwd *pwd;
	struct group *grp;

	current = head;
	while (current)
	{
		perms = format_permissions(current->mode);
		time_str = format_time(current->mtime);
		pwd = getpwuid(current->uid);
		grp = getgrgid(current->gid);
		if (perms && time_str && pwd && grp)
			print_entry_info(current, perms, time_str, pwd, grp);
		free(perms);
		free(time_str);
		current = current->next;
	}
}