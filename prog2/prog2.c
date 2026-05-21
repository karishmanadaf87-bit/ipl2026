#include <stdio.h>
#include <stdlib.h>

#define MAX 100

/* Structure Definition */
struct Student {
    int id;
    char name[30];
    float marks;
};

/* Function Prototypes */
void writeRecords(struct Student s[], int n, char filename[]);
int createSeekArray(FILE *fp, long pos[]);
void displayRecord(FILE *fp, long position);

int main() {
    struct Student s[3] = {
        {101, "Rahul", 85.5},
        {102, "Anita", 90.0},
        {103, "Kiran", 78.5}
    };

    long positions[MAX];
    int count, i;

    /* Store records in ASCII format */
    writeRecords(s, 3, "student.txt");

    FILE *fp = fopen("student.txt", "r");

    if (fp == NULL) {
        printf("File cannot be opened\n");
        return 1;
    }

    /* Create array of seek positions */
    count = createSeekArray(fp, positions);

    printf("Seek Positions:\n");
    for (i = 0; i < count; i++) {
        printf("Record %d starts at position %ld\n", i + 1, positions[i]);
    }

    /* Display a record using seek position */
    printf("\nDisplaying Record at Position %ld:\n", positions[1]);
    displayRecord(fp, positions[1]);

    fclose(fp);

    return 0;
}

/* Function to write array of structures into file */
void writeRecords(struct Student s[], int n, char filename[]) {
    FILE *fp;
    int i;

    fp = fopen(filename, "w");

    if (fp == NULL) {
        printf("Cannot create file\n");
        exit(1);
    }

    for (i = 0; i < n; i++) {
        fprintf(fp, "%d %s %.2f\n",
                s[i].id,
                s[i].name,
                s[i].marks);
    }

    fclose(fp);
}

/* Function to create seek positions array */
int createSeekArray(FILE *fp, long pos[]) {
    int count = 0;
    char line[100];

    rewind(fp);

    while (!feof(fp)) {

        pos[count] = ftell(fp);

        if (fgets(line, sizeof(line), fp) != NULL) {
            count++;
        }
    }

    return count;
}

/* Function to display record using seek position */
void displayRecord(FILE *fp, long position) {
    struct Student s;

    fseek(fp, position, SEEK_SET);

    fscanf(fp, "%d %s %f",
           &s.id,
           s.name,
           &s.marks);

    printf("ID    : %d\n", s.id);
    printf("Name  : %s\n", s.name);
    printf("Marks : %.2f\n", s.marks);
}