#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "utlist.h"

struct node {
    int data;
    struct node* next;
};
typedef struct node Node;

int datacmp (Node* a, Node* b)
{
	if (a->data > b->data) {
		return 1;
	} else if (a->data < b->data) {
		return -1;
	} else {
		return 0;
	}
}

int print_menu(int selection)
{
	printf("\n\t.::Linked List Menu::.\n");
	printf("\n>Enter 1 to add data into list");
	printf("\n>Enter 2 to show list info");
	printf("\n>Enter 3 to delete entire list");
	printf("\n>Enter 4 to search an element in list");
	printf("\n>Enter 5 to delete a specific element");
	printf("\n>Enter 6 to sort the list");
	printf("\n>Enter 7 to exit");
	printf("\n>>>Enter here: ");

	while (!scanf("%d", &selection)) {
		while (getchar() != '\n');
		printf("\nPlease enter a valid menu option: ");
	}

	return selection;
}

void list_append (Node** list)
{
	char user_yn;
	Node* newnode = malloc(sizeof(Node));

	printf("\nEnter the data you want to add: ");

	while (!scanf("%d", &(newnode->data))) {
		printf("\nPlease enter a valid data: ");
		while (getchar() != '\n');
	}

	LL_APPEND(*list, newnode);

	printf("\nElement added. More? (y/n): ");
	scanf(" %c", &user_yn);

	if(user_yn == 'y') {
		list_append(list);
	}

	return;
}

void list_print (Node* list)
{
	Node* elt,* tmp;
			LL_FOREACH_SAFE(list,elt,tmp) {
					if(elt->next) {
						printf("%d -> ", elt->data);
					} else {
						printf("%d", elt->data);
					}
		    	}
			return;
}

int list_length (Node* list)
{
	int len = 0;
	Node* elt,* tmp;
	LL_FOREACH_SAFE(list,elt,tmp) {
			len++;
		    	}
	return len;
}

void list_info (Node* list)
{
	printf("\n___INFO___\nList: ");
	list_print(list);
	printf("\n\nList length: %d\n", list_length(list));
	return;
}

void list_delete (Node** list)
{
	if((*list) == NULL) {
		printf("\nERR: List is already empty.\n");
		return;
	}
	char user_yn;

	printf("\nWARNING! Are you sure? This will erase entire list! (y/n): ");
	scanf(" %c", &user_yn);

	if(user_yn == 'y'){
		Node* elt,* tmp;

		LL_FOREACH_SAFE(*list,elt,tmp) {
			LL_DELETE(*list,elt);
	    	}
		printf("\nList Deleted.\n");
	}
	return;
}

void list_search (Node* list)
{
	if (list == NULL) {
		printf("\nERR: You can't search a list which has 0 elements.\n");
		return;
	}

	Node *elt, *tmp;
	int place = 1;
	printf("\nEnter the value you want to search for: ");

	int user_value;

	while (!scanf("%d", &user_value)) {
		printf("You can't search that. Please enter a valid data: ");
		while (getchar() != '\n');
	}

	LL_FOREACH_SAFE(list, elt, tmp) {

		if (elt->data == user_value) {
			printf("\nElement found at position %d.\n", place);
			break;
		}
		place++;
	}

	if(elt == NULL) {
		printf("\nElement is not in the list.\n");
	}
	return;

}

void list_sort (Node** list)
{
	if ((*list)->next == NULL) {
		printf("\nERR: You can't sort a list with single element.\n");
		return;
	}

	LL_SORT(*list, datacmp);
	printf("\nList sorted.\n");

	return;
}

void node_delete (Node* list)
{
	if(list == NULL) {
		printf("\nERR: List is empty.\n");
		return;
	}

	Node *elt, *tmp;
	printf("\nEnter the value you want to delete: ");

	int user_value;
	while (!scanf("%d", &user_value)) {
		printf("\nPlease enter a valid data: ");
		while (getchar() != '\n');
	}

	LL_FOREACH_SAFE(list, elt, tmp) {
		if (elt->data == user_value) {
			LL_DELETE(list, elt);
			printf("\nElement found and deleted.\n");
			break;
		}
	}

	if(elt == NULL) {
		printf("\nElement is not in the list.\n");
	}

	return;
}

void silent_list_delete (Node** list)
{
	if((*list) == NULL) {
		return;
	} else {
		Node* elt,* tmp;
			LL_FOREACH_SAFE(*list,elt,tmp) {
				LL_DELETE(*list,elt);
			}
	  }

	return;
}

int main ( )
{
	Node* list = NULL;
	int user_menu_choice = 0;
	int exit = 1;

	while(exit){
		switch (user_menu_choice)
		{
			case 1:		list_append(&list);
						user_menu_choice = 0;
						break;

			case 2:		list_info(list);
						user_menu_choice = 0;
						break;

			case 3:		list_delete(&list);
						user_menu_choice = 0;
						break;

			case 4:		list_search(list);
						user_menu_choice = 0;
						break;

			case 5:		node_delete(list);
						user_menu_choice = 0;
						break;

			case 6:		list_sort(&list);
						user_menu_choice = 0;
						break;

			case 7:		exit = 0;
						break;

			default: 	user_menu_choice = print_menu(user_menu_choice);
						break;
		}
	}

	silent_list_delete(&list);
	return 0;
}
