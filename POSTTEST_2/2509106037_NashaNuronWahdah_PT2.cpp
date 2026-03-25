#include <iostream>
#include <string>
using namespace std;

struct Hewan {
    int id;
    string nama;
    string jenis;
    double harga;
};

// Pointer Aritmatika
void tampilData(Hewan* arr, int n) {
    cout << "\n=== Data Hewan Pawcare Petshop ===\n";
    for (int i = 0; i < n; i++) {
        Hewan* p = arr + i;
        cout << "ID: " << p->id
             << " | Nama: " << p->nama
             << " | Jenis: " << p->jenis
             << " | Harga: Rp" << p->harga << endl;
    }
}

// Tambah Data
void tambahData(Hewan* arr, int& n) {
    cout << "\nMasukkan ID: "; cin >> arr[n].id;
    cout << "Masukkan Nama: "; cin.ignore(); getline(cin, arr[n].nama);
    cout << "Masukkan Jenis: "; getline(cin, arr[n].jenis);
    cout << "Masukkan Harga: "; cin >> arr[n].harga;
    n++;
}

void cariNamaLinear(Hewan* arr, int n, string key) {
    cout << "\nProses Linear Search:\n";
    for (int i = 0; i < n; i++) {
        cout << "Cek indeks " << i << " → " << arr[i].nama << endl;
        if (arr[i].nama == key) {
            cout << "Ditemukan di indeks " << i << endl;
            return;
        }
    }
    cout << "Nama tidak ditemukan.\n";
}

// Fibonacci Search
int fibonacciSearch(Hewan* arr, int n, int key) {
    int fib2 = 0, fib1 = 1, fib = fib2 + fib1;
    while (fib < n) {
        fib2 = fib1;
        fib1 = fib;
        fib = fib2 + fib1;
    }
    int offset = -1;
    while (fib > 1) {
        int i = offset + fib2;
        if (i >= n) i = n - 1; 

        if (arr[i].id < key) {
            fib = fib1;
            fib1 = fib2;
            fib2 = fib - fib1;
            offset = i;
        } else if (arr[i].id > key) {
            fib = fib2;
            fib1 = fib1 - fib2;
            fib2 = fib - fib1;
        } else return i;
    }
    if (fib1 && arr[offset + 1].id == key) return offset + 1;
    return -1;
}

// Bubble Sort
void bubbleSortNama(Hewan* arr, int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if ((arr+j)->nama > (arr+j+1)->nama) {
                Hewan* a = arr+j;
                Hewan* b = arr+j+1;
                Hewan temp = *a;
                *a = *b;
                *b = temp;
            }
        }
    }
}

// Selection Sort
void selectionSortHarga(Hewan* arr, int n) {
    for (int i = 0; i < n-1; i++) {
        int minIdx = i;
        for (int j = i+1; j < n; j++) {
            if ((arr+j)->harga < (arr+minIdx)->harga) {
                minIdx = j;
            }
        }
        Hewan* a = arr+i;
        Hewan* b = arr+minIdx;
        Hewan temp = *a;
        *a = *b;
        *b = temp;
    }
}

int main() {
    Hewan daftar[100];
    int n = 0;
    int pilihan;

    daftar[n++] = {101, "Milo", "Kucing Persia", 1500000};
    daftar[n++] = {102, "Bobby", "Anjing Bulldog", 2500000};
    daftar[n++] = {103, "Coco", "Burung Parrot", 1200000};
    daftar[n++] = {104, "Snowy", "Kelinci Anggora", 800000};
    daftar[n++] = {105, "Luna", "Kucing Anggora", 2000000};

    do {
        cout << "\n=== Menu Pawcare Petshop ===\n";
        cout << "1. Tampil semua data\n";
        cout << "2. Tambah data hewan\n";
        cout << "3. Cari nama (Linear Search)\n";
        cout << "4. Cari ID (Fibonacci Search)\n";
        cout << "5. Urutkan nama (Bubble Sort)\n";
        cout << "6. Urutkan harga (Selection Sort)\n";
        cout << "0. Keluar\n";
        cout << "Pilihan: "; cin >> pilihan;

        if (pilihan == 1) tampilData(daftar, n);
        else if (pilihan == 2) tambahData(daftar, n);
        else if (pilihan == 3) {
            string key; cout << "Masukkan nama: "; cin.ignore(); getline(cin, key);
            cariNamaLinear(daftar, n, key);
        }
        else if (pilihan == 4) {
            int key; cout << "Masukkan ID: "; cin >> key;
            int idx = fibonacciSearch(daftar, n, key);
            if (idx != -1) cout << "ID ditemukan di indeks " << idx << endl;
            else cout << "ID tidak ditemukan.\n";
        }
        else if (pilihan == 5) {
            bubbleSortNama(daftar, n);
            cout << "Data berhasil diurutkan berdasarkan nama.\n";
        }
        else if (pilihan == 6) {
            selectionSortHarga(daftar, n);
            cout << "Data berhasil diurutkan berdasarkan harga.\n";
        }
    } while (pilihan != 0);

    return 0;
}
