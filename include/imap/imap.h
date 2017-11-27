/*
 * imap.h - map for uint64_t integer keys
 *
 * author       : Jeroen van der Heijden
 * email        : jeroen@transceptor.technology
 * copyright    : 2016, Transceptor Technology
 *
 * changes
 *  - initial version, 03-08-2016
 *
 */
#pragma once

#include <inttypes.h>
#include <stddef.h>
#include <slist/slist.h>

typedef struct imap_node_s imap_node_t;
typedef struct imap_s imap_t;

typedef int (*imap_cb)(void * data, void * args);
typedef int (*imap_free_cb)(void * data);

typedef void (*imap_update_cb)(
        imap_t * dest,
        imap_t * imap,
        imap_free_cb decref_cb);

struct imap_node_s
{
    size_t size;
    void * data ;
    imap_node_t * nodes;
};

struct imap_s
{
    size_t len;
    slist_t * slist;
    imap_node_t nodes[];
};

imap_t * imap_new(void);
void imap_free(imap_t * imap, imap_free_cb cb);
int imap_set(imap_t * imap, uint64_t id, void * data);
int imap_add(imap_t * imap, uint64_t id, void * data);
void * imap_get(imap_t * imap, uint64_t id);
void * imap_pop(imap_t * imap, uint64_t id);
int imap_walk(imap_t * imap, imap_cb cb, void * data);
void imap_walkn(imap_t * imap, size_t * n, imap_cb cb, void * data);
slist_t * imap_slist(imap_t * imap);
slist_t * imap_slist_pop(imap_t * imap);
slist_t * imap_2slist(imap_t * imap);
slist_t * imap_2slist_ref(imap_t * imap);
void imap_union_ref(
        imap_t * dest,
        imap_t * imap,
        imap_free_cb decref_cb);
void imap_intersection_ref(
        imap_t * dest,
        imap_t * imap,
        imap_free_cb decref_cb);
void imap_difference_ref(
        imap_t * dest,
        imap_t * imap,
        imap_free_cb decref_cb);
void imap_symmetric_difference_ref(
        imap_t * dest,
        imap_t * imap,
        imap_free_cb decref_cb);
