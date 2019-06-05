#ifndef SUPERBLOCK_H
#define SUPERBLOCK_H

#include "types.h"

// constants used in some of the superblock fields.

#define EXT2_SUPER_MAGIC 0xEF53
#define EXT2_VALID_FS 1
#define EXT2_ERROR_FS 2
#define EXT2_ERRORS_CONTINUE 1
#define EXT2_ERRORS_RO 2
#define EXT2_ERRORS_PANIC 3
#define EXT2_OS_LINUX 0
#define EXT2_OS_HURD 1
#define EXT2_OS_MASIC 2
#define EXT2_OS_FREEBSD 3
#define EXT2_OS_LITES 4
#define EXT2_GOOD_OLD_REV 0
#define EXT2_DYNAMIC_REV 1
#define EXT2_DEF_RESUID 0
#define EXT2_DEF_RESGID 0
#define EXT2_GOOD_OLD_FIRST_INO 11
#define EXT2_GOOD_OLD_INODE_SIZE 128
#define EXT2_FEATURE_COMPAT_DIR_PREALLOC 0x0001
#define EXT2_FEATURE_COMPAT_IMAGIC_INODES 0x0002
#define EXT3_FEATURE_COMPAT_HAS_JOURNAL 0x0004
#define EXT2_FEATURE_COMPAT_EXT_ATTR 0x0008
#define EXT2_FEATURE_COMPAT_RESIZE_INO 0x0010
#define EXT2_FEATURE_COMPAT_DIR_INDEX 0x0020
#define EXT2_FEATURE_INCOMPAT_COMPRESSION 0x0001
#define EXT2_FEATURE_INCOMPAT_FILETYPE 0x0002
#define EXT3_FEATURE_INCOMPAT_RECOVER 0x0004
#define EXT3_FEATURE_INCOMPAT_JOURNAL_DEV 0x0008
#define EXT2_FEATURE_INCOMPAT_META_BG 0x0010
#define EXT2_FEATURE_RO_COMPAT_SPARSE_SUPER 0x0001
#define EXT2_FEATURE_RO_COMPAT_LARGE_FILE 0x0002
#define EXT2_FEATURE_RO_COMPAT_BTREE_DIR 0x0004
#define EXT2_LZV1_ALG 0x00000001
#define EXT2_LZRW3A_ALG 0x00000002
#define EXT2_GZIP_ALG 0x00000004
#define EXT2_BZIP2_ALG 0x00000008
#define EXT2_LZO_ALG 0x00000010

struct superblock {
  // total # of inodes, used and free, in system
  UINT32 s_inodes_count;

  // total # of blocks, used and free, in system
  UINT32 s_blocks_count;

  // total # of blocks reserved for superuser
  UINT32 s_r_blocks_count;

  // total # of free blocks, including s_r_blocks_count reserved blocks
  UINT32 s_free_blocks_count;

  // total # of free inodes
  UINT32 s_free_inodes_count;

  // First data block location 
  UINT32 s_first_data_block;

  // log_2(blocksize/1024).
  UINT32 s_log_block_size;

  // shift of log_2(fragmentsize/1024).
  INT32 s_log_frag_size;

  // number of blocks per group.
  UINT32 s_blocks_per_group;

  // number of fragments per group.
  UINT32 s_frags_per_group;

  // number of inodes per group.
  UINT32 s_inodes_per_group;

  // the last time the filesystem was mounted, in "UNIX time"
  UINT32 s_mtime;

  // the last time the file system was written to, in "UNIX time"
  UINT32 s_wtime;

  // Mount count
  UINT16 s_mnt_count;

  // maximal mount count
  UINT16 s_max_mnt_count;

  // the "magic number" identifying the file system as type Ext2.
  // see EXT2_SUPER_MAGIC constant
  UINT16 s_magic;

  // the file system state (cleanly/uncleanly)
  UINT16 s_state;

  // what the file system driver should do when an error is detected.
  // EXT2_ERRORS_CONTINUE 	= 1	= continue as if nothing happened
  // EXT2_ERRORS_RO		      = 2	= remount read-only
  // EXT2_ERRORS_PANIC		  = 3	= cause a kernel panic
  UINT16 s_errors;

  // ext2 file system version information
  UINT16 s_minor_rev_level;

  // the last time a consistency check was run on the filesystem (Unix time)
  UINT32 s_lastcheck;

  // the maximum time (in seconds) allowed between filesystem checks
  UINT32 s_checkinterval;

  // the identifier of the operating system that created this FS. (Linux, Hurd...)
  UINT32 s_creator_os;

  // ext2 file system version information (EXT2_GOOD_OLD_REV or EXT2_DYNAMIC_REV)
  UINT32 s_rev_level;

  // the default userID for reserved blocks. EXT2_DEF_RESUID constant (0=root)
  UINT16 s_def_resuid;

  // the default group ID for reserved blocks. EXT2_DEF_RESGID constant (0=root)
  UINT16 s_def_resgid;

  // the first, non-reserved inode usable for standard files. EXT2_GOOD_OLD_FIRST_INO constant = 11
  UINT32 s_first_ino;

  // the size of an inode.  EXT2_GOOD_OLD_INODE_SIZE contant = 128 bits
  UINT16 s_inode_size;

};

#endif // SUPERBLOCK_H
