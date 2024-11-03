#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definisi struktur pasien
typedef struct Pasien {
    int id;
    char nama[100];
    struct Pasien* next;
} Pasien;

Pasien* head = NULL;
Pasien* tail = NULL;

// Fungsi untuk membuat pasien baru
Pasien* buatPasien(int id, char* nama) {
    Pasien* pasienBaru = (Pasien*) malloc(sizeof(Pasien));
    pasienBaru->id = id;
    strcpy(pasienBaru->nama, nama);
    pasienBaru->next = NULL;
    return pasienBaru;
}

// Fungsi untuk menambahkan pasien ke antrian
void tambahPasien(int id, char* nama) {
    Pasien* pasienBaru = buatPasien(id, nama);
    if (head == NULL) {
        head = pasienBaru;
        tail = pasienBaru;
        tail->next = head; // Circular
    } else {
        tail->next = pasienBaru;
        tail = pasienBaru;
        tail->next = head; // Membuat circular
    }
    printf("Pasien dengan ID %d dan nama %s telah ditambahkan ke antrian.\n", id, nama);
}

// Fungsi untuk melayani pasien
void layaniPasien() {
    if (head == NULL) {
        printf("Antrian kosong. Tidak ada pasien yang bisa dilayani.\n");
        return;
    }

    Pasien* pasienDilayani = head;
    printf("Melayani pasien ID: %d, Nama: %s\n", pasienDilayani->id, pasienDilayani->nama);

    // Memperbarui head ke pasien berikutnya
    if (head == tail) {
        // Jika hanya ada satu pasien dalam antrian
        free(head);
        head = NULL;
        tail = NULL;
    } else {
        head = head->next;
        tail->next = head;
        free(pasienDilayani);
    }
}

// Fungsi untuk menghapus pasien dari antrian berdasarkan ID
void hapusPasien(int id) {
    if (head == NULL) {
        printf("Antrian kosong. Tidak ada pasien yang bisa dihapus.\n");
        return;
    }

    Pasien* current = head;
    Pasien* prev = tail;

    // Jika pasien yang ingin dihapus adalah pasien pertama
    if (current->id == id) {
        if (head == tail) {
            free(head);
            head = NULL;
            tail = NULL;
        } else {
            head = head->next;
            tail->next = head;
            free(current);
        }
        printf("Pasien dengan ID %d telah dihapus dari antrian.\n", id);
        return;
    }

    // Mencari pasien di antrian
    do {
        if (current->id == id) {
            prev->next = current->next;
            if (current == tail) {
                tail = prev;
            }
            free(current);
            printf("Pasien dengan ID %d telah dihapus dari antrian.\n", id);
            return;
        }
        prev = current;
        current = current->next;
    } while (current != head);

    printf("Pasien dengan ID %d tidak ditemukan dalam antrian.\n", id);
}

// Fungsi untuk menampilkan semua pasien dalam antrian
void tampilkanAntrian() {
    if (head == NULL) {
        printf("Antrian kosong.\n");
        return;
    }

    Pasien* temp = head;
    printf("Daftar pasien dalam antrian:\n");
    do {
        printf("ID: %d, Nama: %s\n", temp->id, temp->nama);
        temp = temp->next;
    } while (temp != head);
}

// Fungsi utama
int main() {
    int pilihan, id;
    char nama[100];

    while (1) {
        printf("\n=== Sistem Manajemen Antrian Pasien ===\n");
        printf("1. Tambah Pasien\n");
        printf("2. Layani Pasien\n");
        printf("3. Hapus Pasien\n");
        printf("4. Tampilkan Daftar Pasien\n");
        printf("5. Keluar\n");
        printf("Pilih menu: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                printf("Masukkan ID Pasien: ");
                scanf("%d", &id);
                printf("Masukkan Nama Pasien: ");
                scanf(" %[^\n]%*c", nama);
                tambahPasien(id, nama);
                break;
            case 2:
                layaniPasien();
                break;
            case 3:
                printf("Masukkan ID Pasien yang ingin dihapus: ");
                scanf("%d", &id);
                hapusPasien(id);
                break;
            case 4:
                tampilkanAntrian();
                break;
            case 5:
                printf("Keluar dari program.\n");
                exit(0);
            default:
                printf("Pilihan tidak valid.\n");
        }
    }

    return 0;
}
