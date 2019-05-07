#include "type.h"

/* list of all data for superBlock */
typedef struct
{
    UINT32   s_inodes_count;         /* Inodes count */
    UINT32   s_blocks_count;         /* Blocks count */
	UINT32   s_r_blocks_count;       /* Reserved blocks count */
	UINT32   s_free_blocks_count;    /* Free blocks count */
	UINT32   s_free_inodes_count;    /* Free inodes count */
	UINT32   s_first_data_block;     /* First Data Block */
	UINT32   s_log_block_size;       /* Block size */
	INT32    s_log_frag_size;        /* Fragment size */
	UINT32   s_blocks_per_group;     /* # Blocks per group */
	UINT32   s_frags_per_group;      /* # Fragments per group */
	UINT32   s_inodes_per_group;     /* # Inodes per group */
	UINT32   s_mtime;                /* Mount time */
	UINT32   s_wtime;                /* Write time */
	UINT16   s_mnt_count;            /* Mount count */
	INT16	 s_max_mnt_count;        /* Maximal mount count */
	UINT16   s_magic;                /* Magic signature */
	UINT16   s_state;                /* File system state */
	UINT16   s_errors;               /* Behaviour when detecting errors */
	UINT16   s_pad;                  /* Minor portion of version (combine with Major portion below to construct full version field)  */
	UINT32   s_lastcheck;            /* time of last check */
	UINT32   s_checkINTerval;        /* max. time between checks */
	UINT32   s_creator_os;           /* OS */
	UINT32   s_rev_level;            /* Revision level */
	UINT16   s_def_resuid;           /* Default uid for reserved blocks */
	UINT16   s_def_resgid;           /* Default gid for reserved blocks */
	UINT32	 s_first_inode;			 /* First inode */
	UINT32	 s_inode_size;			 /* Inodes size */
	UINT32   s_reserved[256*2+233];  /* Padding to the end of the block */
} superBlock;