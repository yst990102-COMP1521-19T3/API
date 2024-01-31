// Simulate LRU replacement of page frames

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct ipt_entry {
    int virtual_page;
    int last_access_time;
} ipt_entry_t;


void lru(int n_physical_pages, int n_virtual_pages);
void access_page(int virtual_page, int access_time, int n_physical_pages, struct ipt_entry *ipt);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <n-physical-pages> <n-virtual-pages>\n", argv[0]);
        return 1;
    }
    lru(atoi(argv[1]), atoi(argv[2]));
    return 0;
}

void lru(int n_physical_pages, int n_virtual_pages) {
    printf("Simulating %d pages of physical memory, %d pages of virtual memory\n",
          n_physical_pages, n_virtual_pages);
    struct ipt_entry *ipt = malloc(n_physical_pages * sizeof *ipt);
    assert(ipt);

    for (int i = 0; i < n_physical_pages; i++) {
        ipt[i].virtual_page = -1;
        ipt[i].last_access_time = -1;
    }

    int virtual_page;
    for (int access_time = 0; scanf("%d", &virtual_page) == 1; access_time++) {
        assert(virtual_page >= 0 && virtual_page < n_virtual_pages);
        access_page(virtual_page, access_time, n_physical_pages, ipt);
    }
}

void access_page(int virtual_page, int access_time, int n_physical_pages, struct ipt_entry *ipt) {
    int physical_page_to_use = 0;

    for (int pp = 0; pp < n_physical_pages; pp++) {
        if (ipt[pp].virtual_page == virtual_page) {
            physical_page_to_use = pp;
            break;
        }

        if (ipt[pp].last_access_time < ipt[physical_page_to_use].last_access_time) {
            physical_page_to_use = pp;
        }
    }

    int vp = ipt[physical_page_to_use].virtual_page;

    printf("Time %d: virtual page %d ", access_time, virtual_page);
    if (vp == virtual_page) {
        printf("->");
    } else if (vp == -1) {
        printf("loaded to");
    } else {
        printf(" - virtual page %d evicted - loaded to", vp);
    }
    printf(" physical page %d\n", physical_page_to_use);

    ipt[physical_page_to_use].virtual_page = virtual_page;
    ipt[physical_page_to_use].last_access_time = access_time;
}
