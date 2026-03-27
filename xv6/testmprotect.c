#include "types.h"
#include "stat.h"
#include "user.h"
#include "mmu.h"

int main(void) {
  char *page = sbrk(PGSIZE);         // allocate one page

  // Write to it before protecting
  page[0] = 'A';
  printf(1, "write before mprotect: OK\n");

  // Protect it
  if(mprotect(page, PGSIZE) < 0){
    printf(1, "mprotect failed\n");
    exit();
  }
  printf(1, "mprotect: OK\n");

  // This write should trigger a page fault and kill the process
  page[0] = 'B';
  printf(1, "UNEXPECTED: write succeeded after mprotect\n");
  exit();
}
