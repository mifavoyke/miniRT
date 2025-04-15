/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:10:05 by zpiarova          #+#    #+#             */
/*   Updated: 2025/04/15 12:03:31 by zpiarova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// appends new_node to the end of the list
// new_node MUST have a next - either it has NULL or another t_inter node appended
void append_node(t_inter *new_node, t_inter **head)
{
	t_inter *temp;

	if (!new_node)
		return;
	if (!head || !*head)
	{
		*head = new_node;
		return;
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = new_node;
}

// ---------------------------------------------- MERGE SORT ------------------------------------------------------------------

// recursively merges the separated parts of the list into a single sorted list 
t_inter *merge(t_inter *a, t_inter *b)
{
	t_inter* result;
	
	result = NULL;
	if (!a)
		return b;
	if (!b)
		return a;
	if (a->distance <= b->distance)
	{
		result = a;
		result->next = merge(a->next, b);
	}
	else
	{
		result = b;
		result->next = merge(a, b->next);
	}
	return (result);
}

// splits the linked list into two halves using the fast and slow pointer approach
// when found half, set the next as head of a new list so we have a strat of the new list
// in the first list, set last element->next as NULL so the first list has an end 
void split_list(t_inter* list, t_inter** front, t_inter** back)
{
	t_inter* slow = list;
	t_inter* fast = list->next;

	while (fast)
	{
		fast = fast->next;
		if (fast)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}
	*front = list;
	*back = slow->next;
	slow->next = NULL;
}

// recursive merge sort
// accepts a head pointer (pointer to the first element which is also a pointer)
void merge_sort(t_inter** list_head)
{
	t_inter*	head;
	t_inter* a;
	t_inter* b;
	
	head = *list_head;
	if (!head || !head->next)
		return;


	splitList(head, &a, &b);
	merge_sort(&a);
	merge_sort(&b);

	*list_head = merge(a, b);
}

// ----------------------------------------------------------------------------------------------------------------------------