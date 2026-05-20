#include <stdio.h>
#include <stdlib.h>

struct Student {
    int id;
    char name[50];
    float marks;
};

void addRecords(char *filename, int n) {
    FILE *fp;
    struct Student s;

    fp = fopen(filename, "wb");

    if (fp == NULL) {
        printf("File error\n");
        return;
    }

    for(int i = 0; i < n; i++) {
        printf("\nEnter ID: ");
        scanf("%d", &s.id);

        printf("Enter Name: ");
        scanf("%s", s.name);

        printf("Enter Marks: ");
        scanf("%f", &s.marks);

        fwrite(&s, sizeof(struct Student), 1, fp);
    }

    fclose(fp);
}

void displayMthRecord(char *filename, int m) {
    FILE *fp;
    struct Student s;

    fp = fopen(filename, "rb");

    if(fp == NULL) {
        printf("File error\n");
        return;
    }

    fseek(fp, (m - 1) * sizeof(struct Student), SEEK_SET);

    fread(&s, sizeof(struct Student), 1, fp);

    printf("\nMth Record:\n");
    printf("ID: %d\n", s.id);
    printf("Name: %s\n", s.name);
    printf("Marks: %.2f\n", s.marks);

    fclose(fp);
}

void deleteRecord(char *filename, int delId) {
    FILE *fp, *temp;
    struct Student s;

    fp = fopen(filename, "rb");
    temp = fopen("temp.dat", "wb");

    if(fp == NULL || temp == NULL) {
        printf("File error\n");
        return;
    }

    while(fread(&s, sizeof(struct Student), 1, fp)) {
        if(s.id != delId) {
            fwrite(&s, sizeof(struct Student), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    remove(filename);
    rename("temp.dat", filename);

    printf("Record deleted successfully\n");
}

int main() {
    int n, m, delId;

    printf("Enter number of records: ");
    scanf("%d", &n);

    addRecords("student.dat", n);

    printf("\nEnter mth record to display: ");
    scanf("%d", &m);

    displayMthRecord("student.dat", m);

    printf("\nEnter ID to delete: ");
    scanf("%d", &delId);

    deleteRecord("student.dat", delId);

    return 0;
}