/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:56:30 by dacortes          #+#    #+#             */
/*   Updated: 2025/08/04 13:36:44 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "node.h"
#include "libft.h"
#include "arguments.h"
#include "ft_printf.h"

#include <time.h>
#include <dirent.h>
#include <sys/stat.h>

/*		directory.c		*/
time_t	get_latest_mtime(const char *dir_name);
int		dirs_same_time(struct stat stat1, struct stat stat2, \
		char *dir1, char *dir2);
/*		quicksort.c		*/
void	swap_ptr(void **a, void **b);
void	quicksort_entries(struct dirent **src, int low, int high, t_flags flag);
/*		recursive.c		*/
short	loop_recursive(t_flags flags, t_stack *stack);
short	exec_recursive_flag(t_flags flags, char *start_dir);
/*		sort_files.c	*/
void	sort_entries(struct dirent **entries, int count, t_flags flags);
/*		utils.c			*/
void	has_flag_all(t_flags flags, char *curr_root_dir, char *curr_dir, \
	t_line *add);
int		ignore_current_dir(t_flags flags, struct dirent **files, int *i);
int		select_state(t_flags flags, t_node **curr, struct stat *st, DIR **dir);