/** \file list.c
*   \brief The file contains the kernel api for the list data structure
*   \author Steven W. Eckhoff
*   \bug No known bugs
*/

#include "include/types.h"
#include "include/list.h"

static inline __attribute__((always_inline))
link_t  *list_remove_linear_single(list_t  *list, link_t  *member)
{
	link_t *link_ptr;

	if (NULL == list || NULL == member)
		return NULL;

	if (0 == list->member_count)
		return NULL;
	
	if (list->member_count > 1) {
		if (member == list->head) {
			list->head = member->next;
		} else {
			if ((2 == list->member_count) 
					&& (list->tail == member)) {
				list->tail = list->head;
				list->head->next = NULL;
			} else { // Assumed less likely
				link_ptr = list->head;
				do {
					link_ptr = link_ptr->next;
				} while ((link_ptr != NULL) 
						&& (link_ptr->next != member));

				if (link_ptr == NULL) // Member is not in the list
					return NULL;
			
				link_ptr->next = NULL;

				if (member == list->tail)
					list->tail = link_ptr;
			}
		}
	}	
	
	member->next = NULL;
	
	--list->member_count;

	return member;
}

static inline __attribute__((always_inline))
link_t  *list_remove_linear_double(list_t  *list, link_t  *member)
{	
	if (NULL == list || NULL == member)
		return NULL;
	
	if (0 == list->member_count)
		return NULL;

	if (list->member_count > 1) {

		if (member == list->head) {
			list->head = member->next;
			list->head->prev = NULL;
		} else if (member == list->tail) {
			list->tail = member->prev;
			list->tail->next = NULL;
		} else {
			member->next->prev = member->prev;
			member->prev->next = member->next;
		}
	} else {
		list->head = NULL;
		list->tail = NULL;
	}

	member->next = NULL;
	member->prev = NULL;

	--list->member_count;

	return member;
}

static inline __attribute__((always_inline))
link_t  *list_remove_circular_single(list_t  *list, link_t  *member)
{
	link_t *link_ptr;

	if (NULL == list || NULL == member)
		return NULL;

	if (0 == list->member_count)
		return NULL;
	
	if (list->member_count > 1) {
		if (member == list->head) {
			list->tail->next = member->next;
			list->head = member->next;
		} else {
			if ((2 == list->member_count) 
					&& (list->tail == member)) {
				list->tail = list->head;
				list->head->next = list->head;
			} else { // Assumed less likely
				link_ptr = list->head;
				do {
					link_ptr = link_ptr->next;
				} while ((link_ptr->next != member) 
						&& (link_ptr != list->head));

				if (link_ptr == list->head) // Member is not in the list
					return NULL;
			
				link_ptr->next = member->next;
				
				if (member == list->tail)
					list->tail = link_ptr;
			}
		}
	}	
	
	member->next = NULL;
	
	--list->member_count;

	return member;
}

static inline __attribute__((always_inline))
link_t  *list_remove_circular_double(list_t  *list, link_t  *member)
{	
	if (NULL == list || NULL == member)
		return NULL;

	if (0 == list->member_count)
		return NULL;

	if (list->member_count > 1) {
		member->prev->next = member->next;
		member->next->prev = member->prev;

		if (member == list->head)
			list->head = member->next;
		else if (member == list->tail)
			list->tail = member->prev;
	} else {
		list->head = NULL;
		list->tail = NULL;
	}

	member->next = NULL;
	member->prev = NULL;

	--list->member_count;

	return member;
}

s32_t static inline __attribute__((always_inline))
list_add_linear_single(list_t  *list, link_t  *member_next, link_t  *member_new)
{
	link_t *link_ptr;

	if (NULL == list || NULL == member_new)
		return -1;
	
	if (0 == list->member_count) { // Empty list
		member_new->next = NULL;
		list->head = member_new;
		list->tail = member_new;
	} else if (member_next == list->head) { // Insert as head
		member_new->next = list->head;
		list->head = member_new;
	} else if (NULL == member_next) { // Insert as tail
		member_new->next = NULL;
		list->tail->next = member_new;
		list->tail = member_new;
	} else {
		link_ptr = list->head;	

		while ((NULL != link_ptr) && (link_ptr->next != member_next))
			link_ptr = link_ptr->next;

		if (NULL == link_ptr) // member_next not in list
			return -1;

		member_new->next = member_next;

		link_ptr->next = member_new;
	}
	
	++list->member_count;

	return 0;
}

