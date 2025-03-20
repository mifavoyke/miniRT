/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mergesort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:35:51 by zpiarova          #+#    #+#             */
/*   Updated: 2025/03/20 19:29:27 by zpiarova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"


t_inter *find_middle(t_inter *head)
{
    t_inter *slow;
    t_inter *fast;
    
    if (!head)
        return (NULL);
    slow = head;
    fast = head;
    while (fast && fast->next)
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    return(fast);
}

t_inter *merge_sort(t_inter **head)
{
    return (*head);
}

