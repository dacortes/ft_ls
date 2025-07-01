/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 10:56:35 by dacortes          #+#    #+#             */
/*   Updated: 2025/07/01 13:03:22 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_values.h"
#include "errors.h"

/**
 * get_long_format - Populates a t_line structure with file metadata for long
 * format display.
 * @flags:      Structure containing display flags, including long format
 * 				option.
 * @path_file:  Path to the file whose metadata is to be retrieved.
 * @name:       Name of the file.
 * @add:        Pointer to a t_line structure to be filled with file 
 * 				information.
 *
 * This function retrieves file metadata using lstat and fills the provided
 * t_line structure with formatted information such as permissions,
 * 	number of links,
 * owner, group, file size, modification date, and file name. If the long format
 * flag is not set, or if the file pointer is NULL, the function returns NULL.
 *
 * Return: Always returns NULL.
 */
char	*get_long_format(t_flags flags, char *path_f, char *name, t_line *add)
{
	struct stat	st;

	if (!file)
	{
		fd_printf(2, WARNING_POINTER, YELLOW, END, \
			"printf_flags", "stack");
		return (NULL);
	}
	if (flags.long_format == false)
		return (NULL);
	lstat(path_f, &st);
	add->permissions = get_format_perms(st.st_mode);
	add->num_links = get_num_link(st.st_nlink);
	add->owner = get_owner(st.st_uid);
	add->group = get_group(st.st_gid);
	add->bytes = get_bytes(st.st_size);
	add->date = get_date(&st.st_mtime);
	add->name = get_name(name);
	return (NULL);
}

/**
 * @brief Prints a line of text to standard output followed by a newline.
 *
 * This function writes the given line of text to file descriptor 1 (stdout)
 * and appends a newline character. If the provided line pointer is NULL,
 * it prints a warning message to standard error and returns EXIT_FAILURE.
 *
 * @param line Pointer to the string to print.
 * @param size The number of bytes from the line to write.
 * @return EXIT_SUCCESS on success, EXIT_FAILURE if the line pointer is NULL.
 */
int	print_line(char *line, size_t size)
{
	if (!line)
		return (fd_printf(2, WARNING_POINTER, YELLOW, END, \
			"printf_flags", "stack"), EXIT_FAILURE);
	write(1, line, size);
	write(1, "\n", 1);
	return (EXIT_SUCCESS);
}
