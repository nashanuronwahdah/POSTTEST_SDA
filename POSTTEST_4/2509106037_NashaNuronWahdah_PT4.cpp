#include <iostream>
#include <string>
using namespace std;

const int MAX = 100;

struct Hewan {
    int id;
    string nama;
    string jenis;
    double harga;
    Hewan* next;
};

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

void tambahData(Hewan* arr, int& n) {
    cout << "\nMasukkan ID: "; cin >> arr[n].id;
    cin.ignore(10000, '\n');
    cout << "Masukkan Nama: "; getline(cin, arr[n].nama);
    cout << "Masukkan Jenis: "; getline(cin, arr[n].jenis);
    cout << "Masukkan Harga: "; cin >> arr[n].harga;
    arr[n].next = nullptr;
    cin.ignore(10000, '\n');
    n++;
}

void tukarData(Hewan* a, Hewan* b) {
    int tempId = a->id; 
    a->id = b->id; 
    b->id = tempId;
    
    string tempNama = a->nama; 
    a->nama = b->nama; 
    b->nama = tempNama;
    
    string tempJenis = a->jenis; 
    a->jenis = b->jenis; 
    b->jenis = tempJenis;
    
    double tempHarga = a->harga; 
    a->harga = b->harga; 
    b->harga = tempHarga;
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
    if (fib1 && offset + 1 < n && arr[offset + 1].id == key) return offset + 1;
    return -1;
}

void bubbleSortNama(Hewan* arr, int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if ((arr+j)->nama > (arr+j+1)->nama) {
                tukarData(arr+j, arr+j+1);
            }
        }
    }
}

void selectionSortHarga(Hewan* arr, int n) {
    for (int i = 0; i < n-1; i++) {
        int minIdx = i;
        for (int j = i+1; j < n; j++) {
            if ((arr+j)->harga < (arr+minIdx)->harga) minIdx = j;
        }
        if (minIdx != i) {
            tukarData(arr+i, arr+minIdx);
        }
    }
}

struct Queue {
    Hewan* front = nullptr;
    Hewan* rear = nullptr;
};

bool isEmptyQueue(Queue* q) { return q->front == nullptr; }

