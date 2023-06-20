#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
	int dd, mm, yy;
}date;

typedef struct {
	char tt[11];
	date br;
	date rt;
	char name[20];
	char sdt[10];
}status;

typedef struct {
	int id;
	char name[100];
	char type[100];
	int namst;
	char author[100];
	status stt;
}book;

void showFunctions();
bool askContinue(char statement[]);
int checkInL(book* l, int p);
void showSearchMenu();
void showBookInfo(book* l, int i);
void showLibrary(book* l, int c);
void showUpdateMenu(book* l, int p);
void returnBook(book* l, int p);
void borrowBook(book* l, int p);
int deleteBook(book* l, int c, int position);
void editBookInfo(book* l, int position);
int searchByName(book* l, int c);
int searchById(book* l, int c);
void getType(book* l, int c);
void searchByType(book* l, int c);
book getBookInfo(book* l, int c, bool check);
int appendLibrary(book* l, int c, book a);
void strcline(char[], char[], int len);

int main() {
	printf("\n______________________________________________________________________|| LIBRARY MANAGEMENT PROGRAM ||______________________________________________________________________\n");

	book library[1000]; int current = 0;

	/*DATA LOADING*/

	//FILE* f; errno_t err;

	char filename[] = "library.txt";
	//char filename[] = "C:/Users/HUONG GIANG/Documents/UNI/Programming 1/Final/final01/final01/library.txt";

	FILE* f; errno_t err;
	err = fopen_s(&f, filename, "r");
	if (!err)   {
		char line[256];
		fgets(line, 256, f);
		int num_ele = atoi(line);
		printf("\t\tLibrary now has %d books!\n\n", num_ele);
		//loading data
		for (int i = 0; i < num_ele; i++) {
			// create a student structure and put it in list
			book bk;
			char line[256];
			fgets(line, 256, f); bk.id = atoi(line);
			fgets(line, 256, f);
			int len1 = strlen(line);
			char name[254]; strcline(line, name, len1 - 1);
			strcpy(bk.name, name);
			fgets(line, 256, f);
			int len6 = strlen(line);
			char tp[254]; strcline(line, tp, len6 - 1); strcpy(bk.type, tp);
			fgets(line, 256, f);
			int len5 = strlen(line);
			char st[254]; strcline(line, st, len5 - 1); strcpy(bk.author, st);
			fgets(line, 256, f); bk.namst = atoi(line);
			fgets(line, 256, f);
			int len4 = strlen(line);
			char au[254]; strcline(line, au, len4 - 1); strcpy(bk.stt.tt, au);
			fgets(line, 256, f); bk.stt.br.dd = atoi(line);
			fgets(line, 256, f); bk.stt.br.mm = atoi(line);
			fgets(line, 256, f); bk.stt.br.yy = atoi(line);
			fgets(line, 256, f); bk.stt.rt.dd = atoi(line);
			fgets(line, 256, f); bk.stt.rt.mm = atoi(line);
			fgets(line, 256, f); bk.stt.rt.yy = atoi(line);
			fgets(line, 256, f);
			int len2 = strlen(line);
			char namebr[254]; strcline(line, namebr, len2 - 1); strcpy(bk.stt.name, namebr);
			fgets(line, 256, f);
			int len3 = strlen(line);
			char sdt[254]; strcline(line, sdt, len3 - 1); strcpy(bk.stt.sdt, sdt);
			current = appendLibrary(library, current, bk);
		}
	} fclose(f);
	
	while (true) {
		showFunctions(); int choose;
		printf("\n\nInsert:"); scanf("%d", &choose); while (getchar() != '\n');
		char statement[10];
		if (choose == 0) break;

		if (choose == 1) {
			printf("\n\t\t>>>>> || APPENDING NEW BOOK ||\n");
			while (true) {
				printf("\n\t\t\t--- Get book's information ---\n");
				book a = getBookInfo(library, current, true);
				current = appendLibrary(library, current, a);
				strcpy(statement, "appending");
				if (!(askContinue(statement))) break;
			} printf("\n\t\t=========================================================================================================================");
		}

		else if (choose == 2) {
			showLibrary(library, current);
			printf("\n\t\t=========================================================================================================================");
		}

		else if (choose == 3) {
			printf("\n\t\t>>>>>|| SEARCH BOOK ||\n\n");
			while (true) {
				showSearchMenu();
				int opt;
				printf("Insert: ");  scanf("%d", &opt); while (getchar() != '\n');
				printf("\n");
				if (opt == 1) {
					int position = searchByName(library, current);
					int check = checkInL(library, position);
				}
				else if (opt == 2) {
					searchByType(library, current);
				}
				else if (opt == 3) {
					int position = searchById(library, current);
					int check = checkInL(library, position);
				}
				else printf("invalid input!");
				strcpy(statement, "searching");
				if (!(askContinue(statement))) break;
			} printf("\n\t\t=========================================================================================================================");
		}

		else if (choose == 4) {
			printf("\n\t\t>>>>>|| DELETE BOOK ||\n\n");
			while (true) {
				int position = searchById(library, current);
				int check = checkInL(library, position);
				if (check == 1) { current = deleteBook(library, current, position); printf("\nDELETE SUCCESSFULLY!"); }
				strcpy(statement, "deleting");
				if (!(askContinue(statement))) break;
			} printf("\n\t\t=========================================================================================================================");
		}

		else if (choose == 5) {
			printf("\n\t\t>>>>>|| UPDATE BOOK'S INFORMATION ||\n\n");
			while (true) {
				int position = searchById(library, current);
				int check = checkInL(library, position);
				if (check == 1) {
					showUpdateMenu(library, position);
					while (true) {
						int opt; printf("Insert: "); scanf("%d", &opt); while (getchar() != '\n');
						if (opt == 1) { editBookInfo(library, position); break; }
						else if (opt == 2) {
							if (strcmp(library[position].stt.tt, "Available") == 0) borrowBook(library, position);
							else {
								returnBook(library, position); printf("\nReturn book successfully!\n");
							}
							break;
						} else printf("Invalid input!\n");
					}
				}
				strcpy(statement, "updating");
				if (!(askContinue(statement))) break;
			} printf("\n\t\t=========================================================================================================================");
		}

		else printf("Invalid input!");

		printf("\n");
	}

	/*SAVE DATA*/

	err = fopen_s(&f, filename, "w");
	if (!err) {
		fprintf(f, "%d\n", current); //first line
		for (int i = 0; i < current; i++) {
			// save elements
			fprintf(f, "%d\n", library[i].id);
			fprintf(f, "%s\n", library[i].name);
			fprintf(f, "%s\n", library[i].type);
			fprintf(f, "%s\n", library[i].author);
			fprintf(f, "%d\n", library[i].namst);
			fprintf(f, "%s\n", library[i].stt.tt);
			fprintf(f, "%d\n", library[i].stt.br.dd);
			fprintf(f, "%d\n", library[i].stt.br.mm);
			fprintf(f, "%d\n", library[i].stt.br.yy);
			fprintf(f, "%d\n", library[i].stt.rt.dd);
			fprintf(f, "%d\n", library[i].stt.rt.mm);
			fprintf(f, "%d\n", library[i].stt.rt.yy);
			fprintf(f, "%s\n", library[i].stt.name);
			fprintf(f, "%s\n", library[i].stt.sdt);
		}
	}

	printf("\nGoodbye and see you later!\n");
	return 0;
}

