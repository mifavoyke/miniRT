/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuzanapiarova <zuzanapiarova@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:14:57 by zuzanapiaro       #+#    #+#             */
/*   Updated: 2025/05/13 12:47:00 by zuzanapiaro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	print_inter_list(t_inter **head)
{
	t_inter	*temp;

	if (!head || !*head)
		return ;
	temp = *head;
	while (temp)
	{
		if (temp->type == SPHERE)
			printf("sphere %d ", temp->id);
		else if (temp->type == CYLINDER)
			printf("cylinder %d ", temp->id);
		else if (temp->type == PLANE)
			printf("plane %d ", temp->id);
		printf("%f\n", temp->distance);
		temp = temp->next;
	}
	printf("-----------------\n");
}

// appends new_node to the end of the list
// new_node has a next - either another t_inter node appended or NULL
void	append_node(t_inter *new_node, t_inter **head)
{
	t_inter	*temp;

	if (!new_node)
		return ;
	if (!head || !*head)
	{
		*head = new_node;
		return ;
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = new_node;
}

// ---------------------------- MERGE SORT ------------------------------------

// splits linked list into two halves using the fast and slow pointer approach
// when found half, set the next as head of a new list so new list has a start
// in the first list, set last_element->next as NULL so first list has an end
static void	split_list(t_inter *l, t_inter **first_half, t_inter **second_half)
{
	t_inter	*slow;
	t_inter	*fast;

	if (!l)
		return ;
	slow = l;
	fast = l->next;
	while (fast)
	{
		fast = fast->next;
		if (fast)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}
	*first_half = l;
	*second_half = slow->next;
	slow->next = NULL;
}

// recursively merges the separated parts of the list into a single sorted list
// the result is accumulated 
static t_inter	*compare_and_merge(t_inter *first_half, t_inter *second_half)
{
	t_inter	*result;

	result = NULL;
	if (!first_half)
		return (second_half);
	if (!second_half)
		return (first_half);
	if (!first_half)
		return (second_half);
	if (!second_half)
		return (first_half);
	if (first_half->distance <= second_half->distance)
	{
		result = first_half;
		result->next = compare_and_merge(first_half->next, second_half);
	}
	else
	{
		result = second_half;
		result->next = compare_and_merge(first_half, second_half->next);
	}
	return (result);
}

// recursively split list and then recursively merge it from the smallest parts
// sorts based on distance or distance to the light - can add more later
void	merge_sort(t_inter **list_head)
{
	t_inter	*head;
	t_inter	*first_half;
	t_inter	*second_half;

	head = *list_head;
	if (!head || !head->next)
		return ;
	split_list(head, &first_half, &second_half);
	merge_sort(&first_half);
	merge_sort(&second_half);
	*list_head = compare_and_merge(first_half, second_half);
}
