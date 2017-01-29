#include <iostream>
#include <omp.h>

#ifndef N
#define N 5
#endif
#ifndef FS
#define FS 38
#endif

struct node {
   int data;
   int fibdata;
   struct node* next;
};

int fib(int n) {
   int x, y;
   if (n < 2) {
      return (n);
   } else {
      x = fib(n - 1);
      y = fib(n - 2);
	  return (x + y);
   }
}

void processwork(struct node* p)
{
   int n;
   n = p->data;
   p->fibdata = fib(n);
}

struct node* init_list(struct node* p) {
    int i;
    struct node* head = NULL;
    struct node* temp = NULL;

    //head = malloc(sizeof(struct node));
    head = new node();
    p = head;
    p->data = FS;
    p->fibdata = 0;
    for (i=0; i< N; i++) {
    //    temp  =  malloc(sizeof(struct node));
       temp  =  new node();
       p->next = temp;
       p = temp;
       p->data = FS + i + 1;
       p->fibdata = i+1;
    }
    p->next = NULL;
    return head;
}

int main(int argc, char *argv[]) {
     double start, end;
     struct node *p=NULL;
     struct node *temp=NULL;
     struct node *head=NULL;

	 std::cout << "Process linked list" << std::endl;
     std::cout << "  Each linked list node will be processed by function 'processwork()'" << std::endl;
     std::cout << "  Each ll node will compute " << N << " fibonacci numbers beginning with " << FS << std::endl;

     p = init_list(p);
     head = p;

     start = omp_get_wtime();
     {
        while (p != NULL) {
		   processwork(p);
		   p = p->next;
        }
     }

     end = omp_get_wtime();
     p = head;
	 while (p != NULL) {
        std::cout << p->data << ":" << p->fibdata << std::endl;
        temp = p->next;
        delete p;
        p = temp;
     }
	 delete p;

     std::cout << "Compute Time: " << end - start << " seconds" << std::endl;

     return 0;
}
