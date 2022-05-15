#ifndef COMMANDS_H
#define COMMANDS_H

#include "file_utils.h"
#include "dir_utils.h"

void touch(Dir* parent, char* name);
void mkdir(Dir* parent, char* name);
void ls(Dir* parent);
void rm(Dir* parent, char* name);
void rmdir(Dir* parent, char* name);
void cd(Dir** target, char *name);
void tree(Dir* target, int level);
char* pwd(Dir* target);
void stop(Dir* target);
void mv(Dir* parent, char *oldname, char *newname);

int get_level(Dir* target);

#endif //COMMANDS_H