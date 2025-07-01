/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_num_link.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 11:48:25 by dacortes          #+#    #+#             */
/*   Updated: 2025/07/01 12:17:37 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_values.h"
#include "errors.h"

/**
 * get_num_link - Converts the given number of links to a string representation.
 * @num_link: The number of links (as an unsigned long) to be converted.
 *
 * This function converts the provided number of links to a string using
 * ft_ltoa, and then ensures the memory is protected using protected_memory.
 * The returned string must be freed by the caller if necessary.
 *
 * Return: A pointer to the string representation of num_link.
 */
char	*get_num_link(unsigned long num_link)
{
	return (protected_memory(ft_ltoa(num_link), "get_num_link"));
}
