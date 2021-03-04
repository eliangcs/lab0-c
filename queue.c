#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

#define MAXSTRING 1024

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
    list_ele_t *cur, *next;

    if (!q) {
        return;
    }

    cur = q->head;

    while (cur) {
        next = cur->next;
        free(cur->value);
        free(cur);
        cur = next;
    }

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

    q->size--;
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

static list_ele_t *merge(list_ele_t *a, list_ele_t *b)
{
    list_ele_t h;
    list_ele_t *t = &h;

    h.next = NULL;
    h.value = NULL;

    while (1) {
        if (!a) {
            t->next = b;
            break;
        }
        if (!b) {
            t->next = a;
            break;
        }

        if (strncmp(a->value, b->value, MAXSTRING) < 0) {
            t->next = a;
            t = a;
            a = a->next;
        } else {
            t->next = b;
            t = b;
            b = b->next;
        }
    }

    return h.next;
}

static list_ele_t *merge_sort(list_ele_t *head)
{
    list_ele_t *fast, *slow, *left, *right;

    if (!head || !head->next) {
        return head;
    }

    fast = head->next;
    slow = head;

    // Split list
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    fast = slow->next;
    slow->next = NULL;

    // Sort each list
    left = merge_sort(head);
    right = merge_sort(fast);

    // Merge two sorted list
    return merge(left, right);
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
void q_sort(queue_t *q)
{
    if (!q) {
        return;
    }

    q->head = merge_sort(q->head);

    q->tail = q->head;
    while (q->tail && q->tail->next) {
        q->tail = q->tail->next;
    }
}
