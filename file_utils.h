#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include "data_types.h"
#include "dir_utils.h"

File* create_new_file(Dir* parent, char* name);
File* remove_file(File* file);
File* find_last_file(File* file, char* name);
File* find_file(File* file, char* name);
File* find_used_file_name(File* file, char* name);

#endif //FILE_UTILS_H