s32_t static inline __attribute__((always_inline))
list_add_linear_double(list_t *list, link_t *member_next, link_t *member_new)
{
	if (NULL == list || NULL == member_new)
		return -1;
	
	if (0 == list->member_count) { // Empty list
		member_new->next = NULL;
		member_new->prev = NULL;
		list->head = member_new;
		list->tail = member_new;
	} else if (member_next == list->head) { // Insert as head
		member_new->next = list->head;
		member_new->prev = NULL;
		list->head->prev = member_new;
		list->head = member_new;
	} else if (NULL == member_next) { // Insert as tail
		member_new->next = NULL;
		member_new->prev = list->tail;
		list->tail->next = member_new;
		list->tail = member_new;
	} else {
		member_new->next = member_next;
		member_new->prev = member_next->prev;
		member_next->prev->next = member_new;
		member_next->prev = member_new;
	}
	
	++list->member_count;

	return 0;
}

s32_t static inline __attribute__((always_inline))
list_add_circular_single(list_t *list, link_t *member_next, link_t *member_new)
{
	link_t *link_ptr;

	if (NULL == list || NULL == member_new)
		return -1;
	
	if (0 == list->member_count) { // Empty list
		member_new->next = member_new;
		list->head = member_new;
		list->tail = member_new;
	} else if (member_next == list->head) { // Insert as head
		member_new->next = list->head;
		list->tail->next = member_new;
		list->head = member_new;
	} else if (NULL == member_next) { // Insert as tail
		member_new->next = list->head;
		list->tail->next = member_new;
		list->tail = member_new;
	} else {
		link_ptr = list->head;	

		while (link_ptr->next != member_next) {
			link_ptr = link_ptr->next;
			if (link_ptr == list->head)
				return -1;
		}

		member_new->next = member_next;

		link_ptr->next = member_new;
	}
	
	++list->member_count;

	return 0;
}

s32_t static inline __attribute__((always_inline))
list_add_circular_double(list_t *list, link_t *member_next, link_t *member_new)
{
	if (NULL == list || NULL == member_new)
		return -1;
	
	if (0 == list->member_count) { // Empty list
		member_new->next = member_new;
		member_new->prev = member_new;
		list->head = member_new;
		list->tail = member_new;
	} else if (member_next == list->head) { // Insert as head
		member_new->next = list->head;
		member_new->prev = list->tail;
		list->tail->next = member_new;
		list->head->prev = member_new;
		list->head = member_new;
	} else if (NULL == member_next) { // Insert as tail
		member_new->next = list->head;
		member_new->prev = list->tail;
		list->tail->next = member_new;
		list->head->prev = member_new;
		list->tail = member_new;
	} else {
		member_new->next = member_next;
		member_new->prev = member_next->prev;
		member_next->prev->next = member_new;
		member_next->prev = member_new;
	}
	
	++list->member_count;

	return 0;
}

/*! \brief
 */
void list_destroy(list_t *list)
{
	return;
}

/*! \brief
 *  \note Lock is not acquired with this call.
 */
link_t *list_get_head(list_t *list)
{
	if (NULL == list->head)
		return NULL;
	else
		return list->head;
}
	
/*! \brief
 *  \note Lock is not acqurired with this call.
 */
link_t *list_get_tail(list_t *list)
{
	if (NULL == list->tail)
		return NULL;
	else
		return list->tail;
}

/*! \brief
 */
link_t *list_remove(list_t *list, link_t *member)
{
	u32_t type = (((u32_t)list->circular) << 1) + (u32_t)(list->double_link);

	switch (type) {
	case 0:
		return list_remove_linear_single(list, member);
		break;
	case 1:
		return list_remove_linear_double(list, member);
		break;
	case 2:
		return list_remove_circular_single(list, member);
		break;
	case 3:
		return list_remove_circular_double(list, member);
		break;
	}
	// Should not reach here
	return NULL;
}

/*! \brief
 */
s32_t list_add(list_t *list, link_t *member_next, link_t *member_new)
{
	u32_t type = (((u32_t)list->circular) << 1) + (u32_t)(list->double_link);

	switch (type) {
	case 0:
		return list_add_linear_single(list, member_next, member_new);
		break;
	case 1:
		return list_add_linear_double(list, member_next, member_new);
		break;
	case 2:
		return list_add_circular_single(list, member_next, member_new);
		break;
	case 3:
		return list_add_circular_double(list, member_next, member_new);
		break;
	}
	// Should not reach here
	return -1;
}

