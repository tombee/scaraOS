#ifndef __BLK_HEADER_INCLUDED__
#define __BLK_HEADER_INCLUDED__

struct buffer {
	struct blkdev 	*b_dev;
	block_t 	b_block;
	char 		*b_buf;
	size_t		b_len;
};

struct blkdev {
	/* Used only by bio subsystem */
	struct blkdev *next;

	/* Hardcoded by driver */
	const char *name;
	unsigned int sectsize;
	int (*ll_rw_blk)(struct blkdev *, int, block_t, char *, size_t);

	/* Can be frobbed with */
	size_t count;

	/* Held by block subsystem on ll_rw_blk calls */
	struct semaphore blksem;
};

/* Block and buffer cache */
void blk_init(void);
struct buffer *blk_read(struct blkdev *, int);
int blk_set_blocksize(struct blkdev *, unsigned int);
void blk_free(struct buffer *);

/* Block device maangement */
void blkdev_add(struct blkdev *);
struct blkdev *blkdev_get(const char *);

#endif /* __BLK_HEADER_INCLUDED__ */
