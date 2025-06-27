/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 10:56:35 by dacortes          #+#    #+#             */
/*   Updated: 2025/06/27 11:49:08 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_values.h"
#include "errors.h"

char	*get_owner(unsigned int uid)
{
	struct passwd *pw;
	
	pw = getpwuid(uid);
	return (protected_memory(ft_strdup(pw->pw_name), "get_user"));
}

char	*get_group(unsigned int gid)
{
	struct group *gr;
	
	gr = getgrgid(gid);
	return (protected_memory(ft_strdup(gr->gr_name), "get_group"));
}

char	*get_num_link(unsigned long num_link, size_t *size_num_link)
{
	return (protected_memory(ft_ltoa(num_link, size_num_link), "get_num_link"));
}

char	*get_bytes(long long st_size, size_t *size_bytes)
{
	return (protected_memory(ft_ltoa(st_size, size_bytes), \
	"get_bytes"));
}

char	*get_date(time_t *mtime, size_t *size_date)
{
	char	*date;

	date = protected_memory(ft_strdup(ctime(mtime)), "get_date");
	(*size_date) = ft_strlen(date);
	return (date);
}

char	*get_name(char	*name, size_t *size_name)
{
	char	*cpy_name;

	cpy_name = protected_memory(ft_strdup(name), "get_name");
	(*size_name) = ft_strlen(cpy_name);
	return (cpy_name);
}

char	*get_long_format(t_flags flags, char *path_file, char *name)
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

	t_line	line;
	t_size	size_line;

	line.permissions = get_format(st.st_mode);
	line.num_links = get_num_link(st.st_nlink, &size_line.max_links);
	line.owner = get_owner(st.st_uid);
	line.group = get_group(st.st_gid);
	line.bytes = get_bytes(st.st_size, &size_line.max_bytes);
	line.date = get_date(&st.st_mtime, &size_line.max_date);
	line.name = get_name(name, &size_line.max_name);
	ft_printf("%s %s %s %s %s %s %s\n", \
	line.permissions, \
	line.num_links, \
	line.owner, \
	line.group, \
	line.bytes, \
	line.date, \
	line.name);
	free(line.permissions);
	free(line.num_links);
	free(line.owner);
	free(line.group);
	free(line.bytes);
	free(line.date);
	free(line.name);
	return(NULL);
}

/* pasarle ya el len total para ahorrarse un bucle */
int	print_line(t_flags flags, char *line)
{
	size_t	len;

	(void)flags;
	if (!line)
		return (fd_printf(2, WARNING_POINTER, YELLOW, END, \
			"printf_flags", "stack"), EXIT_FAILURE);
	len = ft_strlen(line);
	write(1, line, len);
	return (EXIT_SUCCESS);
}