#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "mm.h"
#include "memlib.h"

#define WSIZE       4       /* word size (bytes) */  
#define DSIZE       8       /* doubleword size (bytes) */
#define CHUNKSIZE  (1<<12)  /* initial heap size (bytes) */
#define OVERHEAD   8        /* overhead of header and footer (bytes) */
#define MIN        24       /* having a set minimum block size allows for everythiing 
                               to be properly be stored*/ 

#define MAX(x, y) ((x) > (y)? (x) : (y))  

/* Pack a size and allocated bit into a word */
#define PACK(size, alloc)  ((size) | (alloc))

/* Read and write a word at address p */
/* NB: this code calls a 32-bit quantity a word */
#define GET(p)       (*(unsigned int *)(p))
#define PUT(p, val)  (*(unsigned int *)(p) = (val))  

/* Read the size and allocated fields from address p */
#define GET_SIZE(p)  (GET(p) & ~0x7)
#define GET_ALLOC(p) (GET(p) & 0x1)

/* Given block ptr bp, compute address of its header and footer */
#define HDRP(bp)       ((char *)(bp) - WSIZE)  
#define FTRP(bp)       ((char *)(bp) + GET_SIZE(HDRP(bp)) - DSIZE)

/* Given block ptr bp, compute address of next and previous blocks */
#define NEXT_BLKP(bp)  ((char *)(bp) + GET_SIZE(((char *)(bp) - WSIZE)))
#define PREV_BLKP(bp)  ((char *)(bp) - GET_SIZE(((char *)(bp) - DSIZE)))

/*Finds previous and next pointer given a current pointer */
#define POINT_PREV(bp)  (*(unsigned long *)bp)
#define POINT_NEXT(bp)  (*(unsigned long *)(bp + OVERHEAD))
/* $end mallocmacros */

/* Global variables */
static char *list_free_blocks = 0; //List of all free blocks. 
static char *heap_listp = 0;  /* pointer to first block */  

/* function prototypes for internal helper routines */
static void *extend_heap(size_t words);
static void place(void *bp, size_t asize);
static void *find_fit(size_t asize);
static void *coalesce(void *bp);
static void printblock(void *bp); 
static void checkblock(void *bp);
static void insert_node(void *bp);
static void remove_node(void *bp);
static size_t align_size(size_t orig_size);

 //mm_init - Initialize the memory manager 
int mm_init(void) 
{
  /* create the initial empty heap */
  if ((heap_listp = mem_sbrk(2*MIN)) == NULL)
    return -1;

  PUT(heap_listp, 0);                        /* alignment padding */
  PUT(heap_listp+WSIZE, PACK(MIN, 1));  /* prologue header */ 
  PUT(heap_listp+ MIN, PACK(MIN, 1));  /* prologue footer */ 
  PUT(heap_listp+WSIZE+MIN, PACK(0, 1));   /* epilogue header */

  list_free_blocks = heap_listp + (2*WSIZE);

  /* Initialize the Pointers for list_free*/
  PUT(heap_listp + DSIZE, 0); //Pointer to previous.
  PUT(heap_listp + (3*WSIZE), 0); //Pointer to next.

  /* Extend the empty heap with a free block of CHUNKSIZE bytes */
  if (extend_heap(CHUNKSIZE/WSIZE) == NULL)
    return -1;
  return 0;
}

// malloc - Allocate a block with at least size bytes of payload 
void *mm_malloc(size_t size)
{
  size_t asize;      /* adjusted block size */
  size_t extendsize; /* amount to extend heap if no fit */
  char *bp;      

  if (heap_listp == 0)
  {
    mm_init();
  }

  /* Ignore spurious requests */
  if (size <= 0)
    return NULL;

  asize = align_size(size) + DSIZE;
  if(asize < MIN)
  {
    asize = MIN;
  }

  /* Search the free list for a fit */
  if ((bp = find_fit(asize)) != NULL) 
  {
    place(bp, asize);
    return bp;
  }

  /* No fit found. Get more memory and place the block */
  extendsize = MAX(asize,CHUNKSIZE);
  if ((bp = extend_heap(extendsize/WSIZE)) == NULL)
    return NULL;
  place(bp, asize);
  return bp;
} 

 // free - Free a block 
