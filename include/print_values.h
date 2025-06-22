/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_values.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:13:48 by dacortes          #+#    #+#             */
/*   Updated: 2025/06/22 13:12:34 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "arguments.h"
# include "libft.h"
# include "global.h"
# include "ft_printf.h"

# include <dirent.h>

typedef struct s_size			t_size;
typedef struct s_line			t_line;

struct s_size
{
	size_t	max_links;
	size_t	max_owner;
	size_t	max_group;
};

struct s_line
{
	char	*permissions;
	char	*num_links;
	char	*owner;
	char	*group;
	char	*line;
};

/*	print_values.c	*/
char	*bool_to_text(unsigned int bool);
void	printf_value_flag(t_flags *flag);
short	print_array_files(char **files);
char	*get_type_dir(int type);

/*	print_files.c	*/
char	*get_long_format(t_flags flags, char *path_file);
/*	format.c	*/
char	*get_format(unsigned int type);