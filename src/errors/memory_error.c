/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 09:46:33 by dacortes          #+#    #+#             */
/*   Updated: 2025/07/01 12:16:48 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"

/**
 * @brief Checks if a memory allocation was successful and handles errors.
 *
 * This function verifies whether the provided memory pointer is not NULL.
 * If the allocation failed (i.e., memory is NULL), it calls error_msg with
 * the MALLOC error code, an exit status of 1, the function error string,
 * and an empty string, then exits the program.
 *
 * @param memory Pointer to the allocated memory to check.
 * @param func_err String describing the function or context where the
 * 	allocation occurred.
 * @return The original memory pointer if allocation was successful.
 * @note This function will terminate the program if memory allocation fails.
 */
void	*protected_memory(void *memory, char *func_err)
{
	if (!memory)
		exit(error_msg(MALLOC, 1, func_err, ""));
	return (memory);
}
