/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entries.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 15:07:19 by dacortes          #+#    #+#             */
/*   Updated: 2025/05/25 15:18:09 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "node.h"
#include "errors.h"
#include "arguments.h"

/**
 * init_dir - Opens a directory stream for the specified file path.
 *
 * @file: The path to the directory to be opened.
 *
 * Return: A pointer to the opened directory stream (DIR *) on success.
 *         If the directory cannot be opened, an error message is printed
 *         and NULL is returned.
 *
 * Errors:
 * - If the directory cannot be opened, the function prints an error message
 *   using the `error_msg` function, which includes the error description
 *   from `strerror(errno)`.
 */
DIR	*init_dir(char *file)
{
	DIR	*dir;

	dir = opendir(file);
	if (!dir)
		return (error_msg(OPEN_DIR, 2, file, strerror(errno)), NULL);
	return (dir);
}

/**
 * is_readdir - Reads the next directory entry from a directory stream.
 *
 * @entry: A pointer to a pointer of struct dirent where the directory entry
 *         will be stored if successfully read.
 * @dir:   A pointer to the directory stream to read from.
 *
 * This function attempts to read the next entry from the directory stream
 * specified by `dir` and stores it in the location pointed to by `entry`.
 * If the end of the directory stream is reached or an error occurs, `*entry`
 * will be set to NULL.
 *
 * Return:
 * - true (1) if a directory entry was successfully read.
 * - false (0) if the end of the directory stream is reached or an error occurs.
 */
short	is_readdir(struct dirent **entry, DIR *dir)
{
	*entry = readdir(dir);
	if (!*entry)
		return (false);
	return (true);
}

/**
 * read_dir_entries - Reads directory entries and stores them in a dynamically
 * allocated array of struct dirent pointers.
 *
 * @dir: A pointer to the directory stream (of type DIR) to read entries from.
 * @entries: A double pointer to an array of struct dirent pointers. This array
 *           will be dynamically allocated and populated with the directory
 *           entries. The caller is responsible for freeing the allocated memory.
 *
 * Return: The number of directory entries read and stored in the array.
 *
 * Description:
 * This function iterates over the entries in the directory stream `dir` using
 * the `is_readdir` function. For each entry, it dynamically reallocates memory
 * for the `entries` array to accommodate the new entry. If memory allocation
 * fails, the function exits the program with an error message.
 *
 * The `copy_struct_dirent` function is used to copy the contents of the current
 * directory entry into the newly allocated space in the `entries` array.
 *
 * Note:
 * - The caller must ensure that `dir` is a valid and open directory stream.
 * - The caller must free the memory allocated for `entries` after use.
 * - The function relies on external functions `is_readdir`, `ft_realloc`,
 *   `error_msg`, and `copy_struct_dirent`, which must be implemented elsewhere.
 */
int	read_dir_entries(DIR *dir, struct dirent ***entries)
{
	struct dirent	*entry;
	struct dirent	**tmp;
	int				i;

	i = 0;
	while (is_readdir(&entry, dir))
	{
		tmp = ft_realloc(*entries, sizeof(struct dirent *) * i, \
			sizeof(struct dirent *) * (i + 1));
		if (!tmp)
			exit(error_msg(MALLOC, 1, "read_dir_entries", ""));
		*entries = tmp;
		copy_struct_dirent(entry, &(*entries)[i]);
		i++;
	}
	return (i);
}
