#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int data[100];
    int count;
    int top;
} stack;

void createStack(stack *s);
int isEmpty(stack *s);
int isFull(stack *s);
int stackCount(stack *s);
void push(stack *s, int data, int *success);
void pop(stack *s, int *dataOut, int *success);
int stackTop(stack *s, int *dataOut, int *success);
void display(stack *s);
void destroyStack(stack *s);

int main() {
    stack myStack;
    int data;
    char pilihan;
    int success;

    createStack(&myStack);

    do {
        system("cls");
        printf("Pilih operasi:\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Stack Top\n");
        printf("4. Display\n");
        printf("5. Jumlah Elemen\n");
        printf("6. Cek Full Stack\n");
        printf("7. Destroy Stack\n");
        printf("q. Keluar\n");
        printf("MASUKKAN PILIHAN: ");
        scanf(" %c", &pilihan);

        switch (pilihan) {
            case '1':
                if (!isFull(&myStack)) {
                    printf("Masukkan data: ");
                    scanf("%d", &data);
                    push(&myStack, data, &success);
                    if (success) {
                        printf("Data %d berhasil ditambahkan ke stack.\n", data);
                    }
                } else {
                    printf("Stack penuh\n");
                }
                break;

            case '2':
                pop(&myStack, &data, &success);
                if (success) {
                    printf("Data %d dihapus dari stack.\n", data);
                } else {
                    printf("Stack kosong\n");
                }
                break;

            case '3':
                if (stackTop(&myStack, &data, &success)) {
                    printf("Elemen teratas di stack: %d\n", data);
                } else {
                    printf("Stack kosong\n");
                }
                break;

            case '4':
                display(&myStack);
                break;

            case '5':
                printf("Jumlah elemen dalam stack: %d\n", stackCount(&myStack));
                break;

            case '6':
                if (isFull(&myStack)) {
                    printf("Stack penuh.\n");
                } else {
                    printf("Stack tidak penuh.\n");
                }
                break;

            case '7':
                destroyStack(&myStack);
                printf("Stack telah dihapus.\n");
                break;

            case 'q':
                printf("Keluar dari program.\n");
                break;

            default:
                printf("Pilihan tidak valid, silakan coba lagi.\n");
                break;
        }

        if (pilihan != 'q') {
            printf("Tekan enter untuk melanjutkan...\n");
            getchar();
            getchar();
        }

    } while (pilihan != 'q');

    return 0;
}

void createStack(stack *s) {
    s->count = 0;
    s->top = -1;
}

int isEmpty(stack *s) {
    return s->count == 0;
}

int isFull(stack *s) {
    return s->count == 100;
}

int stackCount(stack *s) {
    return s->count;
}

void push(stack *s, int data, int *success) {
    if (isFull(s)) {
        *success = 0;
    } else {
        s->top++;
        s->data[s->top] = data;
        s->count++;
        *success = 1;
    }
}

void pop(stack *s, int *dataOut, int *success) {
    if (isEmpty(s)) {
        *success = 0;
    } else {
        *dataOut = s->data[s->top];
        s->top--;
        s->count--;
        *success = 1;
    }
}

int stackTop(stack *s, int *dataOut, int *success) {
    if (isEmpty(s)) {
        *success = 0;
        return 0;
    } else {
        *dataOut = s->data[s->top];
        *success = 1;
        return 1;
    }
}

void display(stack *s) {
    if (isEmpty(s)) {
        printf("Stack kosong.\n");
    } else {
        printf("Isi stack:\n");
        for (int i = s->top; i >= 0; i--) {
            printf("%d\n", s->data[i]);
        }
    }
    getchar();
}

void destroyStack(stack *s) {
    s->count = 0;
    s->top = -1;
}
