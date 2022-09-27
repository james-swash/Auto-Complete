// Y3624587
#include "PredictiveText.h"

#define MAX_WORDS 25

int main(void) {

  printf("\t\tPredictive Text Application\n");

  struct Node * trie = NodeConstructor();

  FILE * ptr_file;
  char buf[25];

  ptr_file = fopen("words.txt", "r");
  if (!ptr_file)
    return 1;

  while (fgets(buf, 25, ptr_file) != NULL) {
    int i;
    for (i = 0; buf[i]; i++) {
      buf[i] = tolower(buf[i]);
    }
    //       	printf("%s %d",buf, i);
    insert(trie, buf);
  }
  fclose(ptr_file);
  printf("file loaded");

  int letter;

  puts("Press any key, ':' to show suggestions and '@' quit");

  char searchWord[30] = "";
  int i = 0;

  while ((letter = getch()) != EOF && letter != '@' && i < 29) {
    if (letter != ':') {
      searchWord[i] = (char) letter;
      searchWord[i] = tolower(searchWord[i]);
      printf("%c", letter);
      i++;
    } else {
      searchWord[i] = '\0';
      Nodesuggest(trie, searchWord, 0);

    }

  }

  nodeFree(trie);

  return 0;

}