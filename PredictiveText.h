#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include <time.h>
#include <Windows.h>

struct Node;

struct Node* NodeConstructor();
void insert (struct Node* pn, char* word );
void nodeFree(struct Node* pn);
int Nodesuggest(struct Node* crawl, char* prefix, int flag);
void suggest(struct Node *crawl,char *suffix, char *suffix1, char *suffix2,char *suffix3,char *suffix4,char *suffix5, int k);
void choose (char *prefix, char *suffix1,char *suffix2,char *suffix3,char *suffix4,char *suffix5);



