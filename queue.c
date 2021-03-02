#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
 * Create empty queue.
 * Return NULL if could not allocate space.
 */
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    if (!q) {
        return NULL;
    }

    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* TODO: How about freeing the list elements and the strings? */
    /* Free queue structure */
    free(q);
}

/*
 * Attempt to insert element at head of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    list_ele_t *newh;
    char *new_s;
    size_t len;

    if (!q) {
        return false;
    }

    newh = malloc(sizeof(list_ele_t));
    if (!newh) {
        return false;
    }

    /* Allocate space for the string and copy it */
    len = strlen(s);
    new_s = malloc(len + 1);
    if (!new_s) {
        free(newh);
        return false;
    }

    strncpy(new_s, s, len);
    new_s[len] = '\0';

    newh->next = q->head;
    newh->value = new_s;
    q->head = newh;

    if (!q->tail) {
        q->tail = newh;
    }

    q->size++;
    return true;
}

/*
 * Attempt to insert element at tail of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* TODO: You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    /* TODO: Remove the above comment when you are about to implement. */
    list_ele_t *newt;
    char *new_s;
    size_t len;

    if (!q) {
        return false;
    }

    newt = malloc(sizeof(list_ele_t));
    if (!newt) {
        return false;
    }

    len = strlen(s);
    new_s = malloc(len + 1);
    if (!new_s) {
        free(newt);
        return false;
    }

    strncpy(new_s, s, len);
    new_s[len] = '\0';

    newt->next = NULL;
    newt->value = new_s;

    if (q->tail) {
        /* When queue is not empty */
        q->tail->next = newt;
    } else {
        /* When queue is empty */
        q->head = newt;
    }

    q->tail = newt;
    q->size++;
    return true;
}

/*
 * Attempt to remove element from head of queue.
 * Return true if successful.
 * Return false if queue is NULL or empty.
 * If sp is non-NULL and an element is removed, copy the removed string to *sp
 * (up to a maximum of bufsize-1 characters, plus a null terminator.)
 * The space used by the list element and the string should be freed.
 */
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    if (!q || !q->head) {
        return false;
    }

    if (sp) {
        strncpy(sp, q->head->value, bufsize);
        sp[bufsize - 1] = '\0';
    }

    list_ele_t *orig_head = q->head;
    q->head = q->head->next;

    free(orig_head->value);
    free(orig_head);

    return true;
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    return q ? q->size : 0;
}

/*
 * Reverse elements in queue
 * No effect if q is NULL or empty
 * This function should not allocate or free any list elements
 * (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
 * It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    list_ele_t *cur, *prev, *next;

    if (!q) {
        return;
    }

    q->tail = q->head;

    prev = NULL;
    cur = q->head;
    while (cur) {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }

    q->head = prev;
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
void q_sort(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
}
