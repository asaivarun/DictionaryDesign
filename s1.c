#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define MAX_WORD_LENGTH 40
#define MAX_MEANING_LENGTH 50
#define MAX_LENGTH 45
#define MAX_BUCKETS 26

typedef struct dictionary
{
char word[MAX_WORD_LENGTH];
char meaning[MAX_MEANING_LENGTH];
char synonym[MAX_LENGTH];
char antonym[MAX_LENGTH];
		
struct dictionary *next;
}dic_t;
		
dic_t *hash_tbl[MAX_BUCKETS];
		

int hash_function(char *word)
{
int c;
c=(tolower(word[0])-'a')% MAX_BUCKETS;
return c;
}

void hash_tbl_init(dic_t *hash_tbl[MAX_BUCKETS])
{
int i;
for(i=0;i<MAX_BUCKETS;i++)
hash_tbl[i]=NULL;
}

int insert_hash_tbl(dic_t *hash_tbl[MAX_BUCKETS],char *word,char *meaning,char *synonym,char *antonym)
{
int index;
dic_t *d_rec;

//Generating Index

index=hash_function(word);

//Insertion Process starts
//Adding at the bigining of the linked list :O(1)

d_rec=(dic_t *)malloc(sizeof(dic_t));

/*Copying Data */

strcpy(d_rec->word,word);
strcpy(d_rec->meaning,meaning);
strcpy(d_rec->synonym,synonym);
strcpy(d_rec->antonym,antonym);

/* Setting Pointers so as to Insert at the begining */
if(hash_tbl[index]==NULL)
	{
	hash_tbl[index]=d_rec;
	return 1;
	}
	
d_rec->next=hash_tbl[index];
hash_tbl[index]=d_rec;
return 1;
}

int search_hash_tbl(dic_t *hash_tbl[MAX_BUCKETS],char word[],char meaning[],char synonym[],char antonym[] )
{
int index;	
dic_t *d_rec;

//Generating Index

index=hash_function(word);

d_rec=hash_tbl[index];

while(d_rec!=NULL)
{
	if(strcmp(d_rec->word,word)==0)
		{
		//copy data
		strcpy(word,d_rec->word);
		strcpy(meaning,d_rec->meaning);
		strcpy(synonym,d_rec->synonym);
		strcpy(antonym,d_rec->antonym);
		return 1;
		//Success Found It
		}
		
		//Moving To Next Node
	d_rec= d_rec->next;
}

return 0;
//Failture. Word searched was not found

}

int delete_hash_tbl(dic_t *hash_tbl[MAX_BUCKETS], char word[])
{
   int index;
   dic_t *d_rec, *d_prev; // p_rec : the node to be deleted. p_prev : previous node

   /* Generate Index */
   index = hash_function(word);

   d_rec = hash_tbl[index];
   d_prev = NULL;

   while (d_rec != NULL)
   {
      if (strcmp(d_rec->word, word) == 0)
      {
        // Found it.
        if (d_prev != NULL)
          d_prev->next = d_rec->next;
        else
           hash_tbl[index] = d_rec->next;
        free(d_rec);
        return 1; // SUCCESS. found it. Deleted it.
      }

      /* Keep Looking. Move pointers. */
      d_prev = d_rec;
      d_rec = d_rec->next;
  }

   return 0; // FAILURE. did not find it
}

/* Function : To print the hash table */


void print_hash_tbl(dic_t *hash_tbl[MAX_BUCKETS])
{
   int i;
   char c;
   c=97;
   dic_t *d_rec;
   printf("The elements in hash table are:\n");
   for(i=0;i<MAX_BUCKETS;i++,c++)
   {
     d_rec = hash_tbl[i];
     printf("Words Starting with %c are:\n",c );
     while (d_rec != NULL)
     {
     printf("Word=%s",d_rec->word);
     printf("\n");
     printf("Meaning of the %s = %s",d_rec->word,d_rec->meaning); 
     printf("\n");
     printf("Synonym of %s = %s",d_rec->word,d_rec->synonym);
     printf("\n");
     printf("Antonym of the %s = %s",d_rec->word,d_rec->antonym);   
     printf("\n");
     d_rec = d_rec->next;
     }
   }
}




		
void print_by_char(dic_t *hash_tbl[MAX_BUCKETS],char *word)
{
int index;
char c;
index=hash_function(word);
dic_t *d_rec;
d_rec=hash_tbl[index];
c=word[0];
printf("Words Starting with %c Alphabet are :",c);
while (d_rec != NULL)
     {
     printf("\n");
     printf("Word=%s",d_rec->word);
     printf("\n");
     printf("Meaning of the Word=%s",d_rec->meaning); 
     printf("\n");
     printf("Synonym of Word=%s",d_rec->synonym);
     printf("\n");
     printf("Antonym of the Word=%s",d_rec->antonym);   
     printf("\n");
     d_rec = d_rec->next;
     }
}




