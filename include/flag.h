/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:13:25 by dacortes          #+#    #+#             */
/*   Updated: 2025/05/15 12:44:24 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "libft.h"
#include "global.h"
#include "ft_printf.h"

#include <errno.h>
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
};

/*	flag.c	*/
short	is_flag(char *arg);
short	has_flags(t_flags *flags, int num_args, char **args);