#ifndef INODE_H
#define INODE_H

#include "types.h"


// constants use for inodes

#define EXT2_BAD_INO          1  // Bad blocks inode
#define EXT2_ROOT_INO         2  // Root directory inode
#define EXT2_ACL_IDX_INO      3  // ACL index inode (deprecated)
#define EXT2_ACL_DATA_INO     4  // ACL data inode (deprecated)
#define EXT2_BOOT_LOADER_INO  5  // boot loader inode
#define EXT2_UNDEL_DIR_INO    6  // undelete directory inode

// constants for the inode structure itself.

// file format
#define EXT2_S_IFSOCK 0xC000 // socket
#define EXT2_S_IFLNK  0xA000 // symbolic link
#define EXT2_S_IFREG  0x8000 // regular file
#define EXT2_S_IFBLK  0x6000 // block device
#define EXT2_S_IFDIR  0x4000 // directory
#define EXT2_S_IFCHR  0x2000 // charater device
#define EXT2_S_IFIFO  0x1000 // fifo

 // process execution user/group override
#define EXT2_S_ISUID  0x0800 // Set process User ID
#define EXT2_S_ISGID  0x0400 // Set procces Group ID
#define EXT2_S_ISVTX  0x0200 // sticky bit

// access rights
#define EXT2_S_IRUSR  0x0100 // user read
#define EXT2_S_IWUSR  0x0080 // user write
#define EXT2_S_IXUSR  0x0040 // user execution
#define EXT2_S_IRGRP  0x0020 // group read
#define EXT2_S_IWGRP  0x0010 // group write
#define EXT2_S_IXGRP  0x0008 // group execution
#define EXT2_S_IROTH  0x0004 // others read
#define EXT2_S_IWOTH  0x0002 // others write
#define EXT2_S_IXOTH  0x0001 // others execution

struct inode {
  // format of the file and access rights.  
  UINT16 i_mode;

  // user id associated file.
  UINT16 i_uid;

  // indicate the size of the file in bytes
  UINT32 i_size;

  // the unix time of the last time this inode was accessed.
  UINT32 i_atime;

  // the unix time of when this inode was created.
  UINT32 i_ctime;

  // the unix time  of the last time this inode was modified.
  UINT32 i_mtime;

  // the unix time of when this inode was deleted.
  UINT32 i_dtime;

  // group id having access to this file.
  UINT16 i_gid;

  // how many times this inode is linked
  // if = 0, the inode and all of its associated blocks are deleted.
  UINT16 i_links_count;

  // total of blocks reserved to contain data of this inode
  // The block numbers of these are contained in the i_block array.
  UINT16 i_blocks;

  // indicating flags controlling how the filesystem should access the data of this node.
  UINT32 i_flags;

  // os-dependent.
  union {
    struct {
      UINT32  l_i_reserved1;
    } linux1;
    struct {
      UINT32  h_i_translator;
    } hurd1;
    struct {
      UINT32  m_i_reserved1;
    } masix1;
  } i_osdi1;

  // The first 12 entries in the array contain the block numbers of data blocks(i.e., are "direct" entries). 
  // The 13th entry (i_block[12]) contains the block number of the first indirect block, which itself contains (blocksize / 4) block numbers of data blocks.
  // The 14th entry (i_block[13]) contains the block number of  the first doubly-indirect block.  
  // The 15th entry (i_block[14]) is the block number of the first trebly-indirect block.
  UINT32 i_block[15];

  // indicate the file version (NFS).
  UINT32 i_generation;

  // indicating the block number containing extended attributes.
  UINT32 i_file_acl;

  // 32-bit value.  With revision 0 of ext2, this is always 0.
  // With revision 1, it contains the high 32 bits of the 64bit file size.  
  UINT32 i_dir_acl;

  // indicating the location of the file fragment.
  // NOTE : in linux, fragments are unsupported, so this value is always 0.
  UINT32 i_faddr;

  // os-dependant structures.
  union {
    struct {
      UINT8    l_i_frag;       /* Fragment number */
      UINT8    l_i_fsize;      /* Fragment size */
      UINT16   i_pad1;
      UINT16   l_i_uid_high;   /* these 2 fields    */
      UINT16   l_i_gid_high;   /* were reserved2[0] */
      UINT32   l_i_reserved2;
    } linux2;
    struct {
      UINT8    h_i_frag;       /* Fragment number */
      UINT8    h_i_fsize;      /* Fragment size */
      UINT16   h_i_mode_high;
      UINT16   h_i_uid_high;
      UINT16   h_i_gid_high;
      UINT32   h_i_author;
    } hurd2;
    struct {
      UINT8    m_i_frag;       /* Fragment number */
      UINT8    m_i_fsize;      /* Fragment size */
      UINT16   m_pad1;
      UINT32   m_i_reserved2[2];
    } masix2;
  } i_osd2;
};

#endif // INODE_H
