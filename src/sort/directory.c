/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 09:06:25 by dacortes          #+#    #+#             */
/*   Updated: 2025/05/28 17:56:21 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort.h"

// void	recursive_latest_mtime(char *path, struct stat d_time, time_t *mtime)
// {
// 	time_t	subdir_mtime;

// 	if (S_ISDIR(d_time.st_mode))
// 	{
// 		subdir_mtime = get_latest_mtime(path);
// 		if (subdir_mtime > (*mtime))
// 			*mtime = subdir_mtime;
// 	}
// }

time_t	get_latest_mtime(const char *dir_name)
{
	time_t			latest_mtime;
	char			*full_path;
	struct stat		file_stat;
	struct dirent	*entry;
	DIR				*dir;

	dir = opendir(dir_name);
	if (!dir)
		return (0);
	latest_mtime = 0;
	while (is_readdir(&entry, dir))
	{
		if (default_directories(entry->d_name, entry->d_type))
			continue ;
		full_path = create_full_path(dir_name, entry->d_name);
		if (stat(full_path, &file_stat) == EXIT_SUCCESS)
		{
			if (file_stat.st_ctime > latest_mtime)
				latest_mtime = file_stat.st_ctime;
			if (S_ISDIR(file_stat.st_mode))
			{
				time_t subdir_mtime = get_latest_mtime(full_path);
				if (subdir_mtime > latest_mtime)
					latest_mtime = subdir_mtime;
			}
		}
		free(full_path);
	}
	return (closedir(dir), latest_mtime);
}

#include <time.h>

int	dirs_same_time(struct stat stat1, struct stat stat2, char *dir1, char *dir2)
{
	time_t latest1;
	time_t latest2;

	// printf("Modification time (mtime): %s", ctime(&stat1.st_mtime));
    // printf("Change time (ctime): %s", ctime(&stat1.st_ctime));
	if (S_ISDIR(stat1.st_mode) && S_ISDIR(stat2.st_mode))
	{
		latest1 = get_latest_mtime(dir1);
		latest2 = get_latest_mtime(dir2);
		if (latest1 > latest2)
			return (-1);
		else if (latest1 < latest2)
			return (1);
	}
	return (ft_strncmp(dir1, dir2, -1));
}
