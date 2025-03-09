#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 建立学生信息结构体
struct Student {
    char name[20]; // 学生姓名
    int ID;        // 学号
    int age;       // 年龄
    int score;     // 成绩
    struct Student* next; // 指针域
};
typedef struct Student Student;

void displayMenu() {
    printf("-------学生信息管理系统----------\n");
    printf("*\t0.退出系统\t\t*\n");
    printf("*\t1.插入信息\t\t*\n");
    printf("*\t2.查找信息\t\t*\n");
    printf("*\t3.删除信息\t\t*\n");
    printf("*\t4.排序信息\t\t*\n");
    printf("*\t5.查看信息\t\t*\n");
    printf("*\t6.修改信息\t\t*\n");
    printf("*\t7.保存信息\t\t*\n");
    printf("*\t8.加载信息\t\t*\n");
    printf("---------------------------------\n\n");
    printf("请输入：");
}

Student* createList() {
    Student* head = (Student*)malloc(sizeof(Student));
    if (head == NULL) {
        printf("内存分配失败！\n");
        exit(1);
    }
    head->next = NULL;
    return head;
}

int isValidName(const char* name) {
    return strlen(name) > 0 && strlen(name) < 20;
}

int isValidAge(int age) {
    return age >= 0 && age <= 150;
}

int isValidScore(int score) {
    return score >= 0 && score <= 100;
}

Student* insertStudent(Student* head) {
    Student* p = head;
    while (p->next != NULL) {
        p = p->next;
    }
    Student* newStudent = (Student*)malloc(sizeof(Student));
    if (newStudent == NULL) {
        printf("内存分配失败！\n");
        return head;
    }
    printf("姓名：");
    scanf_s("%s", newStudent->name, 20);
    if (!isValidName(newStudent->name)) {
        printf("姓名输入有误！\n");
        free(newStudent);
        return head;
    }
    printf("学号：");
    scanf_s("%d", &newStudent->ID);
    printf("年龄：");
    scanf_s("%d", &newStudent->age);
    if (!isValidAge(newStudent->age)) {
        printf("年龄输入有误！\n");
        free(newStudent);
        return head;
    }
    printf("成绩：");
    scanf_s("%d", &newStudent->score);
    if (!isValidScore(newStudent->score)) {
        printf("成绩输入有误！\n");
        free(newStudent);
        return head;
    }
    p->next = newStudent;
    newStudent->next = NULL;
    printf("插入成功！\n");
    return head;
}

void searchStudent(Student* head) {
    int id;
    printf("请输入学生学号：");
    scanf_s("%d", &id);
    Student* p = head->next;
    while (p != NULL) {
        if (p->ID == id) {
            printf("姓名：%s\n", p->name);
            printf("学号：%d\n", p->ID);
            printf("年龄：%d\n", p->age);
            printf("成绩：%d\n", p->score);
            return;
        }
        p = p->next;
    }
    printf("未找到该学生信息！\n");
}

void deleteStudent(Student* head) {
    int id;
    printf("请输入学生学号：");
    scanf_s("%d", &id);
    Student* p = head->next;
    Student* q = head;
    while (p != NULL) {
        if (p->ID == id) {
            q->next = p->next;
            free(p);
            printf("删除成功！\n");
            return;
        }
        q = p;
        p = p->next;
    }
    printf("删除失败！\n");
}

void sortStudents(Student* head) {
    if (head == NULL || head->next == NULL) {
        return;
    }

    Student* sorted = NULL;

    while (head->next != NULL) {
        Student* current = head->next;
        head->next = current->next;

        if (sorted == NULL || sorted->score < current->score) {
            current->next = sorted;
            sorted = current;
        } else {
            Student* temp = sorted;
            while (temp->next != NULL && temp->next->score >= current->score) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
    }

    head->next = sorted;
    printf("排序成功！\n");
}

void printStudents(Student* head) {
    printf("学生信息如下：\n");
    printf("姓名\t学号\t年龄\t成绩\n");
    for (Student* p = head->next; p != NULL; p = p->next) {
        printf("%s\t%d\t%d\t%d\n", p->name, p->ID, p->age, p->score);
    }
}

void modifyStudent(Student* head) {
    int id;
    printf("请输入要修改的学生学号：");
    scanf_s("%d", &id);
    Student* p = head->next;
    while (p != NULL) {
        if (p->ID == id) {
            printf("找到学生信息：\n");
            printf("姓名：%s\n", p->name);
            printf("学号：%d\n", p->ID);
            printf("年龄：%d\n", p->age);
            printf("成绩：%d\n", p->score);
            
            printf("请输入新的姓名：");
            scanf_s("%s", p->name, 20);
            if (!isValidName(p->name)) {
                printf("姓名输入有误！\n");
                return;
            }
            printf("请输入新的年龄：");
            scanf_s("%d", &p->age);
            if (!isValidAge(p->age)) {
                printf("年龄输入有误！\n");
                return;
            }
            printf("请输入新的成绩：");
            scanf_s("%d", &p->score);
            if (!isValidScore(p->score)) {
                printf("成绩输入有误！\n");
                return;
            }
            printf("修改成功！\n");
            return;
        }
        p = p->next;
    }
    printf("未找到该学生信息！\n");
}

void saveStudents(Student* head, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("无法打开文件！\n");
        return;
    }
    Student* p = head->next;
    while (p != NULL) {
        fprintf(file, "%s %d %d %d\n", p->name, p->ID, p->age, p->score);
        p = p->next;
    }
    fclose(file);
    printf("保存成功！\n");
}

Student* loadStudents(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("无法打开文件！\n");
        return NULL;
    }
    Student* head = createList();
    Student* p = head;
    while (!feof(file)) {
        Student* newStudent = (Student*)malloc(sizeof(Student));
        if (newStudent == NULL) {
            printf("内存分配失败！\n");
            fclose(file);
            return head;
        }
        if (fscanf(file, "%s %d %d %d", newStudent->name, &newStudent->ID, &newStudent->age, &newStudent->score) != 4) {
            printf("文件格式错误或数据缺失！\n");
            free(newStudent);
            break;
        }
        p->next = newStudent;
        newStudent->next = NULL;
        p = newStudent;
    }
    fclose(file);
    printf("加载成功！\n");
    return head;
}

void freeList(Student* head) {
    Student* p = head;
    while (p != NULL) {
        Student* temp = p;
        p = p->next;
        free(temp);
    }
}

int main() {
    Student* head = createList();
    while (1) {
        system("cls");
        displayMenu();
        char choice;
        scanf_s(" %c", &choice, 1);
        switch (choice) {
            case '0':
                freeList(head);
                return 0;
            case '1':
                head = insertStudent(head);
                _sleep(2000);
                break;
            case '2':
                searchStudent(head);
                _sleep(2000);
                break;
            case '3':
                deleteStudent(head);
                _sleep(2000);
                break;
            case '4':
                sortStudents(head);
                _sleep(2000);
                break;
            case '5':
                printStudents(head);
                system("pause");
                break;
            case '6':
                modifyStudent(head);
                _sleep(2000);
                break;
            case '7':
                saveStudents(head, "students.txt");
                _sleep(2000);
                break;
            case '8':
                freeList(head);
                head = loadStudents("students.txt");
                _sleep(2000);
                break;
            default:
                printf("输入有误！\n");
                _sleep(2000);
                break;
        }
    }
    return 0;
}