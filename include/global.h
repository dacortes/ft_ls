/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:10:50 by dacortes          #+#    #+#             */
/*   Updated: 2025/04/28 12:28:09 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

enum e_boolean
{
	false,
	true,
};

enum e_flags
{
	long_format = 'l',
	recursive = 'R',
	all = 'a',
	reverse = 'r',
	time = 't',
};

typedef struct s_flags
{
	short	long_format;
	short	recursive;
	short	all;
	short	reverse;
	short	time;
}	t_flags;