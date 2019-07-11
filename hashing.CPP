#include<iostream.h>
#include<stdlib.h>
#include<conio.h>

/* Node for storing an item in a Linked List */
struct node
{      public:
	int key;
	int value;
	struct node *next;
};

/* For storing a Linked List at each index of Hash Table  */
struct arrayitem
{     public:

	struct node *head;
	/* head pointing the first element of Linked List at an index of Hash Table */

	struct node *tail;
       int count;	/* tail pointing the last element of Linked List at an index of Hash Table */

};

struct arrayitem *array;
int size = 0;
    /* Determines the no. of elements present in Hash Table */
int max = 5;
 /* Determines the maximum capacity of Hash Table array */
// array = (struct arrayitem*) malloc(max * sizeof(struct arrayitem*));
/* This function creates an index corresponding to the every given key */
int hashcode(int key)
{
	return (key % max);
}

struct node* get_element(struct node *list, int find_index);
void remove_element(int key);
void rehash();
void init_array();
int find(struct node *list, int key);
void insert(int key, int value)
{
//	float n = 0.0;
	/* n => Load Factor, keeps check on whether rehashing is required or not */

	int index = hashcode(key);

	/* Extracting Linked List at a given index */
	struct node *list = (struct node*) array[index].head;
	/* Creating an item to insert in the Hash Table */
	struct node *item = (struct node*) malloc(sizeof(struct node));
	item->key = key;
	item->value = value;
	item->next = NULL;
	if (list == NULL)
	{
		/* Absence of Linked List at a given Index of Hash Table */

		cout<<"Inserting "<<key<<"(key) and"<<value<<"(value) \n";
		array[index].head = item;
		array[index].tail = item;
		size++;
		array[index].count=1;

	}
	else if(array[index].count<3)
	{
		/* A Linked List is present at given index of Hash Table */

				array[index].tail->next = item;
				array[index].tail = item;
				size++;

		array[index].count++;
		}
	else
		{ index=(index+1)%max;
		while(1)
		{
		if(array[index].head==NULL)
		{
		    array[index].head = item;
		array[index].tail = item;
		size++;
		array[index].count=1;
		break;
		}
		   else if(array[index].count<3)
			       {
				array[index].tail->next = item;
				array[index].tail = item;
				size++;
				array[index].count++;
				break;
				}
		else;
		index++;
		}

		}
	//Calculating Load factor
	//n = (* size) / max;
	if (size>= max*3)
	{
		//rehashing

		cout<<"going to rehash\n";
		rehash();
	}
}

void rehash()
{
	struct arrayitem *temp = array;
	/* temp pointing to the current Hash Table array */

	int i = 0, n = max;
	size = 0;
	max = 2 * max;

	/*
	 *array variable is assigned with newly created Hash Table
	 *with double of previous array size
	*/
	array = (struct arrayitem*) malloc(max * sizeof(struct node));
	init_array();

	for (i = 0; i < n; i++)
	{

		/* Extracting the Linked List at position i of Hash Table array */
		struct node* list = (struct node*) temp[i].head;

		if (list == NULL)
		{

			/* if there is no Linked List, then continue */
			continue;

		}
		else
		{
			/*
			 *Presence of Linked List at i
			 *Keep moving and accessing the Linked List item until the end.
			 *Get one key and value at a time and add it to new Hash Table array.
			*/

			while (list != NULL)
			{
				insert(list->key, list->value);
				list = list->next;
			}

		}

	}
	temp = NULL;
}

/*
 *This function finds the given key in the Linked List
 *Returns it's index
 *Returns -1 in case key is not present
*/
int find(struct node *list, int key)
{
	int retval = 0;
	struct node *temp = list;
	while (temp != NULL)
	{
		if (temp->key == key)
		{
			return retval;
		}
		temp = temp->next;
		retval++;
	}
	return -1;

}

/* Returns the node (Linked List item) located at given find_index  */
struct node* get_element(struct node *list, int find_index)
{
	int i = 0;
	struct node *temp = list;
	while (i != find_index)
	{
		temp = temp->next;
		i++;
	}
	return temp;
}
void remove_element(int key)
{
	int index = hashcode(key);
	int keep=0;
	int searchlength=0;
	do{
	struct node *list = (struct node*) array[index].head;
	if (list == NULL)
	{
		keep=keep+1;
		searchlength=searchlength+1;
	}
	else
	{
		int find_index = find(list, key);

		if (find_index == -1)
	      {    keep=keep+1;
		//cout<<"This key does not exists\n";

	       }
		else
	    {
			struct node *temp = list;
			if (temp->key == key)
			{

				array[index].head = temp->next;
				cout<<"This key has been removed\n";
				size--;
				return;
			}

			while (temp->next->key != key)
			{
				temp = temp->next;
			}

			if (array[index].tail == temp->next)
			{
				temp->next = NULL;
				array[index].tail = temp;

			}
			else
			{
				temp->next = temp->next->next;

			}
				searchlength++;
		       cout<<"This key has been removed\n";
		       size--;
		       return;

	       }

	}
	index=(index+1)%max;
	} while(searchlength<max);
	if(keep>=max)
	cout<<"This key does not exist\n";
}

/* To display the contents of Hash Table */
void display()
{
	int i = 0;
	for (i = 0; i < max; i++)
	{
		struct node *temp = array[i].head;
		if (temp == NULL)
		{
			cout<<"array"<<i<<" has no elements\n";
		}
		else
		{
			cout<<"array"<<i<<" has elements-: ";
			while (temp != NULL)
			{
				cout<<"key="<<temp->key<<"value="<<temp->value<<"\t";
				temp = temp->next;
			}
			cout<<"\n";
		}
	}
}

/* For initializing the Hash Table */
void init_array()
{
	int i = 0;
	for (i = 0; i < max; i++)
	{
		array[i].head = NULL;
		array[i].tail = NULL;
	}
}

/* Returns size of Hash Table */
int size_of_array()
{       // struct node *x;
	return size;
}

void main()
{
	int choice, key, value, n, c;
clrscr();
	//array = (struct arrayitem*) malloc(max * sizeof(struct arrayitem*));
	init_array();
	do {
		cout<<"Implementation of Hashing chain with singly linked list in C++\n\n";
		cout<<"MENU-: \n1.Inserting item in the Hash Table"
			      "\n2.Removing item from the Hash Table"
			      "\n3.Check the size of Hash Table"
			      "\n4.To display a Hash Table"
		       "\n\n Please enter your choice -: ";
		cin>>choice;
		switch(choice)
		{
		case 1:
		      cout<<"Inserting element in Hash Table\n";
		      cout<<"Enter key and value-:\t";
		      cin>>key;
		      cin>>value;
		      insert(key, value);
		      break;
		case 2:
		      cout<<"Deleting in Hash Table \nEnter the key to delete-:";
		      cin>>key;
		      remove_element(key);
		      break;
		case 3:
		      n = size_of_array();
		      cout<<"Size of Hash Table is-:"<<n<<"\n";
		      break;
		case 4:
		      display();
		      break;
		default:
		       cout<<"Wrong Input\n";
		}
		cout<<"\nDo you want to continue-:(press 1 for yes)\t";
	cin>>c;

	}while(c == 1);

	getch();

}
