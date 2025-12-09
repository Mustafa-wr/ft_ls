/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_format.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 17:00:58 by mradwan           #+#    #+#             */
/*   Updated: 2025/12/09 17:04:18 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	get_month(int mon, char *dest)
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

void	format_day(char *buffer, int *pos, int day)
{
	if (day < 10)
		buffer[(*pos)++] = ' ';
	else
		buffer[(*pos)++] = '0' + (day / 10);
	buffer[(*pos)++] = '0' + (day % 10);
}

void	format_hour_min(char *buffer, int *pos, int hour, int min)
{
	buffer[(*pos)++] = ' ';
	buffer[(*pos)++] = '0' + (hour / 10);
	buffer[(*pos)++] = '0' + (hour % 10);
	buffer[(*pos)++] = ':';
	buffer[(*pos)++] = '0' + (min / 10);
	buffer[(*pos)++] = '0' + (min % 10);
}

void	format_time_string(char *buffer, struct tm *tm_info)
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
