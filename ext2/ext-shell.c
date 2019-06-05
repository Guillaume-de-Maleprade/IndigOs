#include <stdio.h>
#include <assert.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include "headers/types.h"
#include "headers/superblock.h"
#include "headers/blockgroup_descriptor.h"
#include "headers/inode.h"
#include "headers/directoryentry.h"

struct superblock *superblock;
struct blockgroup_descriptor *blockgroup;
struct inode *inodes;

// read superblock 
void read_superblock(int fd) {
	superblock = malloc(sizeof(struct superblock));

	assert(superblock != NULL);
	assert(lseek(fd, (off_t)1024, SEEK_SET) == (off_t)1024);
	assert(read(fd, (void *)superblock, sizeof(struct superblock)) == sizeof(struct superblock));
}

// read blockgroup
void read_blockgroup(int fd) {
	blockgroup = malloc(sizeof(struct blockgroup_descriptor));

	assert(blockgroup != NULL);
	assert(lseek(fd, (off_t)2048, SEEK_SET) == (off_t)2048);
	assert(read(fd, (void *)blockgroup, sizeof(struct blockgroup_descriptor)) == sizeof(struct blockgroup_descriptor));
}

// read inode
void read_inodeTable(int fd) {
	inodes = (struct inode*)malloc(superblock->s_inodes_count*superblock->s_inode_size);

	assert(inodes != NULL);
	assert(lseek(fd, (off_t)(blockgroup->bg_inode_table*1024), SEEK_SET) == (off_t)(blockgroup->bg_inode_table*1024));
	assert(read(fd, (void *)inodes, 0x40000) == 0x40000);
}

// print type of file
void printInodeType(int inode_type) {
	switch(inode_type) {
	case 1:
		printf("-");
		break;
	case 2:
		printf("d");
		break;
	case 3:
		printf("c");
		break;
	case 4:
		printf("b");
		break;
	case 5:
		printf("B");
		break;
	case 6:
		printf("S");
		break;
	case 7:
		printf("l");
		break;
	default:
		printf("X");
		break;
	}
}


// print file permission
void printInodePerm(int fd, int inode_num) {
	short int mode = inodes[inode_num-1].i_mode;

	mode & EXT2_S_IRUSR ? printf("r") : printf("-");
	mode & EXT2_S_IWUSR ? printf("w") : printf("-");
	mode & EXT2_S_IXUSR ? printf("x") : printf("-");
	mode & EXT2_S_IRGRP ? printf("r") : printf("-");
	mode & EXT2_S_IWGRP ? printf("w") : printf("-");
	mode & EXT2_S_IXGRP ? printf("x") : printf("-");
	mode & EXT2_S_IROTH ? printf("r") : printf("-");
	mode & EXT2_S_IWOTH ? printf("w") : printf("-");
	mode & EXT2_S_IXOTH ? printf("x") : printf("-");

	printf("\t");
}

// find Inode by it's name
int findInodeByName(int fd, int base_inode_num, char* filename, int filetype) {
	char* name;
	int curr_inode_num;
	int curr_inode_type;


	struct direntry* dirEntry = malloc(sizeof(struct direntry));
	assert (dirEntry != NULL);
	assert(lseek(fd, (off_t)(inodes[base_inode_num-1].i_block[0]*1024), SEEK_SET) == (off_t)(inodes[base_inode_num-1].i_block[0]*1024));
	assert(read(fd, (void *)dirEntry, sizeof(struct direntry)) == sizeof(struct direntry));

	while (dirEntry->inode) {

		name = (char*)malloc(dirEntry->name_len+1);
		memcpy(name, dirEntry->file_name, dirEntry->name_len);
		name[dirEntry->name_len+1] = '\0';

		curr_inode_num = dirEntry->inode;
		curr_inode_type = dirEntry->file_type;

		if (filetype == curr_inode_type) {
			if(!strcmp(name, filename)) {
				return(curr_inode_num);
			}
		}

		lseek(fd, (dirEntry->rec_len - sizeof(struct direntry)), SEEK_CUR);
		assert(read(fd, (void *)dirEntry, sizeof(struct direntry)) == sizeof(struct direntry));

	} 

	return(-1);	
}

