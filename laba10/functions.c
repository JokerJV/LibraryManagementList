#include "Header.h"

struct node*listInit(struct node *head) {// head mustn't be a pointer, call with &nodeHead
	head->next = NULL;
	return head;
}


void insertElem(struct node*el, struct node*newEl) {//If index not exist elem will be in the end
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
void deleteBooksWithLowPrice(struct node*lst) {//price lower than middle
	struct node*p;
	p = lst;
	struct node*pp = lst;

	int price = calcMidPrice(pp);
	printf("Mid price=%d\n", calcMidPrice(pp));
	int cnt = 0;
	int len = getListLen(lst);
	while (p != NULL) {
		struct node*prev = p;
		p = p->next;
		if (p == NULL)return;
		if (p->book.price < price) {
			struct node*pForDel = p;
			p = prev;
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



void sortByPrice(struct node** lst) {//in growth order
	struct node*tmp;
	struct Book book;
	struct node*i = lst;
	struct node*j;
	for (; i != NULL; i = i->next) {
		for (j = i; j != NULL; j = j->next) {
			if (j->book.price < i->book.price) {
				book = i->book;
				i->book = j->book;
				j->book = book;


			}
		}
	}
}
int countLinesInFile(FILE*fp) {// count each '\n' symbol
	char sym;
	int numberOfBooks = 0;
	sym = getc(fp);
	do {
		if (sym == '\n') {
			numberOfBooks++;
		}
		sym = getc(fp);
	} while (sym != EOF);
	fseek(fp, SEEK_SET, 0);
	return numberOfBooks;
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
		struct node*nodeToClean;
		nodeToClean = lst;

		lst = lst->next;
		free(nodeToClean);
	}
}