void enqueue(Queue* q, Hewan h) {
    Hewan* curr = q->front;
    while (curr != nullptr) {
        if (curr->id == h.id) {
            cout << "Hewan " << h.nama << " (ID " << h.id << ") sudah ada di antrian.\n";
            return;
        }
        curr = curr->next;
    }

    Hewan* newNode = new Hewan;
    newNode->id = h.id;
    newNode->nama = h.nama;
    newNode->jenis = h.jenis;
    newNode->harga = h.harga;
    newNode->next = nullptr;

    if (isEmptyQueue(q)) {
        q->front = newNode;
        q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
    cout << "Hewan " << h.nama << " masuk antrian.\n";
}

Hewan dequeue(Queue* q) {
    Hewan kosong; kosong.id = -1; kosong.nama = ""; kosong.jenis = ""; kosong.harga = 0; kosong.next = nullptr;
    if (isEmptyQueue(q)) { 
        cout << "Antrian kosong (Kondisi Underflow)!\n"; 
        return kosong; 
    }
    
    Hewan* temp = q->front;
    Hewan h = *temp;
    
    q->front = q->front->next;
    if (q->front == nullptr) {
        q->rear = nullptr;
    }
    
    delete temp;
    cout << "Memanggil pasien: " << h.nama << " (ID " << h.id << ")\n";
    return h;
}

void tampilAntrian(Queue* q) {
    if (isEmptyQueue(q)) { cout << "Antrian kosong.\n"; return; }
    cout << "\n=== Antrian Pasien ===\n";
    Hewan* curr = q->front;
    while (curr != nullptr) {
        cout << "ID: " << curr->id << " | Nama: " << curr->nama << endl;
        curr = curr->next;
    }
}

Hewan peekQueue(Queue* q) {
    Hewan kosong; kosong.id = -1; kosong.nama = ""; kosong.jenis = ""; kosong.harga = 0; kosong.next = nullptr;
    if (isEmptyQueue(q)) { 
        cout << "Antrian kosong (Kondisi Underflow)!\n"; 
        return kosong; 
    }
    return *(q->front);
}

struct Stack {
    Hewan* top = nullptr;
};

bool isEmptyStack(Stack* s) { return s->top == nullptr; }

void push(Stack* s, Hewan h) {
    Hewan* newNode = new Hewan;
    newNode->id = h.id;
    newNode->nama = h.nama;
    newNode->jenis = h.jenis;
    newNode->harga = h.harga;
    newNode->next = s->top;
    
    s->top = newNode;
    cout << "Riwayat ditambahkan: " << h.nama << endl;
}

void pop(Stack* s) {
    if (isEmptyStack(s)) { 
        cout << "Riwayat kosong (Kondisi Underflow)!\n"; 
        return; 
    }
    
    cout << "Yakin ingin menghapus riwayat terakhir (" << s->top->nama << ")? (Y/N): ";
    char jawaban; cin >> jawaban;
    cin.ignore(10000, '\n');
    
    if (jawaban == 'Y' || jawaban == 'y') {
        cout << "Menghapus riwayat: " << s->top->nama << endl;
        Hewan* temp = s->top;
        s->top = s->top->next;
        delete temp;
    } else {
        cout << "Pembatalan penghapusan riwayat.\n";
    }
}

void tampilRiwayat(Stack* s) {
    if (isEmptyStack(s)) { cout << "Riwayat kosong.\n"; return; }
    cout << "\n=== Riwayat Tindakan ===\n";
    Hewan* curr = s->top;
    while (curr != nullptr) {
        cout << "ID: " << curr->id << " | Nama: " << curr->nama << endl;
        curr = curr->next;
    }
}

Hewan peekStack(Stack* s) {
    Hewan kosong; kosong.id = -1; kosong.nama = ""; kosong.jenis = ""; kosong.harga = 0; kosong.next = nullptr;
    if (isEmptyStack(s)) { 
        cout << "Riwayat kosong (Kondisi Underflow)!\n"; 
        return kosong; 
    }
    return *(s->top);
}

int main() {
    Hewan daftar[MAX];
    int n = 0;
    int pilihan;
    Queue antrian;
    Stack riwayat;

    daftar[n++] = {101, "Milo", "Kucing Persia", 1500000, nullptr};
    daftar[n++] = {102, "Bobby", "Anjing Bulldog", 2500000, nullptr};
    daftar[n++] = {103, "Coco", "Burung Parrot", 1200000, nullptr};
    daftar[n++] = {104, "Snowy", "Kelinci Anggora", 800000, nullptr};
    daftar[n++] = {105, "Luna", "Kucing Anggora", 2000000, nullptr};

    do {
        cout << "\n=== Menu Pawcare Petshop ===\n";
        cout << "1. Tampil semua data\n";
        cout << "2. Tambah data hewan\n";
        cout << "3. Cari nama (Linear Search)\n";
        cout << "4. Cari ID (Fibonacci Search)\n";
        cout << "5. Urutkan nama (Bubble Sort)\n";
        cout << "6. Urutkan harga (Selection Sort)\n";
        cout << "7. Enqueue (Tambah ke Antrian)\n";
        cout << "8. Dequeue (Panggil Pasien)\n";
        cout << "9. Push Riwayat\n";
        cout << "10. Pop Riwayat\n";
        cout << "11. Peek (Antrian & Riwayat)\n";
        cout << "12. Tampil semua antrian\n";
        cout << "13. Tampil semua riwayat\n";
        cout << "0. Keluar\n";
        cout << "Pilihan: "; cin >> pilihan;

        if (pilihan == 1) tampilData(daftar, n);
        else if (pilihan == 2) tambahData(daftar, n);
        else if (pilihan == 3) {
            cin.ignore(10000, '\n');
            string key; cout << "Masukkan nama: "; getline(cin, key);
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
        else if (pilihan == 7) {
            int idx; cout << "Masukkan indeks hewan (0 - " << n-1 << "): "; cin >> idx;
            if (idx >= 0 && idx < n) enqueue(&antrian, daftar[idx]);
            else cout << "Indeks tidak valid.\n";
        }
        else if (pilihan == 8) {
            Hewan h = dequeue(&antrian);
            if (h.id != -1) push(&riwayat, h);
        }
        else if (pilihan == 9) {
            int idx; cout << "Masukkan indeks hewan (0 - " << n-1 << "): "; cin >> idx;
            if (idx >= 0 && idx < n) push(&riwayat, daftar[idx]);
            else cout << "Indeks tidak valid.\n";
        }
        else if (pilihan == 10) pop(&riwayat);
        else if (pilihan == 11) {
            cout << "\n--- Cek Peek ---" << endl;
            Hewan q = peekQueue(&antrian);
            Hewan s = peekStack(&riwayat);
            if (q.id != -1) cout << "Peek Antrian: " << q.nama << endl;
            if (s.id != -1) cout << "Peek Riwayat: " << s.nama << endl;
        }
        else if (pilihan == 12) tampilAntrian(&antrian);
        else if (pilihan == 13) tampilRiwayat(&riwayat);
        else if (pilihan != 0) cout << "Pilihan tidak dikenal.\n";
    } while (pilihan != 0);

    return 0;
}