void mm_free(void *bp)
{
  if(bp == 0) return;

  size_t size = GET_SIZE(HDRP(bp));
  if (heap_listp == 0)
  {
    mm_init();
  }

  PUT(HDRP(bp), PACK(size, 0));
  PUT(FTRP(bp), PACK(size, 0));
  coalesce(bp);
  //mm_checkheap(0);
}

 //realloc - naive implementation of realloc
void *mm_realloc(void *ptr, size_t size)
{
  size_t oldsize;
  void *newptr;

  /* If size == 0 then this is just free, and we return NULL. */
  if(size == 0) 
  {
    mm_free(ptr);
    return 0;
  }

  /* If oldptr is NULL, then this is just malloc. */
  if(ptr == NULL) {
    return mm_malloc(size);
  }

  newptr = mm_malloc(size);

  /* If realloc() fails the original block is left untouched  */
  if(!newptr) {
    return 0;
  }

  /* Copy the old data. */
  oldsize = GET_SIZE(HDRP(ptr));
  if(size < oldsize) oldsize = size;
  memcpy(newptr, ptr, oldsize);

  /* Free the old block. */
  mm_free(ptr);

  return newptr;
}

/* 
 * checkheap - Minimal check of the heap for consistency 
 */
void mm_checkheap(int verbose)
{
  char *bp = heap_listp;

  if (verbose)
    printf("Heap (%p):\n", heap_listp);

  if ((GET_SIZE(HDRP(heap_listp)) != DSIZE) || !GET_ALLOC(HDRP(heap_listp)))
    printf("Bad prologue header\n");
  checkblock(heap_listp);

  for (bp = heap_listp; GET_SIZE(HDRP(bp)) > 0; bp = NEXT_BLKP(bp)) {
    if (verbose) 
      printblock(bp);
    checkblock(bp);
  }

  if (verbose)
    printblock(bp);
  if ((GET_SIZE(HDRP(bp)) != 0) || !(GET_ALLOC(HDRP(bp))))
    printf("Bad epilogue header\n");
}

/* The remaining routines are internal helper routines */

/* 
 * extend_heap - Extend heap with free block and return its block pointer
 */
/* $begin mmextendheap */
static void *extend_heap(size_t words) 
{
  char *bp;
  size_t size;
  void *return_ptr;

  /* Allocate an even number of words to maintain alignment */
  size = (words % 2) ? (words+1) * WSIZE : words * WSIZE;
  if ((long)(bp = mem_sbrk(size)) < 0) 
    return NULL;

  /* Initialize free block header/footer and the epilogue header */
  PUT(HDRP(bp), PACK(size, 0));         /* free block header */
  PUT(FTRP(bp), PACK(size, 0));         /* free block footer */
  PUT(HDRP(NEXT_BLKP(bp)), PACK(0, 1)); /* new epilogue header */

  /* Coalesce if the previous block was free */
  return_ptr = coalesce(bp);
  //mm_checkheap(0);
  return return_ptr;
}
/* $end mmextendheap */

/* 
 * place - Place block of asize bytes at start of free block bp 
 *         and split if remainder would be at least minimum block size */
static void place(void *bp, size_t asize)
  /* $end mmplace-proto */
{
  size_t csize = GET_SIZE(HDRP(bp));   

  if ((csize - asize) >= MIN) 
  { 
    remove_node(bp); //Node can be used
    PUT(HDRP(bp), PACK(asize, 1));
    PUT(FTRP(bp), PACK(asize, 1));
    bp = NEXT_BLKP(bp);
    PUT(HDRP(bp), PACK(csize-asize, 0));
    PUT(FTRP(bp), PACK(csize-asize, 0));
    coalesce(bp); //Coalesce it. 
  }
  else { 
    remove_node(bp); //use node.
    PUT(HDRP(bp), PACK(csize, 1));
    PUT(FTRP(bp), PACK(csize, 1));
  }
}

/* find_fit - Find a fit for a block with asize bytes */
//Decided not to do next fit so just took it out. 
static void *find_fit(size_t asize)
{
  void *bp;

  for (bp = list_free_blocks; GET_ALLOC(HDRP(bp)) <= 0; bp = (void **)POINT_NEXT(bp)) {
    if (asize <= GET_SIZE(HDRP(bp)))
   {
      return bp;
    }
  }
  return NULL; /* no fit */
}

