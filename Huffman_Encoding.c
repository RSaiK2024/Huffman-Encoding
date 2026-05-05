
#include<stdio.h>                                                                                                                 
#include<stdlib.h>
#include<string.h>
struct Tnode 
{ 
  char al;
  struct Tnode *l,*r;
};
struct list
{
   struct Tnode *c;
   int freq;
   struct list *next;
  };
struct Tnode *CreateTnode(char al)
{
  struct Tnode *n=malloc(sizeof(struct Tnode));
  n->al=al;
  n->l=n->r=NULL;
  return n;
  }
struct list * createnode(char c,int f)
{
 struct list *n=malloc(sizeof(struct list));
 n->freq=f;
 n->c=CreateTnode(c);
 n->next=NULL;
 return (n);
 }
struct list * Pop(struct list **h)
{
 if (*h==NULL)
   return (NULL);
  struct list *t=*h;
  *h=(*h)->next;
  return t;
  }
struct list * JoinT(struct list *a,struct list *b)
{ 
    struct list *n=createnode('\0',a->freq+b->freq);
    n->c->l=a->c;
    n->c->r=b->c;
    return(n);
    }
struct list * Insert(struct list *h,struct list *t)
{ 
  if (h==NULL|| t->freq<h->freq)
      {t->next=h;
      return(t);
  }
  struct list * n=NULL;
  n=h;
  while(n->next!=NULL&&n->next->freq<=t->freq)
      n=n->next;
  
  t->next = n->next;
  n->next = t;
  
  return h;
  }

struct Tnode * BuildTree(struct list*h)
{
  if (h==NULL)
      return (NULL);
  while (h!=NULL && h->next!=NULL)
  { 
    struct list *n = NULL,*q=NULL,*t=NULL;
    q=Pop(&h);
    n=Pop(&h);
    t=JoinT(q,n);
    h=Insert(h,t);
    free(q);
    free(n);
    }
  if (h)
    return h->c;
  else
    return NULL;
}

int find(struct Tnode *h,char c,char *s,int index ,int * found)
{ if(h==NULL||*found)
    return(0);
  if(h->al==c&&h->l==NULL&&h->r==NULL)
    {
     s[index]='\0';
     *found=1;
     return(1);
    }
  s[index]='0';
  if(find(h->l,c,s,index+1,found))
   return(1);
  s[index]='1';
  if(find(h->r,c,s,index+1,found))
   return(1);
  return(0);
}
void encode(struct Tnode* h, char * s,char* es)
{ 
    int i=0;
    for(int j=0;s[j]!=0;j++)
        { char arr[100];
         int found=0;
         if (find(h,s[j],arr,0,&found))
          {
            for (int k = 0; arr[k] != 0; k++) { 
                es[i++] = arr[k];
            }
          }else
          { printf("%c not found",s[j]);
              es[0]=0;
              return;
          }
          }
          es[i]=0;
          }
void decode(struct Tnode*h,char*es,char*ds)
{
 struct Tnode*temp=h;
 int i=0;
 for(int j=0 ; es[j]!=0; j++ )
{
 temp=(es[j]=='0') ? temp->l : temp->r;
 if(temp->l==NULL&&temp->r==NULL)
 {
  ds[i]=temp->al;
  i++;
  temp=h;
 }
}
ds[i]=0;
}
void Free(struct Tnode*h)
{
 if(h)
 {
  Free(h->l);
  Free(h->r);
  free(h);
 }
}
int main()
{
  char c;
  int freq;
  struct list *h=NULL;
  printf("enter the alphabet and their frequencies(0 to end)");
  while (1)
    {if (scanf(" %c %d",&c,&freq)  != 2)
        break;
      if (freq==0)
          break;
      struct list *n=createnode(c,freq);
      h=Insert(h,n);
      }
    struct Tnode *t=BuildTree(h);
    if (t)
    { 
      char is[100];
      printf("enter the string to encode");
      scanf("%s",is);
      char es[1000];
      encode(t,is,es);
      printf("encoded string %s\n",es);
      char ds[100];
      decode(t,es,ds);
      printf("decoded string %s\n",ds);
      Free(t);
      }
      else
          printf("Please enter proper string\n");
      return(0);
      }

