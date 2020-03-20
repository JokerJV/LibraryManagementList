
#include "Header.h"


int main() {
	FILE *f = NULL;
	f = fopen("data.txt", "r");

	int numberOfNodes = 0;
	numberOfNodes = countLinesInFile(f);
	int isRun = 1;

	struct node list;
	listInit(&list);
	char oper = '1';

	char operation;
	menuPrint();
	printf(">>");
	scanf("%c", &oper);
	struct Book book;
	while (isRun)
    {

		if (oper == '1') {

			for (int i = 0; i < numberOfNodes; i++) {


				fscanf(f, "%s", &book.author);

				fscanf(f, "%s", &book.bookName);

				fscanf(f, "%d", &book.year);

				fscanf(f, "%d", &book.numberofPage);

				fscanf(f, "%d", &book.price);
				if (book.year > 0 && book.price >= 0 && book.numberofPage > 0) {
					elAppend(&list, &book);
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
		
		printf(">");
		scanf("%c", &oper);


	}

	printf("\nClick smth to exit");
	getchar();
	getchar();
	return 0;

}
