#include "PredictiveText.h"

struct Node{
    char* value; //letter value of node
    int IsWord; // is this node a leaf
    int level;  // level of node in trie for use in prioritisation
    int use;    // number of times word has been chosen before for use in prioritisation
    int childs; // number of children node has for prioritisation
    //char IfCapital[23]; // if word terminating at this leaf contains capital letters then hold capitalised word here
    struct Node* Children[128]; // number of potential children to be optimised by using only 38 characters in use in input file
};

struct Node* NodeConstructor(){

    struct Node *pn = NULL;
    pn = (struct Node *)malloc(sizeof(struct Node));

    if (pn) // check memory was allocated
    {
        pn->value = '\0'; // initialise values in node
        pn->IsWord = 0;
        pn->level = 0;
        pn->use = 0;
        pn->childs = 0;
       // pn->IfCapital = "";

         int i;
     for(i = 0; i < 127; i++) // initialise children links in node
        {
            pn->Children[i] = NULL;
        }

            }
    return pn;

};

void insert (struct Node* pn, char* word ) // function to insert item into trie
{

    struct Node *crawl = pn; // start crawl at the top

    if(word){               //check word you are inserting exists
       int index=0, i=0;

    if (crawl){ //if at an existng node
        while (word[i] != '\0') // check not at the end of word
            {
             index =  (int)(word[i]);//- 48;

                if (!crawl->Children[index]){ // if child for this letter doesn't exist create it
                    crawl->Children[index]= NodeConstructor();
                    crawl->Children[index]->value = word[i];
                    crawl->childs++;
                }

            crawl =crawl->Children[index]; // move down to the child node for that letter
            i++; // increment letter
                      }
        crawl->IsWord = 1; // make the IsWord variable indicate this is a leaf

       }

    }

}

/* Deallocates memory previously allocated for the Trie */
void nodeFree(struct Node* pn) {

    if(pn){
        int i = 0;
        for(i = 0; i <=126; i ++)
        {
            nodeFree(pn->Children[i]);
        }
        free(pn);

    }

}


int Nodesuggest(struct Node* crawl, char* prefix, int flag) // function for suggesting words

{

// First move down the trie as far as the prefix already typed
    if(prefix){
       int index=0, i=0;
              if (crawl){

        while (prefix[i] != '\0'){
             index =  (int)(prefix[i]);//- 48;
             if (!crawl->Children[index]) //if child nodes for next letter do not exist then say no words
                {
                    printf(" no words exist");
                    return 0;
             }
            crawl =crawl->Children[index];
            i++;
        }

        static int suff1sc = 0; // for use in prioritisation of words
        int suff2sc = 0;// for use in prioritisation of words
        int suff3sc = 0;// for use in prioritisation of words
        int suff4sc = 0;// for use in prioritisation of words
        int suff5sc = 0;// for use in prioritisation of words


        char suffix[22]; //rolling suffix
        char suffix1[22];// fixed suffixes for checking against
        char suffix2[22];
        char suffix3[22];
        char suffix4[22];
        char suffix5[22];
        suffix1[0] ="";
        suffix2[0] ="";
        suffix3[0] ="";
        suffix4[0] ="";
        suffix5[0] ="";
        suggest(crawl,suffix, suffix1, suffix2,suffix3,suffix4,suffix5,0); //function to recursively find potential words
        printf("\n");
        choose(prefix,suffix1, suffix2,suffix3,suffix4,suffix5);

       }
    }
 }
void suggest(struct Node *crawl,char *suffix, char *suffix1, char *suffix2,char *suffix3,char *suffix4,char *suffix5, int k)
// function to recursively find words .. HT http://stackoverflow.com/questions/17843628/algorithm-to-print-trie-alphabetically

{
int i;
if (crawl == NULL)
        return;

suffix[k + 1] = '\0';

if(crawl->IsWord == 1){
// if at a leaf put rolling suffix into fixed suffixes - next steps to organise for prioritisation
    strcpy(suffix5,suffix4); //copy string from suffix 4 to suffix 5
    strcpy(suffix4,suffix3); //copy string from suffix 3 to suffix 4
    strcpy(suffix3,suffix2); //copy string from suffix 2 to suffix 3
    strcpy(suffix2,suffix1); //copy string from suffix 1 to suffix 2
    strcpy(suffix1,suffix); //copy string from rolling suffix to suffix 1
    }


for (i = 0; i < 127; i++) //for each node, starting at 0 and going to 125
{
    suffix[k] = crawl->value; //set suffix[k] equal to the value of the crawl
    suggest(crawl->Children[i], suffix, suffix1, suffix2,suffix3,suffix4,suffix5, k + 1); //recursively searching
}

suffix[k] = '\0'; //set suffix[k] equal NULL
}


void choose (char *prefix, char *suffix1,char *suffix2,char *suffix3,char *suffix4,char *suffix5)
{ //print and allow choice of top 5 suggestions
    printf("%s",suffix1);
    //strip leading letter of suffix;
    int i;
    for(i=0;i<(strlen(suffix1));i++)
        suffix1[i]=suffix1[i+1];
    for(i=0;i<strlen(suffix2);i++)
        suffix2[i]=suffix2[i+1];
    for(i=0;i<strlen(suffix3);i++)
        suffix3[i]=suffix3[i+1];
    for(i=0;i<strlen(suffix4);i++)
        suffix4[i]=suffix4[i+1];
    for(i=0;i<strlen(suffix5);i++)
        suffix5[i]=suffix5[i+1];
        //concatenate into words;
char word1 [22];
char word2 [22];
char word3 [22];
char word4 [22];
char word5 [22];

word1[0]='\0';
word2[0]='\0';
word3[0]='\0';
word4[0]='\0';
word5[0]='\0';
//adding prefixes to the words
strcat(word1,prefix);
strcat(word2,prefix);
strcat(word3,prefix);
strcat(word4,prefix);
strcat(word5,prefix);
//adding suffixes to the words
strcat(word1,suffix1);
strcat(word2,suffix2);
strcat(word3,suffix3);
strcat(word4,suffix4);
strcat(word5,suffix5);

    printf(" Below are some suggestions for words please: type a number for your choice of ? to continue typing");
    printf("\n 1 %s",word1);
    printf("\n 2 %s",word2);
    printf("\n 3 %s",word3);
    printf("\n 4 %s",word4);
    printf("\n 5 %s",word5);

int letter;
//getting the users choice of word
while ((letter = getch()) != EOF && letter!= '?'){
        if(letter == '1')
            printf("\n%s is the word you chose\n",word1);
        else if(letter == '2')
            printf("\n%s is the word you chose\n",word2);
        else if(letter == '3')
            printf("\n%s is the word you chose\n",word3);
        else if(letter == '4')
            printf("\n%s is the word you chose\n",word4);
        else if(letter == '5')
            printf("\n%s is the word you chose\n",word5);
        else
            printf("\nThis is an invalid choice\n");

}
printf(" Please type more letters then \n %s",prefix); //If they want to continue typing remind user of prefix
}
