#include <stdlib.h>
#include <string.h>

#include "dir_utils.h"

/**
 * Create a directory object
 * 
 * @param	parent 		directory where the subdirectory should be created
 * @param name			name of the subdirectory
 * 
 * @return					pointer to the newly created subdirectory
 */ 
Dir* create_new_dir(Dir* parent, char* name) {
	Dir* dir = (Dir*) malloc(sizeof(Dir));
	dir->name = (char*) malloc(strlen(name) + 1);
	strcpy(dir->name, name);
	dir->parent = parent;
	dir->head_children_files = NULL;
	dir->head_children_dirs = NULL;
	dir->next = NULL;
	return dir;
}

/**
 * Removes a directory object
 * 
 * @param file			directory object that will be removed
 * @return					pointer to the next directory in the list of directories of current directory
 */ 
Dir* remove_dir(Dir* dir) {
	while (dir->head_children_files != NULL)
		dir->head_children_files = remove_file(dir->head_children_files);
	while (dir->head_children_dirs) 
		dir->head_children_dirs = remove_dir(dir->head_children_dirs);
	Dir* next_dir = dir->next;
	free(dir->name);
	free(dir);
	return next_dir;
}

/**
 * Find the last directory in a list or NULL if another directory with a specified name already exists
 * 
 * @param file			starting directory in the list
 * @param name			name of a directory that if it exists, the function returns NULL
 * @return					pointer to the last directory in the list, or NULL if another specific directory is found
 */
Dir* find_last_dir(Dir* dir, char* name) {
	do {
		if (strcmp(dir->name, name) == 0) 
			return NULL;
		if (dir->next == NULL)
			break;
		dir = dir->next;
	} while(1);
	return dir;
}

/**
 * Finds a directory in a list
 * 
 * @param	file		starting directory in the list
 * @param	name		name of the directory to be searched
 * @return				pointer to the directory if it already exists, 
 * 									NULL otherwise
 */ 
Dir* find_dir(Dir* dir, char* name) {
	while (dir->next != NULL) {
		if (strcmp(dir->next->name, name) == 0) 
			return dir;
		dir = dir->next;
	} 
	return NULL;
}

/**
 * Find if a name of a directory was already used
 * 
 * @param file		starting directory in the list
 * @param	name		name of the directory to be searched
 * @return				pointer to the directory before the searched one if it already exists, 
 * 									NULL otherwise
 */ 
Dir* find_used_dir_name(Dir* dir, char* name) {
	while (dir != NULL) {
		if (strcmp(dir->name, name) == 0)
			return dir;
		dir = dir->next;
	}
	return NULL;
}