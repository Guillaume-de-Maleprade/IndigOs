/*  Ext2 signature (0xef53), used to help confirm the presence of Ext2 on a volume */
const UINT16 EXT2_SUPER_MAGIC = 0xEF53; 

/* Inode type */
const UINT16 INODE_TYPE_SYMBOL_LINK   = 0xA000; /* Symbolic link */
const UINT16 INODE_TYPE_FILE          = 0x8000; /* Regular file */
const UINT16 INODE_TYPE_DEV           = 0x6000; /* Block device */
const UINT16 INODE_TYPE_DIRECTORY     = 0x4000; /* Directory */
const UINT16 INODE_TYPE_CHAR_DEV      = 0x2000; /* Character device */
const UINT16 INODE_TYPE_FIFO          = 0x1000; /* FIFO */

/* Defined Reserved InodesConstant */
const UINT32 EXT2_BAD_INO			  = 1; /* bad blocks inode */
const UINT32 EXT2_ROOT_INO 			  = 2; /* root directory inode */
const UINT32 EXT2_ACL_IDX_INO		  = 3; /* ACL index inode (deprecated?) */
const UINT32 EXT2_ACL_DATA_INO		  = 4; /* ACL data inode (deprecated?) */
const UINT32 EXT2_BOOT_LOADER_INO	  = 5; /* boot loader inode */
const UINT32 EXT2_UNDEL_DIR_INO       = 6; /* undelete directory inode */

/* Ext2DirEntry file_types */
const UINT8 EXT2_FT_UNKNOWN	          = 0; /*Unknown File Type */
const UINT8 EXT2_FT_REG_FILE          = 1; /* Regular File */
const UINT8 EXT2_FT_DIR		          = 2; /* Directory File */
const UINT8 EXT2_FT_CHRDEV	          = 3; /* Character Device */
const UINT8 EXT2_FT_BLKDEV	          = 4; /* Block Device */
const UINT8 EXT2_FT_FIFO	          = 5; /* Buffer File */
const UINT8 EXT2_FT_SOCK	          = 6; /* Socket File */
const UINT8 EXT2_FT_SYMLINK           = 7; /* Symbolic Link */