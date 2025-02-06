#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student
{
    char studentId[20];
    char name[50];
    float mathScore;
    float physicsScore;
    float chemistryScore;
    float averageScore;
    struct Student *next;
} Student;

Student *createStudent(const char *id, const char *name, float math, float physics, float chemistry);
void addStudent(Student **head);
void displayStudents(Student *head);
Student *searchStudent(Student *head, const char *id);
void deleteStudent(Student **head);
void sortStudents(Student **head, int ascending);
void freeList(Student **head);

int main()
{
    Student *head = NULL;
    int choice;

    do
    {
        printf("\n=== QUAN LY SINH VIEN ===\n");
        printf("1. Them sinh vien\n");
        printf("2. Hien thi danh sach\n");
        printf("3. Tim kiem sinh vien\n");
        printf("4. Xoa sinh vien\n");
        printf("5. Sap xep theo diem TB\n");
        printf("6. Thoat\n");
        printf("Chon chuc nang (1-6): ");
        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
        case 1:
            addStudent(&head);
            break;
        case 2:
            displayStudents(head);
            break;
        case 3:
        {
            char searchId[20];
            printf("Nhap ma sinh vien can tim: ");
            fgets(searchId, sizeof(searchId), stdin);
            searchId[strcspn(searchId, "\n")] = 0;
            Student *found = searchStudent(head, searchId);
            if (found)
            {
                printf("\nThong tin sinh vien tim thay:\n");
                printf("Ma SV: %s\n", found->studentId);
                printf("Ten: %s\n", found->name);
                printf("Diem TB: %.2f\n", found->averageScore);
            }
            break;
        }
        case 4:
            deleteStudent(&head);
            break;
        case 5:
        {
            int order;
            printf("Sap xep tang dan (1) hay giam dan (2)? ");
            scanf("%d", &order);
            sortStudents(&head, order == 1);
            printf("Da sap xep xong!\n");
            break;
        }
        case 6:
            printf("Tam biet!\n");
            break;
        default:
            printf("Lua chon khong hop le!\n");
        }
    } while (choice != 6);

    freeList(&head);
    return 0;
}

Student *createStudent(const char *id, const char *name, float math, float physics, float chemistry)
{
    Student *newStudent = (Student *)malloc(sizeof(Student));
    if (newStudent == NULL)
    {
        printf("Loi cap phat bo nho!\n");
        exit(1);
    }

    strcpy(newStudent->studentId, id);
    strcpy(newStudent->name, name);
    newStudent->mathScore = math;
    newStudent->physicsScore = physics;
    newStudent->chemistryScore = chemistry;
    newStudent->averageScore = (math + physics + chemistry) / 3.0;
    newStudent->next = NULL;

    return newStudent;
}

void addStudent(Student **head)
{
    char id[20], name[50];
    float math, physics, chemistry;

    printf("Nhap ma sinh vien: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = 0;

    printf("Nhap ten sinh vien: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;

    printf("Nhap diem Toan: ");
    scanf("%f", &math);
    printf("Nhap diem Ly: ");
    scanf("%f", &physics);
    printf("Nhap diem Hoa: ");
    scanf("%f", &chemistry);
    getchar();

    Student *newStudent = createStudent(id, name, math, physics, chemistry);

    if (*head == NULL)
    {
        *head = newStudent;
    }
    else
    {
        Student *current = *head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = newStudent;
    }
    printf("Da them sinh vien thanh cong!\n");
}

void displayStudents(Student *head)
{
    if (head == NULL)
    {
        printf("Danh sách sinh vien trong!\n");
        return;
    }

    Student *current = head;
    while (current != NULL)
    {
        printf("\nMa SV: %s\n", current->studentId);
        printf("Ten: %s\n", current->name);
        printf("Diem Toan: %.2f\n", current->mathScore);
        printf("Diem Ly: %.2f\n", current->physicsScore);
        printf("Diem Hoa: %.2f\n", current->chemistryScore);
        printf("Diem TB: %.2f\n", current->averageScore);
        printf("-------------------------\n");
        current = current->next;
    }
}

Student *searchStudent(Student *head, const char *id)
{
    Student *current = head;
    while (current != NULL)
    {
        if (strcmp(current->studentId, id) == 0)
        {
            return current;
        }
        current = current->next;
    }
    printf("Khong tim thay sinh vien!\n");
    return NULL;
}

void deleteStudent(Student **head)
{
    if (*head == NULL)
    {
        printf("Danh sach sinh vien trong!\n");
        return;
    }

    char id[20];
    printf("Nhap ma sinh vien can xoa: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = 0;

    Student *current = *head;
    Student *prev = NULL;

    if (current != NULL && strcmp(current->studentId, id) == 0)
    {
        *head = current->next;
        free(current);
        printf("Da xoa sinh vien thanh cong!\n");
        return;
    }

    while (current != NULL && strcmp(current->studentId, id) != 0)
    {
        prev = current;
        current = current->next;
    }

    if (current == NULL)
    {
        printf("Khong tim thay sinh vien!\n");
        return;
    }

    prev->next = current->next;
    free(current);
    printf("Da xoa sinh vien thanh cong!\n");
}

void sortStudents(Student **head, int ascending)
{
    if (*head == NULL || (*head)->next == NULL)
    {
        return;
    }

    int swapped;
    Student *ptr1;
    Student *lptr = NULL;

    do
    {
        swapped = 0;
        ptr1 = *head;

        while (ptr1->next != lptr)
        {
            if ((ascending && ptr1->averageScore > ptr1->next->averageScore) ||
                (!ascending && ptr1->averageScore < ptr1->next->averageScore))
            {
                char tempId[20];
                char tempName[50];
                float tempMath, tempPhysics, tempChemistry, tempAvg;

                strcpy(tempId, ptr1->studentId);
                strcpy(tempName, ptr1->name);
                tempMath = ptr1->mathScore;
                tempPhysics = ptr1->physicsScore;
                tempChemistry = ptr1->chemistryScore;
                tempAvg = ptr1->averageScore;

                strcpy(ptr1->studentId, ptr1->next->studentId);
                strcpy(ptr1->name, ptr1->next->name);
                ptr1->mathScore = ptr1->next->mathScore;
                ptr1->physicsScore = ptr1->next->physicsScore;
                ptr1->chemistryScore = ptr1->next->chemistryScore;
                ptr1->averageScore = ptr1->next->averageScore;

                strcpy(ptr1->next->studentId, tempId);
                strcpy(ptr1->next->name, tempName);
                ptr1->next->mathScore = tempMath;
                ptr1->next->physicsScore = tempPhysics;
                ptr1->next->chemistryScore = tempChemistry;
                ptr1->next->averageScore = tempAvg;

                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

void freeList(Student **head)
{
    Student *current = *head;
    Student *next;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }

    *head = NULL;
}