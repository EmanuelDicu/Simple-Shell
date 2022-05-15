#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_utils.h"
#include "dir_utils.h"
#include "commands.h"

#define MAX_INPUT_LINE_SIZE 300

int main(void) {
	char* input_line = (char*) malloc(MAX_INPUT_LINE_SIZE);
	char* delim = (char*) malloc(2);
	char* command;
	Dir* root = create_new_dir(NULL, "home");
	Dir* current_dir = root;
	delim[0] = ' '; delim[1] = 0;
	do {
		fgets(input_line, MAX_INPUT_LINE_SIZE, stdin);
		input_line[strlen(input_line) - 1] = 0;
		command = strtok(input_line, delim);
		if (strcmp(command, "touch") == 0) {
			char* name = strtok(NULL, delim);
			touch(current_dir, name);
		} else
		if (strcmp(command, "mkdir") == 0) {
			char* name = strtok(NULL, delim);
			mkdir(current_dir, name);
		} else
		if (strcmp(command, "ls") == 0) {
			ls(current_dir);
		} else
		if (strcmp(command, "rm") == 0) {
			char* name = strtok(NULL, delim);
			rm(current_dir, name);
		} else
		if (strcmp(command, "rmdir") == 0) {
			char* name = strtok(NULL, delim);
			rmdir(current_dir, name);
		} else
		if (strcmp(command, "cd") == 0) {
			char* name = strtok(NULL, delim);
			cd(&current_dir, name);
		} else
		if (strcmp(command, "tree") == 0) {
			tree(current_dir, get_level(current_dir));
		} else
		if (strcmp(command, "pwd") == 0) {
			char* working_dir = pwd(current_dir);
			printf("%s\n", working_dir);
			free(working_dir);
		} else
		if (strcmp(command, "stop") == 0) {
			stop(root);
			free(input_line);
			free(delim);
			break;
		} else
		if (strcmp(command, "mv") == 0) {
			char* name1 = strtok(NULL, delim);
			char* name2 = strtok(NULL, delim);
			mv(current_dir, name1, name2);
		}
	} while (1);
	return 0;
}