void showFunctions() {
	printf("\n\t\t|| MENU FUNCTION ||\n");
	printf("\t\t__________________________________________________________________\n");
	printf("\t\tInsert 1 if you want to APPEND NEW BOOK into the library.\n");
	printf("\t\tInsert 2 if you want to SEE LIST OF BOOK.\n");
	printf("\t\tInsert 3 if you want to SEARCH BOOK.\n");
	printf("\t\tInsert 4 if you want to DELETE BOOK in the library.\n");
	printf("\t\tInsert 5 if you want to UPDATE BOOK'S INFORMATION in the library.\n");
	printf("\t\tInsert 0 if you want to exit program\n");
	printf("\t\t__________________________________________________________________\n");
}

bool askContinue(char statement[]) {
	char rep;
	printf("\n\t\t\tContinue %s book? (y/n)", statement); scanf("%c", &rep); while (getchar() != '\n');
	printf("\n");
	return (rep == 'y');
}

int checkInL(book* l, int p) {
	if (p < 0) {
		printf("\nThere's no book having required condition!\n");
		return 0;
	}
	else {
		showBookInfo(l, p);
		return 1;
	}
}

void showSearchMenu() {
	printf("\t\t\tInsert 1 if you want to search book BY NAME\n");
	printf("\t\t\tInsert 2 if you want to search book BY TYPES\n");
	printf("\t\t\tInsert 3 if you want to search book BY ID\n");
}

void showUpdateMenu(book* l, int p) {
	printf("\n\t\t\tInsert 1 if you want to EDIT BOOK'S INFORMATION\n");
	if (strcmp(l[p].stt.tt,"Available")==0) printf("\t\t\tInsert 2 if you want to INSERT BORROWER'S INFORMATION\n\n");
	else printf("\t\t\tInsert 2 if you want to RETURN BOOK\n\n");
}

void showBookInfo(book* l, int p) {
	printf("\t\t\t%d - '%s' (%s) - %s, %d - %s\n", l[p].id, l[p].name, l[p].type, l[p].author, l[p].namst, l[p].stt.tt);
	if ((strcmp(l[p].stt.tt, "Unavailable") == 0)) {
		printf("\t\t\t\tFrom %d-%d-%d to %d-%d-%d by %s (%s)\n", l[p].stt.br.dd, l[p].stt.br.mm, l[p].stt.br.yy, l[p].stt.rt.dd, l[p].stt.rt.mm, l[p].stt.rt.yy, l[p].stt.name, l[p].stt.sdt);
	} 
	//printf("\t\t\t------------------------------------------------------------------------------------------\n\n");
	printf("\t\t\t.........................................................................................................\n\n");
}

