#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct mahasiswa {
    char nama[30];
    char jeniskelamin[3];
    struct mahasiswa* next;
} mahasiswa;

mahasiswa* head = NULL;
mahasiswa* tail = NULL;

mahasiswa* buatmahasiswa(char* nama, char* jeniskelamin){
    mahasiswa* mahasiswaBaru = (mahasiswa*) malloc(sizeof(mahasiswa));
    strcpy(mahasiswaBaru->nama, nama);
    strcpy(mahasiswaBaru->jeniskelamin, jeniskelamin);
    mahasiswaBaru->next = NULL;
    return mahasiswaBaru;
}

void tambahmahasiswa(char* nama, char* jeniskelamin){
    mahasiswa* mahasiswaBaru = buatmahasiswa(nama, jeniskelamin);
    int total = 0;

    if(total <= 20){
        if(head == NULL){
        head = mahasiswaBaru;
        tail = mahasiswaBaru;
        tail->next = head;
    }else{
        tail->next = mahasiswaBaru;
        tail = mahasiswaBaru;
        tail->next = head;
        }
        printf("mahasiswa telah ditambahkan\n", nama, jeniskelamin);
        total++;
    }
    printf("lingkaran sudah penuh");
}

void hapusmahasiswa(char* nama){
    if (head == NULL){
        printf("tidak ada mahasiswa\n", nama);
        return;
    }
    mahasiswa* pCur = head;
    mahasiswa* pPre = tail;

    if (pPre->nama == nama){
        if (head == tail){
            free(head);
            head = NULL;
            tail = NULL;
        }else{
            head = head->next;
            tail->next = head;
            free(pCur);
        }
        printf("mahasiswa telah keluar lingkaran\n", nama);
        return;
    }

    do{
        if (pCur->nama == nama){
            pPre->next = pCur->next;
            if (pCur == tail){
                tail = pPre;
            }
            free(pCur);
            printf("mahasiswa telah dikeluarkan dari lingkaran\n", nama);
            return;
        }
        pPre = pCur;
        pCur = pCur->next;
    }while(pCur != head);

    printf("mahasiswa tidak ditemukan\n", nama);
}

void tampilkanlingkaran(){
    if (head == NULL){
        printf("api unggun kosong\n");
        return;
    }
    mahasiswa* temp = head;
    printf("daftar mahasiswa di api unggun: \n");
    do{
        printf("nama: %s, jenis kelamin: %s ->", temp->nama, temp->jeniskelamin);
        temp = temp->next;
    }while (temp != head);
}

int main() {
    int pilihan;
    char nama[40];
    char jeniskelamin[3];


    while (1) {
        system("cls");
        printf("\n=== Acara Api Unggun ===\n");
        printf("1. Tambah Mahasiswa\n");
        printf("2. Hapus Mahasiswa\n");
        printf("3. Tampilkan Lingkaran\n");
        printf("4. Keluar\n");
        printf("Pilih menu: ");
        scanf("%d", &pilihan);
        fflush(stdin);
        switch (pilihan) {
            case 1:
                printf("Masukkan Nama Mahasiswa: ");
                scanf("%s", nama);
                printf("Masukkan Jenis Kelamin (l/p): ");
                scanf("%s", jeniskelamin);
                tambahmahasiswa(nama, jeniskelamin);
                break;
            case 2:
                printf("Masukkan nama mahasiswa yang ingin keluar lingkaran: ");
                scanf("%s", nama);
                hapusmahasiswa(nama);
                break;
            case 3:
                tampilkanlingkaran();
                break;
            case 4:
                printf("Keluar dari program.\n");
                exit(0);
            default:
                printf("Pilihan tidak valid.\n");
        }
    }

    return 0;
}
