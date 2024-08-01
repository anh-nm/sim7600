/*
 * struc_queue.h
 *
 *  Created on: Jul 26, 2024
 *      Author: MinhAnh
 */

#ifndef STRUC_QUEUE_H_
#define STRUC_QUEUE_H_

#include <stdint.h>
#include <stdint.h>
#include "string.h"

#define MAX_QUEUE_SIZE  (4096)

typedef struct {
    uint32_t sizeof_item;
    uint32_t num_items;
    uint32_t head;
    uint32_t tail;
    uint8_t buffer[MAX_QUEUE_SIZE];
} sq_t;

uint8_t sq_init(sq_t *queue, uint32_t sizeof_item, uint32_t num_items);
uint8_t sq_push(sq_t *queue, void *item);
uint8_t sq_pop(sq_t *queue, void *item);
uint8_t sq_is_empty(sq_t *queue);
uint8_t sq_is_full(sq_t *queue);
//void sq_free(sq_t *queue);




#endif /* STRUC_QUEUE_H_ */
