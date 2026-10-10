#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <dirent.h>

/* basic ls, just lists files in order */
int basic(char* path) {
  struct dirent *entry;
  DIR *dir = opendir("./");

  /* if dir is NULL, its because we couldn't open it */
  if (dir == NULL) {
    printf("error opening directory!\n");
    return 1;
  }

  /* until there are no entries left, print them */
  while((entry = readdir(dir)) != NULL) {
    printf("%s\n", entry->d_name);
  }

  closedir(dir);

  return 0;
}

/* advanced ls, lists files in order with size and ownership */
int advanced(char* path) {
  struct dirent *entry;
  DIR *dir = opendir("./");

  struct stat stats;

  /* if dir is NULL, its because we couldn't open it */
  if (dir == NULL) {
    printf("error opening directory!\n");
    return 1;
  }

  /* until there are no entries left, print them */
  while((entry = readdir(dir)) != NULL) {
    char filepath[1024];

    strcat(filepath, path);
    strcat(filepath, entry->d_name);

    if(stat(filepath, &stats));
  }

  closedir(dir);

  return 0;

}


int main(int argc, char** argv) {
  /* default path is current directory ./ */
  char* path = "./";

  /* list perms? 0 = n, 1 = y */
  int perms = 0;

  /* 0 is bytes, 1 is human readable */
  int type = 0;

  /* set options */
  int opt;

  while ((opt = getopt(argc, argv, "hl")) != -1) {
    printf("%c", opt);
    switch (opt) {
      case 'h':
        type = 1;
        break;
      case 'l':
        perms = 1;
        break;
    }
  }

  if (optind < argc) {
    /* if there are extra args, assume its the dir to scan */
    path = argv[optind];
  }

  if (perms == 0) {
    basic(path);
  } else {
    advanced(path);
  }

  return 0;
}
