#ifndef BLOCKGROUP_DESCRIPTOR_TABLE_H
#define BLOCKGROUP_DESCRIPTOR_TABLE_H

#include "types.h"

// block group descriptor = array of block group descriptors.

struct blockgroup_descriptor {
  // ID of the first block of the "block bitmap"
  UINT32 bg_block_bitmap;

  // ID of the first block of the "inode bitmap"
  UINT32 bg_inode_bitmap;

  // ID of the first block of the "inode table"
  UINT32 bg_inode_table;

  // total number of free blocks
  UINT16 bg_free_blocks_count;

  // total number of free inodes
  UINT16 bg_free_inodes_count;

  // number of inodes allcated
  UINT16 bg_used_dirs_count;

  // pad value 
  UINT16 bg_pad;

  // 12 bytes of space reserved
  UINT8 bg_reserved[12];
};

#endif // BLOCKGROUP_DESCRIPTOR_TABLE_H
