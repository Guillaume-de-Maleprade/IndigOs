#include "type.h"

typedef struct 
{
	UINT32   bg_block_bitmap;        /* Blocks bitmap block */
	UINT32   bg_inode_bitmap;        /* Inodes bitmap block */
	UINT32   bg_inode_table;         /* Inodes table block */
	UINT16   bg_free_blocks_count;   /* Free blocks count */
	UINT16   bg_free_inodes_count;   /* Free inodes count */
	UINT16   bg_used_dirs_count;     /* Directories count */
	UINT16   bg_pad;                 
	UINT32   bg_reserved[3];         /* Unused */
} GroupDescriptor;