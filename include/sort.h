/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:56:30 by dacortes          #+#    #+#             */
/*   Updated: 2025/05/27 10:29:43 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "node.h"
#include "libft.h"
#include "arguments.h"
#include "ft_printf.h"

#include <dirent.h>
#include <sys/stat.h>

/*	directory.c	*/
time_t	get_latest_mtime(const char *dir_name);
int		dirs_same_time(struct stat stat1, struct stat stat2, \
		char *dir1, char *dir2);
/*	quicksort	*/
void	swap_ptr(void **a, void **b);
void	quicksort_entries(struct dirent **src, int low, int high, t_flags flag);
/*	sort_files	*/
void	sort_entries(struct dirent **entries, int count, t_flags flags);