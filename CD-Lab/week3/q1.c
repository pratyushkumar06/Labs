#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

int idc=0;           /////////identifier count

int tind=0; ////table index
int ca,cb;

char globalf[30];    ////storing name of current global function

int curlbal=0; ///chdcking for global and local 

char dtype[40];

typedef struct entry
{
   int index;
   char name[30];
   char type[10];
   int size;
   char scope;
   char rtype[10];
   int narg;
   char arg[40];
}entry;

typedef struct list *listptr;
typedef struct list
{
   entry e;
   listptr next;
}list;



char keys[32][15]={
   "auto","break","case","char",
   "const","continue","default","do",
   "double","else","enum","extern",
   "float","for","goto","if",
   "int","long","register","return",
   "short","signed","sizeof","static",
   "struct","switch","typedef","union",
   "unsigned","void","volatile","while"
};

char PreFunc[5][10]={"printf","scanf","sprintf","sqrt"};

int isKey(char buf[40])          
{
   for(int i=0;i<32;i++)
   {
      if(!strcmp(buf,keys[i]))
         return 1;
   }
   return 0;
}

int isPreFunc(char buf[40])   ///////CHECKING FOR PREDEFINED FUNCTIONS
{
   for(int i=0;i<4;i++)
   {
      if(!strcmp(buf,PreFunc[i]))
      {
         return 1;
      }
   }
   return 0;
}

entry getNextEntry(FILE *fp,char *buf,int lenght)  ///NEXT ENTRY IN TABLE
{
   entry e1;char buf1[40];int ind1=0;char buf2[10];
   strcpy(e1.name,buf);
   if(!curlbal)
   {
      e1.scope='G';
   }
   else
   {
      e1.scope='L';
   }

   if(ca=='(')
            ///FUNCTION
   {              
      e1.size=-111;
      if(e1.scope=='G')
      {
         strcpy(globalf,e1.name);
      }
      strcpy(e1.type,"FUNC");
      //e1.narg=1;
      strcpy(e1.rtype,dtype);
      ca=getc(fp);
      if(ca==')')
      {
         e1.narg=0;
         strcpy(e1.arg,"NULL");
      }
      else
      {
         e1.narg=1;
         ind1=0;
         buf1[ind1++]='<';
         while(ca!=')')
         {
            buf1[ind1++]=ca;
            ca=getc(fp);
         }
         buf1[ind1]='\0';
         idc++;
   
         strcat(buf1,">");
         strcpy(e1.arg,buf1);
      }
   }
   else
   {
      strcpy(e1.type,dtype);     //////VARIABLE
      strcpy(e1.rtype,"NULL");
      strcpy(e1.arg,"NULL");
      e1.narg=0;
      if(!strcmp(e1.type,"int"))
         e1.size=4;
      else if(!strcmp(e1.type,"float"))
         e1.size=4;
 
      else
         e1.size=-111;
      
   }
   return e1;  
}

listptr newnode(entry e1)
{
   listptr new=(listptr)malloc(sizeof(list));
   new->e=e1;
   new->next=NULL;
   return new;
}

listptr add(listptr head,entry e1)
{
   if(!head)
   {
      head=newnode(e1);
      return head;
   }
   listptr temp=head;
   listptr new=newnode(e1);
   while(temp->next!=NULL)
   {
      temp=temp->next;
   }
   temp->next=new;
   return head;
}

void display(listptr head)
{
    printf("   Name   Type    Size   Scope No of Args   Args   Ret type\n");
   listptr temp=head;
   while(temp!=NULL)
   {

      printf("%d  %s    %s    %d    %c    %d    %s    %s\n\n",temp->e.index,temp->e.name,temp->e.type,temp->e.size,temp->e.scope,temp->e.narg,temp->e.arg,temp->e.rtype);

      temp=temp->next;
   }
}

int present(listptr head,entry e1)
{
   listptr temp=head;
   if((e1.scope=='G')&&(!strcmp(e1.type,"FUNC")))
   {
      return 0;
   }
   while(strcmp(temp->e.name,globalf)&&(temp!=NULL))
   {
      temp=temp->next;
   }
   while((temp!=NULL))
   {
      if(!strcmp(e1.name,temp->e.name))
         return 1;
      temp=temp->next;
   }
   return 0;
}

int present1(listptr head,entry e1)
{
   listptr temp=head;
   while(temp!=NULL)
   {
      if(!strcmp(temp->e.name,e1.name))
         return 1;
      temp=temp->next;
   }
   return 0;

}

int main()
{
   
   FILE *fp=fopen("input.c","r");listptr head=NULL;
   if(!fp)
   {
      printf("File not found\n");
      exit(1);
   }
   ca=getc(fp);entry e1;char *buf=(char*)malloc(sizeof(char)*40);int ind=0;
   while(1)
   {
      ind=0;
      if(ca==EOF)
      {
         display(head);
         exit(0);
      }
      else if(ca=='#')
      {
         while(ca!='\n')
            ca=getc(fp);
      }
      else if(ca=='/')     //REMOVING COMMENTS
      {
         cb=getc(fp);
         if(cb=='/')
         {
            ca=getc(fp);
            while(ca!='\n')
            {
               ca=getc(fp);
            }
         }
         else if(cb=='*')
         {
            ca=getc(fp);
            cb=getc(fp);
            while((ca!='*')&&(cb!='/'))
            {
               
               ca=cb;
               cb=getc(fp);
               //colc++;
            }
            //ca=getc(fp);
         }
         else
         {
            ;
         }
      }


      else if(ca=='\"')    /////IGNORING STRINGS
      {
         ca=getc(fp);
         while(ca!='\"')
         {
      
            ca=getc(fp);
         }
         ca=getc(fp);
      }

      else if(ca=='{')
      {
         curlbal++;
         ca=getc(fp);
      }
      else if(ca=='}')
      {
         curlbal--;
         ca=getc(fp);
      }

      else if(isdigit(ca))
      {
         while(isalnum(ca))
         {
            ca=getc(fp);
         }
         ungetc(ca,fp);
      }

      else if((isalpha(ca))||ca=='_')        ////IDENTIFIERS
      {
         buf[ind++]=ca;ca=getc(fp);
         while(isalnum(ca)||ca=='_')
         {
            buf[ind++]=ca;
            ca=getc(fp);
         }  
         buf[ind]='\0';
         if(isKey(buf))
         {
            if((!strcmp(buf,"int"))||(!strcmp(buf,"char"))||(!strcmp(buf,"float")))
            {
               strcpy(dtype,buf);
            }
         }
         else
         {
            if(!isPreFunc(buf))
            {
               //idc++;
               e1=getNextEntry(fp,buf,ind);

               if(tind==0)
               {
                  e1.index=tind;
                  idc++;
                  head=add(head,e1);
                  tind++;

               }
               else
               {
                  
                  if(!strcmp(e1.type,"FUNC"))      
                  {
                     if(!present1(head,e1))
                     {
                        e1.index=tind;
                        head=add(head,e1);
                     }
                  }
                  else
                  {
                     if(!present(head,e1))
                     {
                     
                         e1.index=tind;
                        idc++;
                        head=add(head,e1);
                        tind++;
                     
                     }
                  }
                  
               }
            }
            ;
            
         }
      }
      else
         ca=getc(fp);

   }
   
   return 0;
}
