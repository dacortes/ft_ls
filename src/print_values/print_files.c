/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 10:56:35 by dacortes          #+#    #+#             */
/*   Updated: 2025/06/30 17:03:06 by dacortes         ###   ########.fr       */
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

char	*get_num_link(unsigned long num_link)
{
	return (protected_memory(ft_ltoa(num_link), "get_num_link"));
}

char	*get_bytes(long long st_size)
{
	return (protected_memory(ft_ltoa(st_size), "get_bytes"));
}

char	*get_date(time_t *mtime)
{
	size_t	len;
	char	*str;

	str = protected_memory(ft_strdup(ctime(mtime)), "get_date");
	len = ft_strlen(str);
	if (len > 0)
		str[len - 1] = '\0';
	return (str);
}

char	*get_name(char	*name)
{
	return (protected_memory(ft_strdup(name), "get_name"));
}

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

/* pasarle ya el len total para ahorrarse un bucle */
int	print_line(char *line, size_t size)
{
	if (!line)
		return (fd_printf(2, WARNING_POINTER, YELLOW, END, \
			"printf_flags", "stack"), EXIT_FAILURE);
	write(1, line, size);
	write(1, "\n", 1);
	return (EXIT_SUCCESS);
}