int main(int argc, char *argv[])
{
int n,ch,ret;
char d[2];
char word[MAX_WORD_LENGTH];
char meaning[MAX_MEANING_LENGTH];
char synonym[MAX_LENGTH];
char antonym[MAX_LENGTH];

//intialising hash table

hash_tbl_init(hash_tbl);

FILE *fp;
   int retu; // return status

   if (argc != 2)
   {
       fprintf(stderr, "Usage : %s <filename>\n", argv[0]);
       exit(1);
   }

   /* Opening file here */
   fp = fopen(argv[1], "r");
   if (fp == NULL)
   {
      
      perror("fopen");
      exit(1);
   }

   
   while (!feof(fp))
   {
      retu = fscanf(fp, "%s%s%s%s",word,meaning,synonym,antonym);
      insert_hash_tbl(hash_tbl, word, meaning,synonym,antonym);
      	 
   }
	delete_hash_tbl(hash_tbl, word);
   /* Closing file */
   fclose(fp);


printf("Instructions");
printf("\n");
printf("1)While entering any kind of string instaed of using spacebar use '_',For Eg. Yellow_colour");
printf("\n");
printf("2)While Enter multiple strings do not Use spacebars b/w ',' only use ','For Eg.Hello,Hello.");


while(1)
{   
    printf("\n");
    printf("\n");
    printf("Welcome To Dictionary 1.1");
    printf("\n");	
    printf("\n");
    printf(" 1)Print Whole Dictionary\n");
    printf(" 2)Insert Word\n");
    printf(" 3)Search Word\n");
    printf(" 4)Delete Word\n");
    printf(" 5)Print words starting from a given Alphabet\n");
    printf(" 0)Exit\n");
    printf(" What do you want to do?");
   
    scanf("%d", &ch);
    switch(ch)
    {
       case 1: /* Print Hash Table */
         print_hash_tbl(hash_tbl);
         break;

       case 2: /* Insert */
         printf("Enter the Word,its Meaning,its Synonym,its Antonym\n");
         scanf("%s",word);
         scanf("%s",meaning);
         scanf("%s",synonym);
         scanf("%s",antonym);
  
               
         ret = insert_hash_tbl(hash_tbl, word, meaning,synonym,antonym);

         if (ret == 1)
           printf("Inserting Into Dictionary succeeded\n");
         else
           printf("Inserting Into Dictionary failed\n");
         break;

       case 3: /* Search */
         printf("Enter The word You want to search?\n");
         scanf("%s", word);

         ret = search_hash_tbl(hash_tbl, word,meaning,synonym,antonym);
         if (ret == 1){
           printf("Search in Dictionary succeeded\n");
           printf("Word:%s,\nMeaning:%s,\nSynonym:%s,\nAntonym:%s",word,meaning,synonym,antonym);       
           }
           else
           {
           printf("search_hash_tbl failed\n");
           printf("For Printing all the words starting with the first alphbet: Press 1\n");
           printf("For searching The Word On ONLINE DICTIONARY: Press 2\n");
           printf("For exiting Search: Press 0");
           scanf("%d",&n);
           if(n==1)
           print_by_char(hash_tbl,word);
           if(n==2)
           printf("http://dictionary.reference.com/");
           if(n==0)
           break;
           }
           break;

        case 4: /* Delete */
         printf("Which word do you want to delete?\n");
         scanf("%s", word);

         ret = delete_hash_tbl(hash_tbl, word);
         if (ret == 1)
           printf("delete_hash_tbl succeeded\n");
         else
           printf("delete_hash_tbl failed\n");
         break;
	case 5:/* Printing Words Starting From the Same Alphabet */
	 printf("Enter The Alphabet for printing the words starting from it");
	 printf("\n");
	 scanf("%s",d);
	 print_by_char(hash_tbl,d);
	 break; 
       case 0: /* Exit */
         exit(0);

    }
  }
}
