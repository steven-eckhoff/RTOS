/*! \file list.h
 *  \brief The file contains the kernel api for the list data structure
 *  \author Steven W. Eckhoff
 *  \bug No known bugs
 */

#ifndef KERNEL_LIST_H
#define KERNEL_LIST_H

#include "include/types.h"
#include "include/lock.h"

/*! \typedef link_t
 *  \brief Provides link member for the linked list structure
 *  \details All links will have space for two pointers. This type will be used
 *   for double and single link structures.
 */
typedef struct link_t_ {
	struct link_t_ *next;
	struct link_t_ *prev;
} link_t;

/*!
 * \typedef list
 * \brief linked list data structure
 * \details Currently all list and derived data structures will have a lock
 */
typedef struct {
	link_t *head;
	link_t *tail;
	lock_t lock;
	const bool double_link;
	const bool circular;
	const bool use_lock;
	u32_t member_count;
} list_t;

/*! \def link_init
 */
#define link_init(x) 				\
		do {				\
			(x)->next = NULL;	\
			(x)->prev = NULL;	\
		} while(0)	

/*! \brief
 */
void list_destroy(list_t *list);

/*! \brief
 */
link_t *list_get_head(list_t *list);
	
/*! \brief
 */
link_t *list_get_tail(list_t *list);

link_t *list_remove(list_t *list, link_t *member);

s32_t list_add(list_t *list, link_t *member_next, link_t *member_new);

void static inline if_list_lock_spin_lock(list_t *list)
{
	if (true == list->use_lock)
		spin_lock(&list->lock);
}

void static inline if_list_lock_spin_unlock(list_t *list)
{
	if (true == list->use_lock)
		spin_unlock(&list->lock);
}

#define DOUBLE_LINK true
#define SINGLE_LINK false
#define CIRCULAR true
#define LINEAR true
#define LOCKED true
#define UNLOCKED false
#define HEAD_EMPTY NULL
#define TAIL_EMPTY NULL

/*! \def list_new
 *  \brief Creates a new list.
 *  \note Accessing a locked list and then trying to acquire a semaphore is not allowed.
 *        If access to the list is long in duration protecting it with a semaphore is
 *        more appropriate. To protect the list with a semaphore use an unlocked list.
 */
#define list_new(name, head, tail, double_link, circular, locked)		\
			 list_t name = {head, tail, lock_init(), 		\
						double_link, circular, locked, 0}

/*! \def list_init
 *  \brief initializes members of an embedded list
 */
#define list_init(head, tail, double_link, circular, locked)			\
			 {head, tail, lock_init(), 				\
				double_link, circular, locked, 0}

/*! \def offset_of
 *  \brief calculates the offset of a given member in a given object
 */
#define offset_of(type, member) ((unsigned int) &(((type*)0)->member))

/*! \def member_of
 *  \brief returns the address of the object containing the specified member
 */
/*#define member_of(ptr, type, member)    					\
		do {								\
            		const typeof((((type*)0)->member)) *__mptr = (ptr);    	\
            		(type *)((char *)(__mptr) - offset_of(type, member));	\
		} while(0)
*/
#define member_of(ptr, type, member) ((type *)((char *)ptr - offset_of(type, member)))


#endif // KERNEL_LIST_H
