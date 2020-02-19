#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Book {
	char* author[25];
	char* bookName[25];
	int year;
	int numberofPage;
	int price;
};

struct node {
	struct node *next;
	struct Book book;
};


/////////


struct node*ListInit(struct node *head) {
	head->next = NULL;
	return head;
}


void insertElem(struct node*el, struct node*newEl) {
	newEl->next = el->next;
	el->next = newEl;

}

void printList(struct node*lst) {
	struct node*p;
	p = lst;
	p = p->next;
	while (p != NULL) {

		printf("%s: '%s',price: %d,number of page:%d,year: %d\n", p->book.author, p->book.bookName, p->book.price, p->book.numberofPage, p->book.year);
		p = p->next;

	}
}
int calcMidPrice(struct node*lst) {
	struct node*p;
	p = lst;
	p = p->next;
	int counter = 0;
	int priceSum = 0;
	while (p != NULL) {
		priceSum += p->book.price;
		counter++;
		p = p->next;
	}
	int midPrice = priceSum / counter;
	return midPrice;
}
void deleteBooksWithLowPrice(struct node*lst) {
	struct node*p;
	p =lst;
	struct node*pp = lst;
	
	int price = calcMidPrice(pp);
	printf("Mid price=%d\n", calcMidPrice(pp));
	int cnt = 0;
	int len = getListLen(lst);
	while (p!=NULL) {
		struct node*prev = p;
		p = p->next;
		if (p == NULL)return;
		if (p->book.price < price) {
			struct node*pForDel = p;
			p=prev;
			p->next = p->next->next;

			free(pForDel);
		}
		
		cnt++;
	}
}


void elAppend(struct node*lst, struct Book *b) {
	struct node*newEl = (struct node*)malloc(sizeof(struct node));
	newEl->book = *b;
	struct node*p;
	p = lst;
	while (p->next != NULL) {
		p = p->next;
	}
	p->next = newEl;
	newEl->next = NULL;
}

int getListLen(struct node*lst) {
	struct node*t;
	t = &lst;
	t = t->next;
	int cnt = 0;
	while (t->next != NULL) {
		cnt++;
		t = t->next;
	}
	return cnt;
}


void insertByIndex(struct node*lst, int index, struct Book *b) {
	if (index > getListLen(lst))return;
	struct node*newEl = (struct node*)malloc(sizeof(struct node));
	newEl->book = *b;
	struct node*p;
	p = &lst;
	int counter = 0;
	p = p->next;
	index--;
	while ((counter != index) && (p->next != NULL)) {
		p = p->next;
		counter++;
	}
	newEl->next = p->next;
	p->next = newEl;
}



void sortByPrice(struct node** lst) {
	struct node*tmp;
	struct Book b;
	struct node*i = lst;
	struct node*j;
	for (; i != NULL; i = i->next) {
		for (j = i; j != NULL; j = j->next) {
			if (j->book.price < i->book.price) {
				b = i->book;
				i->book = j->book;
				j->book = b;


			}
		}
	}
}
int countLinesInFile(FILE*fp) {
	char sym;
	int numberOfAllBooks = 0;
	sym = getc(fp);
	do {
		if (sym == '\n') {
			numberOfAllBooks++;
		}
		sym = getc(fp);
	} while (sym != EOF);
	fseek(fp, SEEK_SET, 0);
	return numberOfAllBooks;
}
int menuPrint() {
	printf("\n1-Read list\n2-Append elements to current list\n3-Print list\n4-Delete books with price, lower than middle price\n5-Sort list\n6-insert elem\n7-save\n");
	return 1;
}

void fListWrite(struct node*lst, FILE*fp) {
	struct node*p;
	p = lst;
	p = p->next;
	while (p != NULL) {

		fprintf(fp, "%s %s %d %d %d\n", p->book.author, p->book.bookName, p->book.year, p->book.numberofPage, p->book.price);
		p = p->next;

	}
}

void cleanList(struct node*lst) {
	lst = lst->next;
	while (lst != NULL) {
		struct node*l;
		l = lst;

		lst = lst->next;
		free(l);
	}
}

int main() {
	FILE *f = NULL;
	f = fopen("data.txt", "r");

	int numberOfNodes = 0;
	numberOfNodes = countLinesInFile(f);
	int isRun = 1;
	struct node list;
	char operation;
	ListInit(&list);
	menuPrint();
	struct Book b;
	char oper;
    do
    {

		printf(">>");
		scanf("%c", &oper);
		if (oper == '1') {

			for (int i = 0; i < numberOfNodes; i++) {


				fscanf(f, "%s", &b.author);

				fscanf(f, "%s", &b.bookName);

				fscanf(f, "%d", &b.year);

				fscanf(f, "%d", &b.numberofPage);

				fscanf(f, "%d", &b.price);
				if (b.year > 0 && b.price >= 0 && b.numberofPage > 0) {
					elAppend(&list, &b);
				}
				else {
					printf("Error in file with reading book N%d. Not enought data in file\n", i + 1);
				}
			}
			printf("\nList len-%d\n", getListLen(&list));
			menuPrint();
		}
		else if (oper == '2') {
			struct Book b;
			printf("Author: ");
			scanf("%s", b.author);
			printf("Book's name: ");
			scanf("%s", b.bookName);
			printf("Year: ");
			scanf("%d", &b.year);
			printf("Number of page: ");
			scanf("%d", &b.numberofPage);
			printf("Price: ");
			scanf("%d", &b.price);
			printf("\n----------------\n");
			if (b.year > 0 && b.price >= 0 && b.numberofPage > 0) {
				elAppend(&list, &b);
			}
			else {
				printf("Error input\n");
			}
			menuPrint();
		}
		else if (oper == '3') {
			if (&list != NULL)printList(&list);
			menuPrint();
		}
		else if (oper == '4') {
			deleteBooksWithLowPrice(&list);
			menuPrint();

		}
		else if (oper == '5') {
			sortByPrice(&list);
			printf("\nSorted.Choose'3' to see new list\n");
			menuPrint();
		}
		else if (oper == '6') {
			int index = 0;
			printf("\nEnter index insertion: ");
			scanf("%d", &index);
			printf("\n");
			struct Book b;
			printf("Author: ");
			scanf("%s", b.author);
			printf("Book's name: ");
			scanf("%s", b.bookName);
			printf("Year: ");
			scanf("%d", &b.year);
			printf("Number of page: ");
			scanf("%d", &b.numberofPage);
			printf("Price: ");
			scanf("%d", &b.price);
			printf("\n----------------\n");

			menuPrint();
			if (b.year > 0 && b.price >= 0 && b.numberofPage > 0) {
				insertByIndex(&list, index, &b);
			}
			else {
				printf("Error input\n");
			}

		}
		else if (oper == '7') {
			fclose(f);
			FILE*f2;
			f2 = fopen("data.txt", "w");
			fListWrite(&list, f2);
			fclose(f2);

			cleanList(&list);


			isRun = 0;

		}
		
		


	}while (isRun);

	printf("\nClick smth to exit");
	getchar();
	getchar();
	return 0;

}
