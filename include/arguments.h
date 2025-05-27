/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:13:25 by dacortes          #+#    #+#             */
/*   Updated: 2025/05/27 10:02:16 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "libft.h"
#include "global.h"
#include "ft_printf.h"

#include <pwd.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

/******************************************************************************/
/*                            STRUCTURES                                      */
/******************************************************************************/

typedef struct s_flags			t_flags;

struct s_flags
{
	short	long_format;
	short	recursive;
	short	all;
	short	reverse;
	short	time;
	int		status;
	char	*cur_dir;
};

/*	flag.c	*/
short			is_flag(char *arg);
short			has_flags(t_flags *flags, int num_args, char **args);

/*	file.c	*/
int				get_size_files(char **args);
struct dirent	**is_file(t_flags flags, char **args, int sizes);
char			*create_full_path(const char *curr_root_dir, \
	const char *curr_dir);

/*	entries.c	*/
DIR				*init_dir(char *file);
short			is_readdir(struct dirent **entry, DIR *dir);
int				read_dir_entries(DIR *dir, struct  dirent ***entries);