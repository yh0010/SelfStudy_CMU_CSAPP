/**
 * @file queue.c
 * @brief Implementation of a queue that supports FIFO and LIFO operations.
 *
 * This queue implementation uses a singly-linked list to represent the
 * queue elements. Each queue element stores a string value.
 *
 * Assignment for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Extended to store strings, 2018
 *
 * TODO: fill in your name and Andrew ID
 * @author XXX <XXX@andrew.cmu.edu>
 */

#include "queue.h"
#include "harness.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * @brief Allocates a new queue
 * @return The new queue, or NULL if memory allocation failed
 */
queue_t *queue_new(void) {
    queue_t *q = malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if (q) {
        q->head = NULL;
        q->tail = NULL;
        q->qsize = 0;
    }
    return q;
}

/**
 * @brief Frees all memory used by a queue
 * @param[in] q The queue to free
 */
void queue_free(queue_t *q) {
    /* How about freeing the list elements and the strings? */
    if (q) {
        list_ele_t *newh;
        while (q->head) {
            newh = q->head->next;
            free(q->head->value);
            free(q->head);
            q->head = newh;
        }
        free(q);
    }
}

/**
 * @brief Attempts to insert an element at head of a queue
 *
 * This function explicitly allocates space to create a copy of `s`.
 * The inserted element points to a copy of `s`, instead of `s` itself.
 *
 * @param[in] q The queue to insert into
 * @param[in] s String to be copied and inserted into the queue
 *
 * @return true if insertion was successful
 * @return false if q is NULL, or memory allocation failed
 */
bool queue_insert_head(queue_t *q, const char *s) {
    /* What should you do if the q is NULL? */

    if (q) {
        // list_ele_t *newh = (list_ele_t *)malloc(sizeof(list_ele_t));
        // newh->value = malloc(strlen(s) + 1);
        list_ele_t *newh;
        while (!(newh = (list_ele_t *)malloc(sizeof(list_ele_t)))) {
        }
        while (!(newh->value = malloc(strlen(s) + 1))) {
        }
        strcpy(newh->value, s);

        if (q->head == NULL) {
            newh->next = NULL;
            q->tail = newh;
        } else
            newh->next = q->head;
        q->head = newh;
        q->qsize++;
        return true;
    }
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    return false;
}

/**
 * @brief Attempts to insert an element at tail of a queue
 *
 * This function explicitly allocates space to create a copy of `s`.
 * The inserted element points to a copy of `s`, instead of `s` itself.
 *
 * @param[in] q The queue to insert into
 * @param[in] s String to be copied and inserted into the queue
 *
 * @return true if insertion was successful
 * @return false if q is NULL, or memory allocation failed
 */
bool queue_insert_tail(queue_t *q, const char *s) {
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */

    if (q) {
        // list_ele_t *newh = (list_ele_t *)malloc(sizeof(list_ele_t));
        // newh->value = malloc(strlen(s) + 1);
        list_ele_t *newh;
        while (!(newh = (list_ele_t *)malloc(sizeof(list_ele_t)))) {
        } // as a response to malloc faliure percentage
        while (!(newh->value = malloc(strlen(s) + 1))) {
        }
        strcpy(newh->value, s);
        newh->next = NULL;

        if (q->tail != NULL)
            q->tail->next = newh;
        else
            q->head = newh;
        q->tail = newh;
        q->qsize++;
        return true;
    }
    return false;
}

/**
 * @brief Attempts to remove an element from head of a queue
 *
 * If removal succeeds, this function frees all memory used by the
 * removed list element and its string value before returning.
 *
 * If removal succeeds and `buf` is non-NULL, this function copies up to
 * `bufsize - 1` characters from the removed string into `buf`, and writes
 * a null terminator '\0' after the copied string.
 *
 * @param[in]  q       The queue to remove from
 * @param[out] buf     Output buffer to write a string value into
 * @param[in]  bufsize Size of the buffer `buf` points to
 *
 * @return true if removal succeeded
 * @return false if q is NULL or empty
 */
bool queue_remove_head(queue_t *q, char *buf, size_t bufsize) {
    /* You need to fix up this code. */
    list_ele_t *nxt_hd;
    char *ch, *ch_copy, *buf_cpy;

    if (q && q->head) {
        nxt_hd = q->head->next;
        q->head->next = NULL;
        ch = malloc(strlen(q->head->value) + 1);
        strcpy(ch, q->head->value);
        free(q->head->value);
        free(q->head);
        if (nxt_hd) {
            q->head = nxt_hd;
        } else {
            q->tail = NULL;
            q->head = NULL;
        }

        q->qsize--;
        ch_copy = ch;
        buf_cpy = buf;

        if (buf != NULL) {
            // printf("%s%zu\n", "bufsieze: ", bufsize);
            while (--bufsize > 0 && *ch != '\0') {
                // printf("%c", *ch);
                *buf++ = *ch++;
            }
            *buf = '\0';
            free(ch_copy);
            // printf("\n%s%s\n", "storedBUF: ", buf_cpy);
            return true;
        } else {
            free(ch_copy);
            return true;
        }
    }
    return false;
}

/**
 * @brief Returns the number of elements in a queue
 *
 * This function runs in O(1) time.
 *
 * @param[in] q The queue to examine
 *
 * @return the number of elements in the queue, or
 *         0 if q is NULL or empty
 */
size_t queue_size(queue_t *q) {
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    if (q && q->qsize > 0)
        return q->qsize;
    return 0;
}

/**
 * @brief Reverse the elements in a queue
 *
 * This function does not allocate or free any list elements, i.e. it does
 * not call malloc or free, including inside helper functions. Instead, it
 * rearranges the existing elements of the queue.
 *
 * @param[in] q The queue to reverse
 */
void queue_reverse(queue_t *q) {
    /* You need to write the code for this function */

    if (q && q->head) {
        if (q->qsize > 1) {
            list_ele_t *left, *mid, *right;
            right = q->head;
            q->head = q->tail;
            q->tail = right;
            right = right->next;
            q->tail->next = NULL;
            left = q->tail;

            while (right) {
                mid = right;
                right = right->next;
                mid->next = left;
                left = mid;
            }
        }
    }
}
