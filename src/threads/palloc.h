#ifndef THREADS_PALLOC_H
#define THREADS_PALLOC_H

#include <stddef.h>

/* How to allocate pages. */
enum palloc_flags
  {
    PAL_ASSERT = 001,           /* Panic on failure. */
    PAL_ZERO = 002,             /* Zero page contents. */
    PAL_USER = 004              /* User page. */
  };

void palloc_init (size_t user_page_limit);
void *palloc_get_page (enum palloc_flags);
void *palloc_get_multiple (enum palloc_flags, size_t page_cnt);
void palloc_free_page (void *);
void palloc_free_multiple (void *, size_t page_cnt);

size_t palloc_get_free_pages_cnt(void);

#include <bitmap.h> 
#include "threads/synch.h"
struct pool {
  struct lock lock;         /* Mutual exclusion. */
  struct bitmap *used_map;  /* Bitmap of free pages. */
  uint8_t *base;            /* Base of pool. */
};
extern struct pool kernel_pool;
extern struct pool user_pool;


#endif /* threads/palloc.h */
