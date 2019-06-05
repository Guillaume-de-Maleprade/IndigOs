#ifndef DIRECTORYENTRY_H
#define DIRECTORYENTRY_H

#include "types.h"

// Constants used
#define EXT2_NAME_LEN 255
#define EXT2_FT_UNKNOWN   0  //  Unknown File Type
#define EXT2_FT_REG_FILE  1  //  Regular File
#define EXT2_FT_DIR       2  //  Directory File
#define EXT2_FT_CHRDEV    3  //  Character Device
#define EXT2_FT_BLKDEV    4  //  Block Device
#define EXT2_FT_FIFO      5  //  Buffer File
#define EXT2_FT_SOCK      6  //  Socket File
#define EXT2_FT_SYMLINK   7  //  Symbolic Link

struct direntry {
  // inode number of the file referred to by this directory entry. if it's 0 value = invalid.
  UINT32 inode;

  // Directory entry length
  UINT16 rec_len;

  // indicating how many bytes of character data are in the name.
  UINT8 name_len;

  //  file's type. See constants
  UINT8 file_type;

  // file's name
  UINT8 file_name[EXT2_NAME_LEN];
};

#endif // DIRECTORYENTRY_H
