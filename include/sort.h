/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:56:30 by dacortes          #+#    #+#             */
/*   Updated: 2025/05/23 16:17:23 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "node.h"
#include "libft.h"
#include "arguments.h"
#include "ft_printf.h"

#include <dirent.h>
#include <sys/stat.h>

/*	quicksort	*/
void	swap_ptr(void **a, void **b);
void	quicksort(char **arr, int low, int high);
/*	sort_files	*/
void	sort_files(char **files, int size);
void	sort_entries(struct dirent **entries, int count, t_flags flags);