#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

/*
 * HEAD STRUCTURE--beginig of the list--
 * first - poiter tothe first element of the list
 */ 
struct head {
  struct node *first;
};

/*
 * NODE STRUCTURE--single elemet of the list--
 * val - value of the list element
 * next - pointer to the next element of the list (default NULL)
 */
struct node {
  int val;
  struct node *next;
};

int global_counter = 0;
int global_delete = 0;
int global_mtf_finds = 0;
int global_trans_finds = 0;

/*
 * createList FUNC--func that creates list--
 */
struct head* createList() {
  struct head *h = malloc(sizeof(struct head));
  h->first = NULL;
    
  return h;
}

/*
 * insert FUNC--func that inserts an element as first element--
 * head - pointer to beginig of the list
 * val - value of inserting data
 */
void insert(struct head *head, int val) {
  if (head->first == NULL) {
	struct node *new = malloc(sizeof(struct node));
	new->val = val;
	new->next = NULL;
	head->first = new;
  } else {
	struct node *cur = head->first;

	struct node *new = malloc(sizeof(struct node));
	new->val = val;
	new->next = cur;
	head->first = new;
  }   

}

/*
 *insterE FUNC--func that inserts an element at the end of the list--
 * head - pointer to beginig of the list
 * val - value of inserting data
 */
void insertE(struct head *head, int val) {
    
  if (head->first == NULL) {
	struct node *new = malloc(sizeof(struct node));
	new->val = val;
	new->next = NULL;
	head->first = new;
  } else {
	struct node *cur = head->first;
    
	while (cur->next != NULL) {
	  cur = cur->next;
	}

	struct node *new = malloc(sizeof(struct node));
	new->val = val;
	new->next = NULL;
	cur->next = new;
  }
}

/*
 * isEmpty FUNC--func that checks if the list is empty--
 * if list is empty func returns true
 * if not func returns false
 * */  
bool isEmpty(struct head *head) {
  return head->first==NULL;
}

/*
 * findMTF FUNC--func that finds element and puts it to the first index of the list--
 * head - pointer to beginig of the list
 * s_val - searching value
 */
bool findMTF(struct head *head, int s_val) {
  if (isEmpty(head))
	return false;

  struct node *cur = head->first;
  struct node *prev;
    
  global_mtf_finds++;

  if (cur->val == s_val) // first special value if first matches 
	return true;
  
  while (cur != NULL) {
        
	global_mtf_finds++;
	
	if (cur->val == s_val) {   //if matches switch pointers
	  prev->next = cur->next;
	  cur->next = head->first;
	  head->first = cur;
            
	  return true;
	}

	prev = cur;
	cur = cur->next;
  }    

  return false;
}

/*
 * findTRANS--func that finds element and takes it one index left--
 * head - pointer to beginig of the list
 * s_val - searching value
 */
bool findTRANS(struct head *head, int s_val) {
  if (isEmpty(head))
	return false;
    
  struct node *cur = head->first; 
  
  global_trans_finds++;

  //if first value, dont't do anything!
  if (cur->val == s_val)
	return true;

  while (cur->next) {
        
	global_trans_finds++;

	if (cur->next->val == s_val) {  //checkig second value and swap only values if matches
	  int tmp = cur->val;
	  cur->val = cur->next->val;
	  cur->next->val = tmp;
            
	  return true; 
	}
        
	cur = cur->next;
  }

  return false;
    
}

/*
 * DELETEING FUNC--fuc taht deletes the element--
 * head - pointer to beginig of the list
 * val - value of deleteing data
 */ 
void delete(struct head *head, int d_val) {
  if (isEmpty(head))
	return;

  struct node *cur = head->first;
  struct node *prev; // = head->first;

  global_delete++;

  //deleteing special first value
  if (cur->val == d_val) {
	head->first = cur->next;
	//printf("deleting!: %d\n", cur->val); //debug
	free(cur);
	return;
  }

  //deleteing rest of vlues
  while (cur != NULL) {
        
	global_delete++;
        
	if (cur->val == d_val) {
	  prev->next = cur->next;
	  //printf("deleting: %d\n", cur->val); //debug
	  free(cur);
	  break;
	}

	prev = cur;
	cur = cur->next;
  }    

  return;
    
}

/*
 * l_print FUNC--func that prints whole list--
 */ 
void l_print(struct head *head) {
  struct node *cur = head->first;

  while (cur != NULL) {
	printf("val: %d\n", cur->val);
	cur = cur->next;
  }
}

int main(void) {
    
  struct head *h = createList();
  struct head *h1 = createList();

  srand(time(NULL)); //seed random

  int tab[100]; //tab for values

  for (int i = 1; i <= 100; i++) // fill tab with values
	tab[i-1] = i;

  for (int i = 0; i < 100; i++) { // permute tab values 100 times
	int a = rand()%99;
	int b = rand()%99;
	int tmp = 0;

	tmp = tab[a];
	tab[a] = tab[b];
	tab[b] = tmp;        
  }

  for (int i = 0; i < 100; i++) { // insert permuted values to lists
	insert(h, tab[i]);
	insert(h1, tab[i]);
  }

  while (!isEmpty(h)) { //delete all nodes
	bool everyone = true; //true if list is full
	int max = 0;
	for (int j = 100; j >= 0; j--) //iterate for every element of the list (sorted asc)
	  if (!findTRANS(h, j)) {  //check if value is in the list
		everyone = false;
	  } else {
		if (j > max) // set max
		  max = j;
	  }

	delete(h, max); // delete simple node with max value
  }

  global_counter = global_delete + global_trans_finds;
  
  printf("TRANS finds x %d\n", global_trans_finds);
  printf("TRANS deletes x %d\n", global_delete);
  printf("\e[32mTRANS all x %d\n\e[0m", global_counter);    

  if (isEmpty(h))
	printf("EMPTY!\n\n");
  
  global_counter = 0;
  global_delete = 0;
  global_trans_finds = 0;
    
  while (!isEmpty(h1)) { // delete all nodes
	bool everyone = true; //true if list is full
	int max = 0;
	for (int j = 1; j <= 100; j++) //iterate for every element of the list (sorted desc)
	  if (!findMTF(h1, j)) { //check if value is in the list
		everyone = false;
	  } else {
		if (j > max) //set max
		  max = j;
	  }
	       
	delete(h1, max);  // delete simple node with max value
  }

  global_counter = global_delete + global_mtf_finds;
  
  printf("MTF finds x %d\n", global_mtf_finds);
  printf("MTF deletes x %d\n", global_delete);
  printf("\e[31mMTF all x %d\n\e[0m", global_counter);    

  if (isEmpty(h1))
	printf("EMPTY!\n");
  
  return 0;
}
