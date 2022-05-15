#ifndef DIR_UTILS_H
#define DIR_UTILS_H

#include "data_types.h"
#include "file_utils.h"

Dir* create_new_dir(Dir* parent, char* name);
Dir* remove_dir(Dir* dir);
Dir* find_last_dir(Dir* dir, char* name);
Dir* find_dir(Dir* dir, char* name);
Dir* find_used_dir_name(Dir* dir, char* name);

#endif //DIR_UTILS_H