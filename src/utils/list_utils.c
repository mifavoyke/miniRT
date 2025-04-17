/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:10:05 by zpiarova          #+#    #+#             */
/*   Updated: 2025/04/17 15:31:15 by zpiarova         ###   ########.fr       */
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

// prints linked list
void print_list(t_inter *head, int x, int y)
{
	if (!head)
	{
		//printf("List is empty.\n");
		return;
	}
	printf("[%d, %d] ------------------------------------------------------------\n", x, y);
	while (head)
	{
		printf("Intersection point: (%f, %f, %f) distance: %f, dist_to_light: %f, object: %d\n", head->point.x, head->point.y, head->point.z, head->distance, head->dist_to_light, head->type);
		head = head->next;
	}
}

// ---------------------------------------------- MERGE SORT ------------------------------------------------------------------

// splits the linked list into two halves using the fast and slow pointer approach
// when found half, set the next as head of a new list so we have a start of the new list
// in the first list, set last_element->next as NULL so the first list has an end
void split_list(t_inter *list, t_inter **first_half, t_inter **second_half)
{
	t_inter *slow = list;
	t_inter *fast = list->next;

	while (fast)
	{
		fast = fast->next;
		if (fast)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}
	*first_half = list;
	*second_half = slow->next;
	slow->next = NULL;
}

// recursively merges the separated parts of the list into a single sorted list
// if criteria is dist-to-light, use that, else use distance as the base case
// the result is accumulated 
t_inter *compare_and_merge(t_inter *first_half, t_inter *second_half, char *criteria)
{
	t_inter *result;
	float first_half_criteria;
	float second_half_criteria;
	
	result = NULL;
	if (!ft_strncmp("dist_to_light\0", criteria, ft_strlen(criteria)))
	{
		first_half_criteria = first_half->dist_to_light;
		second_half_criteria = second_half->dist_to_light;
	}
	else
	{
		first_half_criteria = first_half->distance;
		second_half_criteria = second_half->distance;
	}
	if (!first_half)
		return second_half;
	if (!second_half)
		return first_half;
	if (first_half_criteria <= second_half_criteria)
	{
		result = first_half;
		result->next = compare_and_merge(first_half->next, second_half, criteria);
	}
	else
	{
		result = second_half;
		result->next = compare_and_merge(first_half, second_half->next, criteria);
	}
	return (result);
}

// merge sort - recursively split the list and then recursively merges it from teh smallest parts
// sorts based on distance or distance to the light - can add more later
void merge_sort(t_inter **list_head, char *criteria)
{
	t_inter *head;
	t_inter *first_half;
	t_inter *second_half;

	head = *list_head;
	if (!head || !head->next)
		return;
	split_list(head, &first_half, &second_half);
	merge_sort(&first_half, criteria);
	merge_sort(&second_half, criteria);

	*list_head = compare_and_merge(first_half, second_half, criteria);
}

// ----------------------------------------------------------------------------------------------------------------------------