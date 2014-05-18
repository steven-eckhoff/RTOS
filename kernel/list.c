/** \file list.c
*   \brief The file contains the kernel api for the list data structure
*   \author Steven W. Eckhoff
*   \bug No known bugs
*/

#include "include/list.h"
#include "include/lock.h"

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
	s32_t ret = -1;	

	if (true == list->use_lock)
		spin_lock(&list->lock);

	if (NULL == list->head) { // Empty list
		list->head = head_new;
		list->tail = head_new; 

		if (true == list->circular) {
			list->head->next = list->head;
			list->tail->next = list->head;
						
			if (true == list->double_link) {
				list->head->prev = list->tail;
				list->tail->prev = list->head;
			}
		} else {
			list->head->next = NULL;
			list->tail->next = NULL;
			
			list->head->prev = NULL;
			list->tail->prev = NULL;
		}
		
		ret = 0;
	}

	if (true == list->use_lock)
		spin_unlock(&list->lock);
	
	return ret;
}

/*! \brief
 */
link_t *list_get_head(list_t *list);
	
/*! \brief
 */
link_t *list_get_tail(list_t *list);

/*! \brief
 */
link_t *list_remove_head(list_t *list);
	
/*! \brief
 */
link_t *list_remove_tail(list_t *list);

/*! \brief
 */
void list_add_head(list_t *list, link_t *link_new);

/*! \brief
 */
void list_add_tail(list_t *list, link_t *link_new);
	
/*! \brief
 */
void list_insert_link(list_t *list, link_t *link_prev, link_t *link_new);
	
/*! \brief
 */
link_t list_remove_link(list_t *list, link_t *link_old);
