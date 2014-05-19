/** \file list.c
*   \brief The file contains the kernel api for the list data structure
*   \author Steven W. Eckhoff
*   \bug No known bugs
*/

#include "include/list.h"
#include "include/lock.h"

link_t* static inline list_remove_circular_double(list_t *list, link_t *member)
{	
	if (0 == list->member_count)
		return NULL;

	--list->member_count;

	if (list->member_count > 0) {
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

	return member;
}

link_t* static inline list_remove_linear_double(list_t *list, link_t *member)
{	
	if (0 == list->member_count)
		return NULL;

	--list->member_count;

	if (list->member_count > 0) {

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

	return member;
}

/*! \brief
 */
void list_destroy(list_t *list)
{
	return;
}

/*! \brief
 */
s32_t list_head_set(list_t *list, link_t *head_new)
{
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
link_t *list_remove_head(list_t *list)
{
}
	
/*! \brief
 */
link_t *list_remove_tail(list_t *list)
{
}

/*! \brief
 */
void list_add_head(list_t *list, link_t *link_new)
{
}

/*! \brief
 */
void list_add_tail(list_t *list, link_t *link_new)
{
}
	
/*! \brief
 */
void list_insert_link(list_t *list, link_t *link_prev, link_t *link_new)
{
}
	
/*! \brief
 */
link_t list_remove_link(list_t *list, link_t *link_old)
{
}
