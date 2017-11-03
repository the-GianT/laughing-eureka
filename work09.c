#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>

/**
 * only prints directories and regular files
 *
 * Precondition: The directory being scanned cannot contain more than 4096
 * bytes, unless it only contains more because of newlines or nulls or whatever
 * at the end.
 */
int main(int argc, char *argv[])
{
  // printf("%s\n", argv[1]);
  DIR * d;
  struct dirent * entry;
  char dirs[4096]; // char array to store names of the directories within the argv[1] directory
  char regfiles[4096]; //char array to store names of the regular files within the argv[1] directory
  // size_t dirsize = 0;
  struct stat sb;
  // int i;
  // char currentchar;
  char nextfilename[256]; // stores the name of the next file in the directory

  dirs[0] = 0; // so that strlen(dirs) will definitely equal 0
  regfiles[0] = 0; // so that strlen(regfiles) will definitely equal 0

  stat(argv[1], &sb); // for taking size of the directory
  
  d = opendir(argv[1]);

  entry = readdir(d);
  while (entry) {
    // nextfilename[0] = entry->d_name;
    
    // set up string to be added to dirs or regfiles
    strncpy(nextfilename, "\n\t", sizeof(nextfilename) - 1);
    nextfilename[sizeof(nextfilename) - 1] = 0;
    strncat(nextfilename, entry->d_name, sizeof(nextfilename) - strlen(nextfilename) - 1);

    // add this next file to the char array that corresponds with the type of the file
    if (entry->d_type == DT_DIR) {
      strncat(dirs, nextfilename, sizeof(dirs) - strlen(dirs) - 1);
    } else if (entry->d_type == DT_REG) {
      strncat(regfiles, nextfilename, sizeof(regfiles) - strlen(regfiles) - 1);
    }
    entry = readdir(d);
  }

  printf("Statistics for directory: %s\n", argv[1]);
  printf("Total Directory Size: %lu Bytes\n", sb.st_size);
  printf("Directories:%s\n", dirs);
  /*
  i = 0;
  while (currentchar = dirs[i]) {
    printf("%c", currentchar);
    i++;
  }
  */
  printf("Regular files:%s\n", regfiles);
  /*
  i = 0;
  while (currentchar = regfiles[i]) {
    printf("%c", currentchar);
    i++;
  }
  */

  closedir(d);

  return 0;
}