void ls(int fd, int base_inode_num) {
	char* name;
	int curr_inode_num;
	int curr_inode_type;

	struct direntry* dirEntry = malloc(sizeof(struct direntry));
	assert (dirEntry != NULL);
	assert(lseek(fd, (off_t)(inodes[base_inode_num-1].i_block[0]*1024), SEEK_SET) == (off_t)(inodes[base_inode_num-1].i_block[0]*1024));
	assert(read(fd, (void *)dirEntry, sizeof(struct direntry)) == sizeof(struct direntry));


         printf("%s", "permissions\tuid\tgid\tsecteurs\tinode\tnom\n");
	 while (dirEntry->inode) {
		name = (char*)malloc(dirEntry->name_len+1);
		memcpy(name, dirEntry->file_name, dirEntry->name_len);
		name[dirEntry->name_len+1] = '\0';

		curr_inode_num = dirEntry->inode;
		curr_inode_type = dirEntry->file_type;

		lseek(fd, (dirEntry->rec_len - sizeof(struct direntry)), SEEK_CUR);
		assert(read(fd, (void *)dirEntry, sizeof(struct direntry)) == sizeof(struct direntry));

		if (name[0] == '.') {
			if ( name[1]=='.' || name[1]=='\0')
				continue;
		} else {
			printInodeType(curr_inode_type);
			printInodePerm(fd, curr_inode_num);
			printf("%d\t", inodes[curr_inode_num-1].i_uid);
			printf("%d\t", inodes[curr_inode_num-1].i_gid);
			printf("%d\t", inodes[curr_inode_num-1].i_blocks);
			printf("\t");
			printf("%d\t", curr_inode_num);
			printf("%s\t", name);
			printf("\n");
		}
	} 
	return;
}

int cd(int fd, int base_inode_num) {
	char dirname[255];
	int ret;

	scanf("%s", dirname);

	ret = findInodeByName(fd, base_inode_num, dirname, EXT2_FT_DIR);

	if(ret==-1) {
		printf("Répertoire %s n'existe pas\n", dirname);
		return(base_inode_num);
	} else {
		printf("Répertoire actuel : %s\n", dirname);
		return(ret);
	}

}

int extShell(int fd) {
	char cmd[4];
	static int pwd_inode = 2;

	printf("shell$ ");
	scanf("%s", cmd);

	if(!strcmp(cmd, "quit")) {
		return(-1);

	} else if(!strcmp(cmd, "ls")) {
		ls(fd, pwd_inode);

	} else if(!strcmp(cmd, "cd")) {
		pwd_inode = cd(fd, pwd_inode);

	} else {
		printf("Commande inconnue: %s\n", cmd);
		return(-EINVAL);
	}

	return(0);
}

int main(int argc, char **argv) {
	// open  the disk file
	if (argc !=2) {
	printf("usage:  ext-shell <file.img>\n");
		return -1; 
	}

	int fd = open(argv[1], O_RDONLY|O_SYNC);
	if (fd == -1) {
		printf("Impossible d'ouvrir le fichier image' \"%s\"\n", argv[1]);
		return -1; 
	}

	// read superblock
	read_superblock(fd);
	printf("block size \t\t= %d bytes\n", 1<<(10 + superblock->s_log_block_size));
	printf("inode count \t\t= 0x%x\n", superblock->s_inodes_count);
	printf("inode size \t\t= 0x%x\n", superblock->s_inode_size);

	// read blockgroup
	read_blockgroup(fd);
	printf("inode table address \t= 0x%x\n", blockgroup->bg_inode_table);
	printf("inode table size \t= %dKB\n", (superblock->s_inodes_count*superblock->s_inode_size)>>10);

	// read inode table
	read_inodeTable(fd);

	while(1) {
		if (extShell(fd) == -1)
			break;
	}

	printf("\n\nshell quitté.\n\n");
	return(0);
}
