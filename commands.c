#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commands.h"

/**
 * Create a file
 * 
 * @param parent	directory where the file is created
 * @param name		name of the newly created file
 */
void touch(Dir* parent, char* name) {
	if (parent->head_children_files == NULL) {
		parent->head_children_files = create_new_file(parent, name);
	} else {
		File* last_file = find_last_file(parent->head_children_files, name);
		if (last_file == NULL) 
			printf("File already exists\n");
 		else 
			last_file->next = create_new_file(parent, name);
	}
}

/**
 * Create a directory
 * 
 * @param parent	directory where the subdirectory is created
 * @param name		name of the newly created directory
 */
void mkdir(Dir* parent, char* name) {
	if (parent->head_children_dirs == NULL) {
		parent->head_children_dirs = create_new_dir(parent, name);
	} else {
		Dir* last_dir = find_last_dir(parent->head_children_dirs, name);
		if (last_dir == NULL)
			printf("Directory already exists\n");
		else 
			last_dir->next = create_new_dir(parent, name);
	}
}

/**
 * Lists all immediate child directories and files inside a directory
 * 
 * @param parent	directory whose immediate child subdirectories and subfiles should be listed
 */ 
void ls(Dir* parent) {
	for (Dir *dir = parent->head_children_dirs; dir != NULL; dir = dir->next)
		printf("%s\n", dir->name);
	for (File *file = parent->head_children_files; file != NULL; file = file->next)
		printf("%s\n", file->name);
}

/**
 * Removes a file from a directory
 * 
 * @param parent	directory where to search for the file
 * @param name		name of the file
 */ 
void rm(Dir* parent, char* name) {
	if (parent->head_children_files == NULL)
		printf("Could not find the file\n");
	else 
	if (strcmp(parent->head_children_files->name, name) == 0) 
		parent->head_children_files = remove_file(parent->head_children_files);
	else {
		File* file = file = find_file(parent->head_children_files, name);
		if (file == NULL)
			printf("Could not find the file\n");
		else
			file->next = remove_file(file->next);
	}
}

/**
 * Recursively removes a directory and all of its content
 * 
 * @param parent		name of the directory where to search for the subdirectory
 * @param	name			name of the subdirectory which will be removed
 */ 
void rmdir(Dir* parent, char* name) {
	if (parent->head_children_dirs == NULL)
		printf("Could not find the dir\n");
	else 
	if (strcmp(parent->head_children_dirs->name, name) == 0) 
		parent->head_children_dirs = remove_dir(parent->head_children_dirs);
	else {
		Dir* dir = find_dir(parent->head_children_dirs, name);
		if (dir == NULL)
			printf("Could not find the dir\n");
		else
			dir->next = remove_dir(dir->next);
	}
}

/**
 * Changes the current working directory 
 * 
 * @param	target[out]		pointer to the working directory which has to be changed
 * @param	name					relative path change used to determine the new working directory
 */ 
void cd(Dir** target, char *name) {
	if (strcmp(name, "..") == 0) {
		if ((*target)->parent != NULL)
			*target = (*target)->parent;
	} else {
		Dir* dir = (*target)->head_children_dirs;
		while (dir != NULL) {
			if (strcmp(dir->name, name) == 0)
				break;
			dir = dir->next;
		}
		if (dir == NULL)
			printf("No directories found!\n");
		else
			*target = dir;
	}
}

/**
 * Recursively lists all of the content of a directory in a tree-like shape
 * 
 * @param target		directory to be listed
 * @param	level			number of tabs used to indend the current directory
 */ 
void tree(Dir* target, int level) {
	for (Dir *dir = target->head_children_dirs; dir != NULL; dir = dir->next) {
		for (int nr_spaces = level * 4; nr_spaces; --nr_spaces) 
			printf(" ");
		printf("%s\n", dir->name);
		tree(dir, level + 1);
	}
	for (File *file = target->head_children_files; file != NULL; file = file->next) {
		for (int nr_spaces = level * 4; nr_spaces; --nr_spaces) 
			printf(" ");
		printf("%s\n", file->name);
	}
}

/**
 * Returns the level of a directory inside directory tree
 * 
 * @param	target		name of the directory whose level should be calculated
 * @return 					level of the current directory
 */ 
int get_level(Dir* target) {
	if (target->parent == NULL)
		return 0;
	return get_level(target->parent) + 1;
}

/**
 * Prints current working directory
 * 
 * @param target		name of the directory whose path should be determined
 * @return 				  string representation of the path of current directory
 */ 
char* pwd(Dir* target) {
	char* working_dir;
	if (target->parent == NULL) { 
		working_dir = (char*) malloc(strlen(target->name) + 2);
		strcpy(working_dir, "/");
		strcat(working_dir, target->name);
	} else {
		working_dir = pwd(target->parent);
		working_dir = (char*) realloc(working_dir, strlen(working_dir) + strlen(target->name) + 2);
		strcat(working_dir, "/");
		strcat(working_dir, target->name);
	}
	return working_dir;
}

/**
 * Removes the entire directory hierarchy
 * 
 * @param target		name of the directory where the deletion process begins
 */
void stop(Dir* target) {
	remove_dir(target);
}

/**
 * Renames a directory/file and moves its position in the directory list
 * 
 * @param parent 		directory where the moved object is searched
 * @param	oldname		old name of the object
 * @param	newname		new name of the project
 */ 
void mv(Dir* parent, char *oldname, char *newname) {
	File* old_file = find_used_file_name(parent->head_children_files, oldname);
	Dir* old_dir = find_used_dir_name(parent->head_children_dirs, oldname);
	if (old_file == NULL && old_dir == NULL)
		printf("File/Director not found\n");
	else {
		File* new_file = find_used_file_name(parent->head_children_files, newname);
		Dir* new_dir = find_used_dir_name(parent->head_children_dirs, newname);
		if (new_file != NULL || new_dir != NULL)
			printf("File/Director already exists\n");
		else {
			if (old_file != NULL) { // the moved object is a file
				free(old_file->name);
				old_file->name = (char*) malloc(strlen(newname) + 1);
				strcpy(old_file->name, newname);
				File* last_file = find_last_file(parent->head_children_files, oldname); 
				if (old_file != last_file) {
					last_file->next = old_file;
					if (parent->head_children_files == old_file) {
						parent->head_children_files = old_file->next;
					} else {
						File* prev_file = find_file(parent->head_children_files, oldname);
						prev_file->next = old_file->next;
					}
					old_file->next = NULL;
				}
			} else { // the moved object is a directory
				free(old_dir->name);
				old_dir->name = (char*) malloc(strlen(newname) + 1);
				strcpy(old_dir->name, newname);
				Dir* last_dir = find_last_dir(parent->head_children_dirs, oldname); 
				if (old_dir != last_dir) {
					last_dir->next = old_dir;
					if (parent->head_children_dirs == old_dir) {
						parent->head_children_dirs = old_dir->next;
					} else {
						Dir* prev_dir = find_dir(parent->head_children_dirs, oldname);
						prev_dir->next = old_dir->next;
					}
					old_dir->next = NULL;
				}
			}
		}
	}
}

