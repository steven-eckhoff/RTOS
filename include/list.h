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

/*! \enum list_link_type_
 *  \brief Specifies the link type of the list
 */
typedef enum {SINGLE, DOUBLE} link_num_t;

/*!
 * \typedef list
 * \brief linked list data structure
 * \details Currently all list and derived data structures will have a lock
 */
typedef struct {
	link_num_t type;
	link_t *head;
	link_t *tail;
	lock_t lock;
} list_t;

/*! \brief
 */
void list_destroy(list_t *list);

/*! \brief
 */
void list_head_set(list_t *list, link_t *head_new);

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

/*! \def list_new
 *  \brief Creates a new list.
 */
#define list_new(name,type,head,tail) list_t name = {type, head, tail, lock_init()}

/*! \def list_new_nopreempt
 *  \brief Creates a new list.
 */
#define list_new_nopreempt(name,type,head,tail) list_t name = {type, head, tail, 
								lock_init_nopreempt()}

/*! \def list_init
 *  \brief initializes members of an embedded list
 */
#define list_init(type, head, tail) {type, head, tail, lock_init()}

/*! \def list_init_nopreempt
 *  \brief initializes members of an embedded list
 */
#define list_init_nopreempt(type, head, tail) {type, head, tail, lock_init_nopreempt()}

#endif // KERNEL_LIST_H
