/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:10:50 by dacortes          #+#    #+#             */
/*   Updated: 2025/05/21 16:01:22 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

/******************************************************************************/
/*                            COLORS                                          */
/******************************************************************************/

# define END	"\033[m"
# define RED	"\033[1;31m"
# define GREEN	"\033[1;32m"
# define YELLOW	"\033[1;33m"
# define BLUE	"\033[1;34m"
# define TUR	"\033[1;35m"
# define CYAN	"\033[1;36m"
# define ORANGE	"\033[38;5;208m"
# define PURPLE	"\033[38;5;128m"

/* error messages */
# define FT_LS "\033[1;31mft_ls: \033[m"
# define ERR_MALLOC "%serror trying to allocate memory `%s'\n"
# define ERR_INVALID "%sinvalid option -- '%s'\n"
# define ERR_OPEN "%scannot open directory '%s':%s\n"
# define WARNING_POINTER "%sWarning%s: func: %s pointer %s are null\n"

/******************************************************************************/
/*                            STRUCTURES                                      */
/******************************************************************************/

enum e_boolean
{
	false,
	true,
};

enum e_dir
{
	dir,
	dir_link,
	file,
	end_dir,
};

enum e_errors
{
	ERROR = -1,
	MALLOC = 1,
	INVALID = 1 << 2,
	PERROR = 1 << 3,
	OPEN_DIR = 1 << 4,
};

enum e_flags
{
	long_format = 'l',
	recursive = 'R',
	all = 'a',
	reverse = 'r',
	time = 't',
};