void showLibrary(book* l, int c) {
	printf("\n\t\t>>>>>|| BOOK LIST ||\n\n");
	for (int i = 0; i < c; i++) {
		showBookInfo(l, i);
	}
}

int deleteBook(book* l, int c, int position) {
	for (int i = position; i < c; i++) l[i] = l[i + 1];
	c--;
	return c;
}

void editBookInfo(book* l, int position) {
		printf("Insert updated information:\n");
		book a;
		a = getBookInfo(l,position, false);
		l[position] = a;// updated information.
}

int searchByName(book* l, int c) {
	char namebk[100];
	printf("\t\t\tInsert name of the book: "); gets_s(namebk); 
	for (int i = 0; i < c; i++) {
		if (strcmp(namebk, l[i].name) == 0) return i;
	} return -1;
}

int searchById(book* l, int c) {
	int id;
	printf("\t\t\tInsert ID of the book: "); scanf("%d", &id); while (getchar() != '\n');
	for (int i = 0; i < c; i++) {
		if (id == l[i].id) return i;
	} return -1;
}  

void getType(book* l, int c) {
	char array_type[100][20];
	for (int i = 0; i < 100; i++) strcpy(array_type[i], "empty");
	int z = 0;
	for (int i = 0; i < c; i++) {
		bool check = true;
		for (int j = 0; j < 100; j++) {
			if (strcmp(l[i].type, array_type[j]) == 0) { check = false;  break; }
		} 
		if (check == true) { strcpy(array_type[z], l[i].type); z++; }
	}
	//print types
	for (int i = 0; i < 100; i++) {
		if (strcmp(array_type[i], "empty") == 0) break;
		printf("%s; ", array_type[i]);
	}
}

void searchByType(book*l, int c) {
	printf("\t\t\tThe library now has these categories: "); getType(l, c);
	printf("\n\n\t\t\tInsert one type to find the book you want: "); 
	char type[20]; gets_s(type); printf("\n");
	int dem = 0;
	for (int i = 0; i < c; i++) {
		if (strcmp(l[i].type, type) == 0) { printf("\t"); showBookInfo(l, i); dem++; }
	}
	printf("\n\t\t\t=> %d books with type %s\n", dem, type);
}

void borrowBook(book* l, int p) {
	strcpy(l[p].stt.tt, "Unavailable");
	printf("\t\tInsert borrow date: "); scanf("%d%d%d", &l[p].stt.br.dd, &l[p].stt.br.mm, &l[p].stt.br.yy);
	printf("\t\tInsert return date: "); scanf("%d%d%d", &l[p].stt.rt.dd, &l[p].stt.rt.mm, &l[p].stt.rt.yy); while (getchar() != '\n');
	printf("\t\tInsert name of borrower: "); gets_s(l[p].stt.name);
	printf("\t\tInsert phone number of borrower: "); gets_s(l[p].stt.sdt);
}

void returnBook(book* l, int p) {
	strcpy(l[p].stt.tt, "Available");
	l[p].stt.br.dd = 0;
	l[p].stt.br.mm = 0;
	l[p].stt.br.yy = 0;
	l[p].stt.rt.dd = 0;
	l[p].stt.rt.mm = 0;
	l[p].stt.rt.yy = 0;
	strcpy(l[p].stt.name, "0");
	strcpy(l[p].stt.sdt, "0");
}

book getBookInfo(book* l, int c, bool check) {
	book a;
	if (check == false) a.id = l[c].id;
	else while (check == true) {
		printf_s("\n\t\t\tInsert ID of the book: "); scanf_s("%d", &a.id); while (getchar() != '\n');
		for (int i = 0; i < c; i++) {
			if (l[i].id == a.id) {
				printf("\nID exists. Please insert another ID!\n");
				break;
			}
			else if (i == (c - 1)) check = false;
		}
	}

	printf_s("\t\t\tInsert name of the book: "); gets_s(a.name);
	printf("\t\t\tInsert type of book: "); gets_s(a.type);
	printf_s("\t\t\tInsert author the book: "); gets_s(a.author);
	printf_s("\t\t\tInsert year when book is created: "); scanf_s("%d", &a.namst); while (getchar() != '\n');
	strcpy(a.stt.tt, "Available");
	a.stt.br.dd = 0;
	a.stt.br.mm = 0;
	a.stt.br.yy = 0;
	a.stt.rt.dd = 0;
	a.stt.rt.mm = 0;
	a.stt.rt.yy = 0;
	strcpy(a.stt.name, "0");
	strcpy(a.stt.sdt, "0");

	return a;
}

int appendLibrary(book* l, int c, book a) {
	if (c < 1000) {
		l[c] = a;
		c++;
	}
	else
		printf("Over capacity! Can't import new book!");
	return c;
}

void strcline(char source[], char dest[], int len) {
	int i = 0;
	for (i = 0; i < len; i++)
		dest[i] = source[i];
	dest[i] = '\0';
}