/* coalesce - boundary tag coalescing. Return ptr to coalesced block */
static void *coalesce(void *bp) 
{
  size_t prev_alloc = GET_ALLOC(FTRP(PREV_BLKP(bp))); 
  size_t next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(bp)));
  size_t size = GET_SIZE(HDRP(bp));

  if(PREV_BLKP(bp) == bp)
  {
    prev_alloc = 1;
  }

  if (prev_alloc && next_alloc) {            /* Case 1 */
    insert_node(bp);
    return bp;
  }

  else if (prev_alloc && !next_alloc) {      /* Case 2 */
    remove_node(NEXT_BLKP(bp));
    size += GET_SIZE(HDRP(NEXT_BLKP(bp)));
    PUT(HDRP(bp), PACK(size, 0));
    PUT(FTRP(bp), PACK(size,0));
    insert_node(bp);
  }

  else if (!prev_alloc && next_alloc) {      /* Case 3 */
    size += GET_SIZE(HDRP(PREV_BLKP(bp)));
    bp = PREV_BLKP(bp); //Had to move bp assignage to previous_blk up.
    remove_node(bp);
    PUT(HDRP(bp), PACK(size, 0));
    PUT(FTRP(bp), PACK(size, 0));
    insert_node(bp);
  }

  else {                                     /* Case 4 */
    size += GET_SIZE(HDRP(PREV_BLKP(bp))) + 
      GET_SIZE(FTRP(NEXT_BLKP(bp)));
    remove_node(NEXT_BLKP(bp));
    remove_node(PREV_BLKP(bp));
    bp = PREV_BLKP(bp);
    PUT(HDRP(bp), PACK(size, 0));
    PUT(FTRP(bp), PACK(size, 0));
    insert_node(bp);
  }  
      return bp;
}


static void printblock(void *bp) 
{
  size_t hsize;//, halloc, fsize, falloc;

  hsize = GET_SIZE(HDRP(bp));
  //halloc = GET_ALLOC(HDRP(bp));  
  //fsize = GET_SIZE(FTRP(bp));
  //falloc = GET_ALLOC(FTRP(bp));  

  if (hsize == 0) {
    printf("%p: EOL\n", bp);
    return;
  }

  /*  printf("%p: header: [%p:%c] footer: [%p:%c]\n", bp, 
      hsize, (halloc ? 'a' : 'f'), 
      fsize, (falloc ? 'a' : 'f')); */
}

static void checkblock(void *bp) 
{
  if ((size_t)bp % 8)
    printf("Error: %p is not doubleword aligned\n", bp);
  if (GET(HDRP(bp)) != GET(FTRP(bp)))
    printf("Error: header does not match footer\n");
}

void *mm_calloc (size_t nmemb, size_t size)
{
  void *ptr;
  if (heap_listp == 0){
    mm_init();
  }

  ptr = mm_malloc(nmemb*size);
  bzero(ptr, nmemb*size);


  return ptr;
}

//Aligns block correctly. 
static size_t align_size(size_t orig_size)
{
  size_t ret = (orig_size + (DSIZE-1));// & ~0x7;
  size_t rem = ret % 8;
  ret = ret - rem;
  return ret;
}

/*  remove node: If no previous block, sets list to next. 
    If previous, points node to the previous. */
static void remove_node(void *bp)
{
  //Assigns back pointer of next to previous of bp, skipping bp
   POINT_PREV(POINT_NEXT(bp)) = POINT_PREV(bp);

  if ((void **)POINT_PREV(bp) == NULL) 
  {
    list_free_blocks = (char *)POINT_NEXT(bp); 
  }

  if (POINT_PREV(bp))
  {
     POINT_NEXT(POINT_PREV(bp)) = POINT_NEXT(bp);
  }
}

/* insert node: puts new free block at front of the list.
   Need to do following 
    1. list points back to bp 
    2. bp points to list
    3. start of list now bp 
    4. bp back points to NULL   */
static void insert_node(void *bp)
{
  POINT_PREV(list_free_blocks) = (unsigned long)bp;
  POINT_NEXT(bp) = (unsigned long)list_free_blocks; 
  list_free_blocks = bp; 
  POINT_PREV(bp) = (unsigned long) NULL;
}



