#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h> 

struct Contact {
	char name[50];
	char phone[15];
	char email[30];
	struct Contact* next;

};
struct Hash {
	struct Contact** table;
	int size;
	int count;

};
unsigned long hash_djb2(const char* str, int size) {
	unsigned long hash = 5381;
	int c;

	while ((c = *str++)) {
		hash = ((hash << 5) + hash) + c;  
	}

	return hash % size;
}
struct Hash* create(int size) {
	struct Hash* pb = (struct Hash*)malloc(sizeof(struct Hash));
	pb->size = size;
	pb->count = 0;
	pb->table = calloc(size, sizeof(struct Contact*));
	return pb;

}
void insert(struct Hash* pb, const char* name, const char* phone, const char* email) {
	int index = hash_djb2(name, pb->size);
	struct Contact* NewNode = (struct Contact*)malloc(sizeof(struct Contact));
	strcpy(NewNode->name, name);
	strcpy(NewNode->phone, phone);
	strcpy(NewNode->email, email);
	NewNode->next = pb->table[index];
	pb->table[index] = NewNode;
	pb->count++;



}
struct Contact* search(struct Hash* pb, const char* name) {
	int index = hash_djb2(name, pb->size);
	struct Contact* cur = pb->table[index];
	while (cur != NULL) {
		if (strcmp(cur->name, name) == 0) {
			return cur;
		}
		cur = cur->next;
	}
	return NULL;
}
void print(struct Hash* pb) {
	for (int i = 0; i < pb->size; i++) {
		struct Contact* cur = pb->table[i];
		while (cur != NULL) {
			printf("%s %s %s\n", cur->name, cur->phone, cur->email);
			cur = cur->next;

		}
	}
}
void del(struct Hash* pb, const char* name) {
	int index = hash_djb2(name, pb->size);
	struct Contact* cur = pb->table[index];
	struct Contact* prew = NULL;
	while (cur != NULL) {
		if (strcmp(cur->name, name) == 0) {
			if (prew == NULL) {
				pb->table[index] = cur->next;
				free(cur); 
				pb->count--;
				printf("Deleted: %s\n", name);
				return;
			}
			else {
				printf("Deleted: %s\n", name);
				prew->next = cur->next;

			}
			free(cur);
			pb->count--;
		}
		prew = cur;
		cur = cur->next;
	}
	printf("Cannot delete: %s not found\n", name);


}
void stat(struct Hash* pb) {
	int empty_slots = 0;
	int collisions = 0;
	int longest_chain = 0;
	printf("\n===== HASH TABLE STATISTICS =====\n");
	printf("Table size: %d\n", pb->size);
	printf("Total elements: %d\n", pb->count);
	for (int i = 0; i < pb->size; i++) {
		struct Contact* cur = pb->table[i];
		if (cur == NULL) {
			empty_slots++;

		}
		else {
			int chain_lenght = 0;
			while (cur != NULL) {
				chain_lenght++;
				cur = cur->next;

			}
			if (chain_lenght > 1) {
				collisions = collisions + (chain_lenght - 1);


			}
			if (chain_lenght > longest_chain) {
				longest_chain = chain_lenght;
			}
		}

	}
	float load_factor = (float)pb->count / pb->size;
	printf("Empty slots: %d\n", empty_slots);
	printf("Collisions: %d\n", collisions);
	printf("Longest chain: %d\n", longest_chain);
	printf("Load factor: %.2f\n", load_factor);
	printf("=================================\n");


}
void show_menu(int count) {
	printf("\n");
	printf("+========================================+\n");
	printf("|    PHONEBOOK (Hash Table)             |\n");
	printf("+========================================+\n");
	printf("Contacts: [%d]\n", count);
	printf("1. Add Contact\n");
	printf("2. Search Contact\n");
	printf("3. Delete Contact\n");
	printf("4. Show All Contacts\n");
	printf("5. Statistics\n");
	printf("6. Export to File\n");
	printf("7. Import from File\n");
	printf("8. Generate Test Data\n");
	printf("9. Search Contact by prefixs\n");
	printf("10.Visualize Distribution\n");
	printf("0. Exit\n");
	printf(">> ");
}
void export_to_file(struct Hash* pb) {
	if (pb->count == 0) {
		printf("No data to add\n");
		return;
	}
	FILE* fp;
	fp = fopen("phone_book.txt", "w");
	if (fp == NULL) {
		printf("Error openning fie\n");
		return;
	}
	for (int i = 0; i < pb->size; i++) {
		struct Contact* cur = pb->table[i];
		while (cur != NULL) {
			fprintf(fp, "%s,%s,%s\n", cur->name, cur->phone, cur->email);
			cur = cur->next;
		}
	}
	printf("All data added succesfully\n");
	fclose(fp);

}
void load_data(struct Hash* pb) {
	FILE* fp;
	fp = fopen("phone_book.txt", "r");
	if (fp == NULL) {
		printf("Error openning file\n");
		return;

	}
	char line[300];
	int imp = 0;
	while (fgets(line, 300, fp)!=NULL) {
		line[strcspn(line, "\n")] = 0;
		char* name = strtok(line, ",");
		char* phone = strtok(NULL, ",");
		char* email = strtok(NULL, ",");
		if (name != NULL && phone != NULL && email != NULL) {
			insert(pb, name, phone, email);
			imp++;
		}
		
	}
	printf("Imported %d contacts\n", imp);
	fclose(fp);

}
void genereta_test_data(struct Hash* pb, int size) {
	char name[50], phone[15], email[30];
	for (int i = 0; i < size; i++) {
		sprintf(name, "Person%d", i+1);
		sprintf(phone, "555-%04d", i);
		sprintf(email, "person%d@test.com", i);
		insert(pb, name, phone, email);
	}
	printf("Generated[%d] contacts successfully!\n", size);

}
void search_pre(struct Hash* pb,const char* prefix) {
	int n = strlen(prefix);
	printf("Searching for names starting with '%s'\n", prefix);
	int found = 0;
	for (int i = 0; i < pb->size; i++) {
		struct Contact* cur = pb->table[i];
		while (cur != NULL) {
			if (strncmp(cur->name, prefix,n) == 0) {
				found++;
				printf("%s %s %s\n", cur->name, cur->phone, cur->email);
				
			}
			cur = cur->next;
		}
	}
	printf("Found [%d] matches\n", found);

}
void v(struct Hash* pb) {
	printf("===== TABLE DISTRIBUTION =====\n");
	for (int i = 0; i < pb->size; i++) {
		struct Contact* cur = pb->table[i];
		int l = 0;
		while (cur != NULL) {
			l++;
			cur = cur->next;
		}
		printf("[%02d] ", i);
		if (l == 0) {
			printf(". (0)\n");

		}
		else {
			for (int j = 0; j < l; j++) {
				printf("*");
			}
			printf("(%d)\n", l);
		}

	}
	printf("==============================\n");
}
void free1(struct Hash* pb) {
    for (int i = 0; i < pb->size; i++) {
        struct Contact* cur = pb->table[i];
        while (cur != NULL) {
			struct Contact* temp = cur;
            cur= cur->next;
            free(temp);
        }
    }
    free(pb->table);
    free(pb);
    printf("Memory freed successfully!\n");
}
int pivot(struct Contact* sarr[], int l, int h) {
	struct Contact* pivot = sarr[h];
	int i = l - 1;
	for (int j = l; j < h ; j++) {
		if (strcmp(sarr[j]->name, pivot->name) < 0) {
			i++;
			struct Contact* temp = sarr[i];
			sarr[i] = sarr[j];
			sarr[j] = temp;
		}
	}
	struct Contact* temp = sarr[i+1];
	sarr[i+1] = sarr[h];
	sarr[h] = temp;
	return i + 1;

}
void q_sort(struct Contact* sarr[], int l, int h) {
	if (l < h) {
		int pi = pivot(sarr, l, h);
		q_sort(sarr,l,pi - 1);
		q_sort(sarr,pi+1,h);


	}
}
void print_sort(struct Hash* pb) {
	if (pb->count == 0) {
		return;
	}
	struct Contact* sarr[sizeof(pb->count)];
	int idx=0;
	for (int i = 0; i < pb->size; i++) {
		struct Contact* cur = pb->table[i];
		while (cur != NULL) {
			sarr[idx] = cur;
			idx++;
			cur = cur->next;

		}
	}
	q_sort(sarr, 0, (pb->count) - 1);
	printf("Sorted database\n");
	for (int i = 0; i < pb->count; i++) {
		printf("%s %s %s\n",sarr[i]->name, sarr[i]->phone, sarr[i]->email);

	}

}
int main() {
	struct Hash* pb = create(500);  
	int choice;
	char name[50];
	char phone[15];
	char email[30];
	char prefix[20];
	int size;

	while (1) {
		show_menu(pb->count);
		scanf_s("%d", &choice);
		getchar(); 

		switch (choice) {
		case 1:
			printf("Enter name: ");
			gets_s(name, 50);
			

			printf("Enter phone: ");
			gets_s(phone, 15);
			

			printf("Enter email: ");
			gets_s(email, 30);
			

			insert(pb, name, phone, email);
			printf("Contact added succesufully\n");
			break;
			
			
		case 2:
			printf("Enter name to search: ");
			gets_s(name, 50);
			

			struct Contact* result = search(pb, name);
			if (result != NULL) {
				printf("\n===== CONTACT FOUND =====\n");
				printf("Name:  %s\n", result->name);
				printf("Phone: %s\n", result->phone);
				printf("Email: %s\n", result->email);
				printf("=========================\n");
			}
			else {
				printf("Contact '%s' not found!\n", name);
			}
			break;
			

		case 3:
			printf("Enter name to delete: ");
			gets_s(name, 50);
			

			del(pb, name);
			break;

		case 4:
			if (pb->count == 0) {
				printf("\nNo contacts yet!\n");
			}
			else {
				print_sort(pb);
			}
			break;

		case 5:
			stat(pb);
			break;

		case 6:
			
			export_to_file(pb);
			break;

		case 7:
			
			load_data(pb);
			break;

		case 8:
			printf("How many contacts to generate? ");
			scanf_s("%d", &size);
			getchar();
			if (size <= 0) {
				printf("Invalid number!\n");
				break;
			}
			genereta_test_data(pb, size);
			


			
			
			break;

		case 9:
			printf("Enter prefix to search: ");
			gets_s(prefix,20);
			search_pre(pb, prefix);


			
			
			break;

		case 0:
			printf("\nGoodbye!\n");
			free1(pb);
			return 0;
		case 10:
			v(pb);
			break;
		default:
			printf("Invalid choice!\n");
		}
	}

	return 0;
}