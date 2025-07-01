/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_values.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:13:48 by dacortes          #+#    #+#             */
/*   Updated: 2025/07/01 12:09:25 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "arguments.h"
# include "libft.h"
# include "global.h"
# include "ft_printf.h"

# include <grp.h>
# include <pwd.h>
# include <time.h>
# include <dirent.h>

typedef struct s_size			t_size;
typedef struct s_line			t_line;

struct s_size
{
	size_t	max_links;
	size_t	max_owner;
	size_t	max_group;
	size_t	max_bytes;
	size_t	max_date;
	size_t	max_name;
	size_t	max_line;
};

struct s_line
{
	char	*permissions;
	char	*num_links;
	char	*owner;
	char	*group;
	char	*bytes;
	char	*date;
	char	*name;
	char	*line;
};

/*	print_values.c	*/
char	*bool_to_text(unsigned int bool);
void	printf_value_flag(t_flags *flag);
short	print_array_files(char **files);
char	*get_type_dir(int type);

/*	print_files.c	*/
char	*get_long_format(t_flags flags, char *path_file, char *name, t_line *line);
int		print_line(char *line, size_t size);
/*	get_bytes.c		*/
char	*get_bytes(long long st_size);
/*	get_date.c		*/
char	*get_date(time_t *mtime);
/*	get_group.c		*/
char	*get_group(unsigned int gid);
/*	get_name.c		*/
char	*get_name(char	*name);
/*	get_num_link.c	*/
char	*get_num_link(unsigned long num_link);
/*	get_owner.c		*/
char	*get_owner(unsigned int uid);
/*	get_perms.c		*/
char	*get_format_perms(unsigned int mode);