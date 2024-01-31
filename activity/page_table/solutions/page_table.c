// Simulate LRU replacement of page frames

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define READ_ACCESS  0x1
#define WRITE_ACCESS 0x2

// represent an entry in a simple page table
typedef struct pt_entry {
    int physical_page;
    int permissions;      // READ_ACCESS and/or WRITE_ACCESS may be set
} pt_entry_t;

// represent an entry in a simple inverted page table

typedef struct ipt_entry {
    int virtual_page;        // == -1 if physical page free
    int last_access_time;
} ipt_entry_t;


void page_table(int n_physical_pages, int n_virtual_pages);
void page_access(int action, int virtual_page, int access_time,
                 int n_virtual_pages, int n_physical_pages,
                 struct pt_entry *page_table, struct ipt_entry *inverted_page_table);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <n-physical-pages> <n-virtual-pages>\n", argv[0]);
        return 1;
    }
    page_table(atoi(argv[1]), atoi(argv[2]));
    return 0;
}


void page_table(int n_physical_pages, int n_virtual_pages) {
    printf("Simulating %d pages of physical memory, %d pages of virtual memory\n",
          n_physical_pages, n_virtual_pages);

    struct pt_entry *page_table = malloc(n_virtual_pages * sizeof *page_table);
    assert(page_table);

    struct ipt_entry *inverted_page_table = malloc(n_physical_pages * sizeof *inverted_page_table);
    assert(inverted_page_table);

    for (int i = 0; i < n_virtual_pages; i++) {
        page_table[i].physical_page = -1;
        page_table[i].permissions = 0;
    }

    for (int i = 0; i < n_physical_pages; i++) {
        inverted_page_table[i].virtual_page = -1;
        inverted_page_table[i].last_access_time = 0;
    }

    int virtual_page;
    char action;
    for (int access_time = 0; scanf(" %c%d", &action, &virtual_page) == 2; access_time++) {
        assert(virtual_page >= 0 && virtual_page < n_virtual_pages);
        assert(strchr("RWrwU", action) != NULL);
        page_access(action, virtual_page, access_time, n_virtual_pages, n_physical_pages,
                    page_table, inverted_page_table);
    }
}


void page_access(int action, int virtual_page, int access_time,
                 int n_virtual_pages, int n_physical_pages,
                 struct pt_entry *page_table, struct ipt_entry *inverted_page_table) {
    printf("Time %d: virtual page %d ", access_time, virtual_page);
    if (action == 'R') {
        page_table[virtual_page].permissions |= READ_ACCESS;
        printf("mapped read-only\n");
        return;
    }

    if (action == 'W') {
        page_table[virtual_page].permissions |= (READ_ACCESS|WRITE_ACCESS);
        printf("mapped read-write\n");
        return;
    }

    int physical_page = page_table[virtual_page].physical_page;

    if (action == 'U') {
        if (page_table[virtual_page].permissions == 0) {
            printf("not mapped\n");
            return;
        }
        page_table[virtual_page].physical_page = -1;
        page_table[virtual_page].permissions = 0;
        printf("unmapped");
        if (physical_page != -1) {
            inverted_page_table[physical_page].virtual_page = -1;
            printf(" - physical page %d now free" , physical_page);
        }
        printf("\n");
        return;
    }

    //action must be 'r' (read) or 'w'(write)
    char *access_type = action == 'w' ? "write" : "read";
    printf(" - %s access - ", access_type);

    if (
        (action == 'r' && !(page_table[virtual_page].permissions & READ_ACCESS)) ||
        (action == 'w' && !(page_table[virtual_page].permissions & WRITE_ACCESS))
       ) {
        printf("illegal\n");
        return;
    }

    if (physical_page != -1) {
        printf("at physical page %d\n" , physical_page);
        inverted_page_table[physical_page].last_access_time = access_time;
        return;
    }

    // Page fault must find a free page or evict the least-recently-accessed page

    int physical_page_to_use = 0;
    for (int pp = 0; pp < n_physical_pages; pp++) {
        if (inverted_page_table[pp].virtual_page == -1) {
            physical_page_to_use = pp;
            break;
        }
        if (inverted_page_table[pp].last_access_time <
            inverted_page_table[physical_page_to_use].last_access_time) {
            physical_page_to_use = pp;
        }
    }

    int evicted_virtual_page = inverted_page_table[physical_page_to_use].virtual_page;

    if (evicted_virtual_page == -1) {
        printf("loaded to");
    } else {
        printf("virtual page %d evicted - loaded to", evicted_virtual_page);
        page_table[evicted_virtual_page].physical_page = -1;
    }
    printf(" physical page %d\n", physical_page_to_use);

    page_table[virtual_page].physical_page = physical_page_to_use;
    inverted_page_table[physical_page_to_use].virtual_page = virtual_page;
    inverted_page_table[physical_page_to_use].last_access_time = access_time;
}
