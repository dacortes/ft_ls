/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:13:25 by dacortes          #+#    #+#             */
/*   Updated: 2025/08/04 11:13:14 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "libft.h"
#include "global.h"
#include "ft_printf.h"
#include "print_values.h"

#include <errno.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

/******************************************************************************/
/*                            STRUCTURES                                      */
/******************************************************************************/

typedef struct s_flags			t_flags;
typedef struct s_line			t_line;

struct s_flags
{
	short	long_format;
	short	recursive;
	short	all;
	short	reverse;
	short	time;
	short	args;
	int		status;
	char	*cur_dir;
};

/*	flag.c	*/
short			is_flag(char *arg);
short			has_flags(t_flags *flags, int num_args, char **args);

/*	file.c	*/
int				get_size_files(char **args);
void			loop_recursive_flag(t_flags flags, struct dirent **files, \
	int sizes);
struct dirent	**is_file(t_flags flags, char **args, int sizes);
char			*create_full_path(const char *curr_root_dir, \
	const char *curr_dir);

/*	entries.c	*/
DIR				*init_dir(char *file);
short			is_readdir(struct dirent **entry, DIR *dir);
int				read_dir_entries(DIR *dir, struct dirent ***entries);

/*	utils.c		*/
int				get_regular_files_number(struct dirent **files, int sizes);
void			get_regular(t_flags flags, struct dirent **fls, int sizes, \
	t_line **ln);
