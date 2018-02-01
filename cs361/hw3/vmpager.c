#include "stdlib.h"
#include "stdio.h"
#include "stdint.h"
#include "unistd.h"
#include "sys/stat.h"
#include "sys/mman.h"
#include "sys/stat.h"
#include "fcntl.h"

typedef struct {
        uint8_t pid;
        uint8_t page;
} MemoryAccess;

typedef struct {
        int inf_frame;   // -1 if not loaded
        int inf_pageHits;
        int inf_pageMisses;
        int fifo_frame;
        int fifo_pageHits;
        int fifo_pageMisses;
} PageTableEntry;

typedef struct {
        uint8_t pid;
        uint8_t page;
        uint8_t vacant;
} FrameTableEntry;

typedef struct {
        unsigned int tail;
        unsigned int count;
        unsigned int max;
} PageFIFO;

#define PAGETABLESIZE 256
#define NPROCESSES 256

int main(int argc, char *argv[])
{
        // class info
        printf("Name: Gregory N. Schmit\nNetID: 667397912\nACCC (Systems) Account: temp150\n\n");

        // defs
        if (argc < 2) { return 0; }
        char* path = argv[1];
        int lim_memacc;
        int n_memacc;
        int ft_size;
        int file;
        int f_size;
        struct stat *f_stats;
        int i, j;
        MemoryAccess *memacc;

        // print target file
        printf("CLI Option 1 :: Target File: %s\n", argv[1]);

        // cli option parsing
        if (argc > 2) {
                lim_memacc = atoi(argv[2]);
                if (lim_memacc < 0) { lim_memacc = 0; }
        } else {
                lim_memacc = 0;
        }
        // print limit provided on memory accesses
        printf("CLI Option 2 :: Memacc Limit: %i\n", lim_memacc);
        if (argc > 3) {
                ft_size = atoi(argv[3]);
                if (ft_size < 1) { ft_size = 256; }
        } else {
                ft_size = 256;
        }
        // print size of frame table
        printf("CLI Option 3 :: Frame Table Size: %i\n\n", ft_size);

        // open file and load values
        file = open(path, O_RDWR);
        if (file <= 0) {
                printf("open problem\n");
                return 1;
        }
        f_stats = calloc(1, sizeof(*f_stats));
        i = fstat(file, f_stats);
        if (i != 0) {
                printf("fstat problem\n");
                return 2;
        }
        f_size = f_stats->st_size;
        memacc = (MemoryAccess*)mmap(0, f_size, PROT_READ, MAP_PRIVATE, file, 0);
        if (memacc == MAP_FAILED) { printf("MAP_FAILED\n"); return 0; }
        // get number of memaccs that I have now
        if (lim_memacc <= 0) {
                n_memacc = f_size / sizeof(MemoryAccess);
        } else {
                n_memacc = lim_memacc;
        }

        // build page tables
        PageTableEntry page_tables[PAGETABLESIZE][NPROCESSES];
        for (i=0; i<PAGETABLESIZE; i++) {
                for (j=0; j<NPROCESSES; j++) {
                        page_tables[i][j].inf_frame = -1;
                        page_tables[i][j].inf_pageHits = 0;
                        page_tables[i][j].inf_pageMisses = 0;
                        page_tables[i][j].fifo_frame = -1;
                        page_tables[i][j].fifo_pageHits = 0;
                        page_tables[i][j].fifo_pageMisses = 0;
                }
        }
        PageTableEntry global_page_table;
        global_page_table.inf_pageHits = 0;
        global_page_table.inf_pageMisses = 0;
        global_page_table.inf_frame = -1;
        global_page_table.fifo_pageHits = 0;
        global_page_table.fifo_pageMisses = 0;
        global_page_table.fifo_frame = -1;

        // build frame table
        FrameTableEntry *frame = calloc(sizeof(*frame), ft_size);
        for (i=0; i<ft_size; i++) {
                frame[i].vacant = 1;
        }

        // build FIFO tracking struct
        PageFIFO fifo;
        fifo.tail = 0;
        fifo.count = 0;
        fifo.max = ft_size;
        
        // simulation algorithm
        for (i=0; i<n_memacc; i++) {
                uint8_t page = memacc[i].page;
                uint8_t pid = memacc[i].pid;
                PageTableEntry *pt = &page_tables[page][pid];
                // inf
                if (pt->inf_frame == -1) {
                        // page miss
                        pt->inf_pageMisses++;
                        global_page_table.inf_pageMisses++;
                        // now, load missing page
                        pt->inf_frame = 1;
                } else {
                        // page hit
                        pt->inf_pageHits++;
                        global_page_table.inf_pageHits++;
                }
                // fifo
                if (pt->fifo_frame == -1) {
                        // page miss
                        pt->fifo_pageMisses++;
                        global_page_table.fifo_pageMisses++;
                        // now, load missing page
                        // select frame to use
                        int fr;
                        if (!fifo.count) {
                                // first frame entry
                                fr = 0;
                                fifo.count = 1;
                                fifo.tail = 0;
                        } else {
                                fifo.tail++;
                                if (fifo.tail >= fifo.max) {
                                        fifo.tail = 0;
                                }
                                fr = fifo.tail;
                                // if displacing victim page, don't increment fifo count
                                //  and delete victim first
                                if (fifo.count < fifo.max) {
                                        fifo.count++;
                                } else {
                                        // maxed out the fifo! displace victim page
                                        page_tables[frame[fr].page][frame[fr].pid].fifo_frame = -1;
                                }
                        }
                        // record frame in pt
                        pt->fifo_frame = fr;
                        // mark frame as containing new page
                        frame[fr].page = memacc[i].page;
                        frame[fr].pid = memacc[i].pid;
                        frame[fr].vacant = 0;
                } else {
                        // page hit
                        pt->fifo_pageHits++;
                        global_page_table.fifo_pageHits++;
                }
        }

        // print global statistics
        printf("1) Infinite Memory Algorithm:\n");
        printf("   Page Hits:    %i\n", global_page_table.inf_pageHits);
        printf("   Page Misses:  %i\n", global_page_table.inf_pageMisses);
        printf("\n");
        printf("2) FIFO Memory Algorithm:\n");
        printf("   Page Hits:    %i\n", global_page_table.fifo_pageHits);
        printf("   Page Misses:  %i\n", global_page_table.fifo_pageMisses);
        printf("\n");

        printf("unmapping memacc; freeing frame\n");
        munmap(memacc, f_size);
        free(frame);
        return 0;
}
