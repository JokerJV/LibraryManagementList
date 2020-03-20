#pragma once
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

struct node*ListInit(struct node *head);

void insertElem(struct node*el, struct node*newEl);

void printList(struct node*lst);

int calcMidPrice(struct node*lst);

void deleteBooksWithLowPrice(struct node*lst);


void elAppend(struct node*lst, struct Book *b);

int getListLen(struct node*lst);


void insertByIndex(struct node*lst, int index, struct Book *b);

void sortByPrice(struct node** lst);

int countLinesInFile(FILE*fp);

int menuPrint();

void fListWrite(struct node*lst, FILE*fp);

void cleanList(struct node*lst);
