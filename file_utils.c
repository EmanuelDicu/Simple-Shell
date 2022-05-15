#include <stdlib.h>
#include <string.h>

#include "file_utils.h"

/**
 * Create a file object
 * 
 * @param	parent 		directory where the file should be created
 * @param name			name of the file
 * 
 * @return					pointer to the newly created file
 */ 
File* create_new_file(Dir* parent, char* name) {
	File* file = (File*) malloc(sizeof(File));
	file->name = (char*) malloc(strlen(name) + 1);
	strcpy(file->name, name);
	file->parent = parent;
	file->next = NULL;
	return file;
}

/**
 * Removes a file object
 * 
 * @param file			file object that will be removed
 * @return					pointer to the next file in the list of files of current directory
 */ 
File* remove_file(File* file) {
	File* next_file = file->next;
	free(file->name);
	free(file);
	return next_file;
}

/**
 * Find the last file in a list or NULL if another file with a specified name already exists
 * 
 * @param file			starting file in the list
 * @param name			name of a file that if it exists, the function returns NULL
 * @return					pointer to the last file in the list, or NULL if another specific file is found
 */
File* find_last_file(File* file, char* name) {
	do {
		if (strcmp(file->name, name) == 0)
			return NULL;
		if (file->next == NULL)
			break;
		file = file->next;
	} while(1);
	return file;
}

/**
 * Finds a file in a list
 * 
 * @param	file		starting file in the list
 * @param	name		name of the file to be searched
 * @return				pointer to the file if it already exists, 
 * 									NULL otherwise
 */ 
File* find_file(File* file, char* name) {
	while (file->next != NULL) {
		if (strcmp(file->next->name, name) == 0)
			return file;
		file = file->next;
	} 
	return NULL;
}

/**
 * Find if a name of a file was already used
 * 
 * @param file		starting file in the list
 * @param	name		name of the file to be searched
 * @return				pointer to the file before the searched one if it already exists, 
 * 									NULL otherwise
 */ 
File* find_used_file_name(File* file, char* name) {
	while (file != NULL) {
		if (strcmp(file->name, name) == 0)
			return file;
		file = file->next;
	}
	return NULL;
}