#include "type.h"

typedef struct 
{
	UINT32   inode;                 /* Inode number */
	UINT16   rec_len;               /* Directory entry length */
	UINT8   name_len;				/* Name length */
	UINT8   file_type;				/* File type */
	char    name[256];				/* File name */
} DirEntry;