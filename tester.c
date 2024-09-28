/* initial test driver for strmap implementation */
//FINISH IMPLEMENTING THE OTHER 3 FUNCTIONS[x]
//COMMENT OUT THE FUNCTIONS[x]
//WRITE BETTER TESTS[]
#include <stdio.h>
#include "strmap.h"


char *key1 = "string1";
char *key2 = "gobbledygook";
char *key3 = "string2";
char *key4 = "mystring";
char *key5 = "X";
char *key6 = "XX";
char *key7 = "Y";
char *key8 = "abcdefghijklm";
char *key9 = "abcdefghijkl";

strmap_t *m;

void doput(char *k,void *v) {
  void *rv = strmap_put(m,k,v);
  printf("put(%s,%d) returned %p.\n",k,(int)v,rv);
}

int main() {
  m = strmap_create(1);
  doput(key1,(void *)1);
  doput(key2,(void *)2);
  doput(key3,(void *)3);
  doput(key4,(void *)4);
  doput(key5,(void *)5);
  doput(key6,(void *)6);
  doput(key7,(void *)7);
  doput(key8,(void *)8);
  doput(key9,(void *)9);
  doput(key7,(void *)700);
  doput(key1,(void *)100);
  strmap_put(m,"duhmer", (void *) 69);
  strmap_put(m,"duhmer", (void *) 420);
  strmap_put(m,"forever21", (void *) 21);
  strmap_put(m,"xxxtentacion", (void *) 888);
  strmap_put(m,"jennifer", (void *) 30);
  strmap_put(m,"shrek", (void *) 111111);
    printf("---------------\n");
    strmap_dump(m);
  printf("Number of elements in the map: %d\n",strmap_getsize(m));
    printf("----------------\n");
  strmap_remove(m,"jennifer");
  strmap_dump(m);
  strmap_remove(m,"shrek");
  strmap_dump(m);
  strmap_remove(m,"shrek");
  strmap_dump(m);
  printf("Value of shrek: %d\n", (int)strmap_get(m,"shrek"));
  printf("Number of elements in the map: %d\n",strmap_getsize(m));

  printf("Number of buckets in the map: %d\n", strmap_getnbuckets(m));

   return 0;
}
    
