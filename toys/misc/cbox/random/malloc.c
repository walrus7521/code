#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// api
void ffree(void *ap);
void *mmalloc(unsigned nbytes);


// internal private code
typedef long Align; /* for alignment to long boundary */
union header { /* block header */
    struct {
        union header *ptr; /* next block if on free list */
        unsigned size; /* size of this block */
    } s;
    Align x; /* force alignment of blocks */
};

typedef union header Header;

static Header base; /* empty list to get started */
static Header *freep = NULL; /* start of free list */
static Header *morecore(unsigned nu);

char block[1024*1024];
int ptr = 0;
char *sbrk(int n)
{
    printf("requesting %d bytes\n", n);
    char *ret = &block[ptr];
    ptr += n;
    return ret;
}

#define NALLOC 1024 /* minimum #units to request */
/* morecore: ask system for more memory */

static Header *morecore(unsigned nu)
{
    char *cp, *sbrk(int);
    Header *up;

    printf("morecore: %d\n", nu);
    if (nu < NALLOC) {
        nu = NALLOC;
    }

    cp = sbrk(nu * sizeof(Header));
    if (cp == (char *) -1) { /* no space at all */
        printf("no space\n");
        return NULL;
    }
    up = (Header *) cp;
    up->s.size = nu;
    ffree((void *)(up+1));

    return freep;
}



void *mmalloc(unsigned nbytes)
{
    Header *p, *prevp;
    Header *morecore(unsigned);
    unsigned nunits;
    nunits = (nbytes+sizeof(Header)-1)/sizeof(Header) + 1;
    if ((prevp = freep) == NULL) { /* no free list yet */
        base.s.ptr = freep = prevp = &base;
        base.s.size = 0;
    }
    for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr) {
        if (p->s.size >= nunits) { /* big enough */
            if (p->s.size == nunits) /* exactly */
                prevp->s.ptr = p->s.ptr;
            else { /* allocate tail end */
                p->s.size -= nunits;
                p += p->s.size;
                p->s.size = nunits;
            }
            freep = prevp;
            return (void *)(p+1);
        }
        if (p == freep) { /* wrapped around free list */
            if ((p = morecore(nunits)) == NULL) {
                return NULL; /* none left */
            }
        }
    }
}

/* free: put block ap in free list */
void ffree(void *ap) {
    Header *bp, *p;
    bp = (Header *)ap - 1; /* point to block header */
    for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
        if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
            break; /* freed block at start or end of arena */
    if (bp + bp->s.size == p->s.ptr) {
        bp->s.size += p->s.ptr->s.size;
        bp->s.ptr = p->s.ptr->s.ptr;
    } else {
        bp->s.ptr = p->s.ptr;
    }

    if (p + p->s.size == bp) {
        p->s.size += bp->s.size;
        p->s.ptr = bp->s.ptr;
    } else {
        p->s.ptr = bp;
    }
    freep = p;
}

int main()
{
    char *p;
    int i;

    for (i = 0; i < 16*1024; i++) {
        printf("iteration: %d\n", i);
        p = mmalloc(42);
        strcpy(p, "namesuperwoiuoweirnweroioiwerbart");    
        printf("name: %s\n", p);
        ffree(p);
        p = mmalloc(42);
        strcpy(p, "rankeruownasdvnlkauoiuqwerwq");    
        printf("rank: %s\n", p);
        ffree(p);
    }
}

