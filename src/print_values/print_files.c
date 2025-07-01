/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 10:56:35 by dacortes          #+#    #+#             */
/*   Updated: 2025/07/01 12:07:34 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_values.h"
#include "errors.h"

char	*get_long_format(t_flags flags, char *path_file, char *name, t_line *add)
{
	struct	stat	st;

	if (!file)
	{
		fd_printf(2, WARNING_POINTER, YELLOW, END, \
			"printf_flags", "stack");
		return (NULL);
	}
	if (flags.long_format == false)
		return (NULL);
	lstat(path_file, &st);

	add->permissions = get_format_perms(st.st_mode);
	add->num_links = get_num_link(st.st_nlink);
	add->owner = get_owner(st.st_uid);
	add->group = get_group(st.st_gid);
	add->bytes = get_bytes(st.st_size);
	add->date = get_date(&st.st_mtime);
	add->name = get_name(name);
	return(NULL);
}

int	print_line(char *line, size_t size)
{
	if (!line)
		return (fd_printf(2, WARNING_POINTER, YELLOW, END, \
			"printf_flags", "stack"), EXIT_FAILURE);
	write(1, line, size);
	write(1, "\n", 1);
	return (EXIT_SUCCESS);
}