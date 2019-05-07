#include "type.h"

typedef struct
{
    UINT16   i_mode;         /* File mode */
    UINT16   i_uid;          /* Owner Uid */
    UINT32   i_size;         /* Size in bytes */
    UINT32   i_atime;        /* Access time */
    UINT32   i_ctime;        /* Creation time */
    UINT32   i_mtime;        /* Modification time */
    UINT32   i_dtime;        /* Deletion Time */
    UINT16   i_gid;          /* Group Id */
    UINT16   i_links_count;  /* Links count */
    UINT32   i_blocks;       /* Blocks count */
    UINT32   i_flags;        /* File flags */

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
    } osd1;                         /* OS dependent 1 */

    UINT32   i_block[15];	 /* Pointers to blocks */
    UINT32   i_version;      /* File version (for NFS) */
    UINT32   i_file_acl;     /* File ACL */
    UINT32   i_dir_acl;      /* Directory ACL */
    UINT32   i_faddr;        /* Fragment address */

    union {
            struct {
                    UINT8    l_i_frag;       /* Fragment number */
                    UINT8    l_i_fsize;      /* Fragment size */
                    UINT16   i_pad1;
                    UINT32   l_i_reserved2[2];
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
    } osd2;                         /* OS dependent 2 */

} Inode;