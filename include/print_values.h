/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_values.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:13:48 by dacortes          #+#    #+#             */
/*   Updated: 2025/08/04 12:15:21 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "arguments.h"
#include "libft.h"
#include "global.h"
#include "ft_printf.h"

#include <grp.h>
#include <pwd.h>
#include <time.h>
#include <dirent.h>

typedef struct s_size			t_size;
typedef struct s_line			t_line;
typedef struct s_flags			t_flags;

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
	char	*link_target;
	char	*line;
};

/*	append_line.c	*/
void	add_permissions(char **cursor, char *permissions);
void	add_links(char **cursor, char *num_links, size_t offset);
void	add_owner(char **cursor, char *owner, size_t offset);
void	add_group(char **cursor, char *group, size_t offset);
void	add_bytes(char **cursor, char *bytes, size_t offset);

/*	create_line.c	*/
void	create_line(t_line *line, t_size size);

/*	get_bytes.c		*/
char	*get_bytes(long long st_size);
/*	get_date.c		*/
char	*get_date(time_t *mtime);
/*	get_group.c		*/
char	*get_group(unsigned int gid);
/*	get_link		*/
char	*get_link(unsigned int mode, char *full_path);
/*	get_name.c		*/
char	*get_name(char	*name);
/*	get_num_link.c	*/
char	*get_num_link(unsigned long num_link);
/*	get_owner.c		*/
char	*get_owner(unsigned int uid);
/*	get_perms.c		*/
char	*get_format_perms(unsigned int mode);

/*	print_files.c	*/
char	*get_long_format(t_flags flags, char *path_file, char *name, \
	t_line *line);
char	*get_basic_format(t_flags flags, char *path_f, char *name, t_line *add);
void	get_format(t_flags flags, char *path_f, char *name, t_line *add);
int		print_line(char *line, char *add, size_t size);
void	print_regular_files(t_flags flags, struct dirent **files, int sizes);

/*	print_flags.c	*/
char	*bool_to_text(unsigned int bool);
void	printf_value_flag(t_flags *flag);
short	print_array_files(char **files);
char	*get_type_dir(int type);

/*	handle_line.c	*/
short	handle_line_basic(t_flags flags, t_line **line, int limit);
short	handle_line_long_format(t_flags flags, t_line **line, int limit);
short	handle_line(t_flags flags, t_line **line, int limit);

/*	utils.c	*/
short	check_struct_line(t_line *line);
void	update_max_lengths(t_line *line, t_size *size);
void	fill_spaces_right(char *dest, char *str, size_t width);
void	fill_spaces_left(char *dest, char *str, size_t width);
