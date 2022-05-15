#ifndef DATA_TYPES_H
#define DATA_TYPES_H

struct File;
struct Dir;

/**
 * File struct used to store a file object
 */ 
typedef struct File {
	char *name;						/** name of the file */
	struct Dir* parent;		/** parent directory of the file */
	struct File* next;		/** next file in the list of current file */
} File;

/**
 * Directory struct used to store a directory object
 */ 
typedef struct Dir{
	char *name;													/** name of the directory */
	struct Dir* parent;									/** parent directory of the current subdirectory */
	struct File* head_children_files;		/** pointer to head of list of files inside the current directory */
	struct Dir* head_children_dirs;			/** pointer to head of list of directories inside the current directory */
	struct Dir* next;										/** next directory in the list of current directory */
} Dir;

#endif //DATA_TYPES_H