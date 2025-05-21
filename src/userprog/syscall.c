#include "userprog/syscall.h"
#include <stdio.h>
#include <stdint.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"

#include "threads/palloc.h"//
#include "threads/vaddr.h" //
void list_mem_usage(void); // 


static void syscall_handler (struct intr_frame *);

void
syscall_init (void) 
{
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}
/*
static void
syscall_handler (struct intr_frame *f UNUSED) 
{
  printf ("system call!\n");
  thread_exit ();
}*/

static void
syscall_handler (struct intr_frame *f) 
{
  // Kiểm tra con trỏ hợp lệ trước khi sử dụng
  if (f == NULL || !is_user_vaddr(f->esp)) {
    thread_exit();
  }

  uint32_t syscall_num = *(uint32_t *)(f->esp);

  switch (syscall_num)
  {
    case SYS_LIST_MEM:
    list_mem_usage();
     break;
    
    default:
      printf("Unknown system call: %d\n", syscall_num);
      thread_exit();
      break;
  }
}

/*void list_mem_usage(void) {
  size_t free_pages = palloc_get_free_pages_cnt();
  size_t used_pages = (init_ram_pages- free_pages); // RAM_PAGES = tổng số trang

  printf("------ Memory Usage ------\n");
  printf("Used pages: %zu (%zu KB)\n", used_pages, used_pages * PGSIZE / 1024);
  printf("Free pages: %zu (%zu KB)\n", free_pages, free_pages * PGSIZE / 1024);
}
  */
 #include <bitmap.h> 
 extern struct pool kernel_pool;
extern struct pool user_pool;

void list_mem_usage(void) {
    size_t kernel_pages = bitmap_size(kernel_pool.used_map);
    size_t user_pages = bitmap_size(user_pool.used_map);
    size_t total_pages = kernel_pages + user_pages;

    size_t free_pages = palloc_get_free_pages_cnt();
    size_t used_pages = total_pages - free_pages;

    printf("------ Memory Usage ------\n");
    printf("Used pages: %zu (%zu KB)\n", used_pages, used_pages * PGSIZE / 1024);
    printf("Free pages: %zu (%zu KB)\n", free_pages, free_pages * PGSIZE / 1024);
}
