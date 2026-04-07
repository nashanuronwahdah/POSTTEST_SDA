#include <iostream>
#include <string>
using namespace std;

const int MAX = 100;

struct Hewan {
    int id;
    string nama;
    string jenis;
    double harga;
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
    cin.ignore(10000, '\n');
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
                Hewan temp = *(arr + j);
                *(arr + j) = *(arr + j + 1);
                *(arr + j + 1) = temp;
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
        Hewan temp = *(arr + i);
        *(arr + i) = *(arr + minIdx);
        *(arr + minIdx) = temp;
    }
}

struct Queue {
    Hewan data[MAX];
    int front = 0, rear = -1, count = 0;
};

bool isEmptyQueue(Queue* q) { return q->count == 0; }
bool isFullQueue(Queue* q) { return q->count == MAX; }

void enqueue(Queue* q, Hewan h) {
    if (isFullQueue(q)) { cout << "Antrian penuh!\n"; return; }
    for (int i = 0; i < q->count; i++) {
        Hewan* p = &q->data[(q->front + i) % MAX];
        if (p->id == h.id) {
            cout << "Hewan " << h.nama << " (ID " << h.id << ") sudah ada di antrian.\n";
            return;
        }
    }
    q->rear = (q->rear + 1) % MAX;
    q->data[q->rear] = h;
    q->count++;
    cout << "Hewan " << h.nama << " masuk antrian.\n";
}

void enqueueDarurat(Queue* q, Hewan h) {
    if (isFullQueue(q)) { cout << "Antrian penuh!\n"; return; }
    for (int i = 0; i < q->count; i++) {
        Hewan* p = &q->data[(q->front + i) % MAX];
        if (p->id == h.id) {
            cout << "Hewan " << h.nama << " (ID " << h.id << ") sudah ada di antrian.\n";
            return;
        }
    }
    q->front = (q->front - 1 + MAX) % MAX;
    q->data[q->front] = h;
    q->count++;
    if (q->rear == -1) q->rear = q->front;
    cout << "Hewan darurat " << h.nama << " langsung ditempatkan di depan antrian!\n";
}

Hewan dequeue(Queue* q) {
    Hewan kosong; kosong.id = -1; kosong.nama = ""; kosong.jenis = ""; kosong.harga = 0;
    if (isEmptyQueue(q)) { cout << "Antrian kosong!\n"; return kosong; }
    Hewan h = q->data[q->front];
    q->front = (q->front + 1) % MAX;
    q->count--;
    if (q->count == 0) { q->front = 0; q->rear = -1; }
    cout << "Memanggil pasien: " << h.nama << " (ID " << h.id << ")\n";
    return h;
}

void tampilAntrian(Queue* q) {
    if (isEmptyQueue(q)) { cout << "Antrian kosong.\n"; return; }
    cout << "\n=== Antrian Pasien ===\n";
    for (int i = 0; i < q->count; i++) {
        Hewan* p = &q->data[(q->front + i) % MAX];
        cout << "ID: " << p->id << " | Nama: " << p->nama << endl;
    }
}

Hewan peekQueue(Queue* q) {
    Hewan kosong; kosong.id = -1; kosong.nama = ""; kosong.jenis = ""; kosong.harga = 0;
    if (isEmptyQueue(q)) return kosong;
    return q->data[q->front];
}

struct Stack {
    Hewan data[MAX];
    int top = -1;
};

bool isEmptyStack(Stack* s) { return s->top == -1; }
bool isFullStack(Stack* s) { return s->top == MAX - 1; }

void push(Stack* s, Hewan h) {
    if (isFullStack(s)) { cout << "Riwayat penuh!\n"; return; }
    s->data[++s->top] = h;
    cout << "Riwayat ditambahkan: " << h.nama << endl;
}

void pop(Stack* s) {
    if (isEmptyStack(s)) { cout << "Riwayat kosong!\n"; return; }
    cout << "Yakin ingin menghapus riwayat terakhir (" << s->data[s->top].nama << ")? (Y/N): ";
    char jawaban; cin >> jawaban;
    cin.ignore(10000, '\n');
    if (jawaban == 'Y' || jawaban == 'y') {
        cout << "Menghapus riwayat: " << s->data[s->top].nama << endl;
        s->top--;
    } else {
        cout << "Pembatalan penghapusan riwayat.\n";
    }
}

void tampilRiwayat(Stack* s) {
    if (isEmptyStack(s)) { cout << "Riwayat kosong.\n"; return; }
    cout << "\n=== Riwayat Tindakan ===\n";
    for (int i = 0; i <= s->top; i++) {
        Hewan* p = &s->data[i];
        cout << "ID: " << p->id << " | Nama: " << p->nama << endl;
    }
}

Hewan peekStack(Stack* s) {
    Hewan kosong; kosong.id = -1; kosong.nama = ""; kosong.jenis = ""; kosong.harga = 0;
    if (isEmptyStack(s)) return kosong;
    return s->data[s->top];
}

int main() {
    Hewan daftar[MAX];
    int n = 0;
    int pilihan;
    Queue antrian;
    Stack riwayat;

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
        cout << "7. Enqueue (Tambah ke Antrian)\n";
        cout << "8. Dequeue (Panggil Pasien)\n";
        cout << "9. Push Riwayat\n";
        cout << "10. Pop Riwayat\n";
        cout << "11. Peek (Antrian & Riwayat)\n";
        cout << "12. Tampil semua antrian\n";
        cout << "13. Tampil semua riwayat\n";
        cout << "14. Enqueue Darurat (Tambah ke depan Antrian)\n";
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
            int idx; cout << "Masukkan indeks hewan: "; cin >> idx;
            if (idx >= 0 && idx < n) enqueue(&antrian, daftar[idx]);
            else cout << "Indeks tidak valid.\n";
        }
        else if (pilihan == 8) {
            Hewan h = dequeue(&antrian);
            if (h.id != -1) push(&riwayat, h);
        }
        else if (pilihan == 9) {
            int idx; cout << "Masukkan indeks hewan: "; cin >> idx;
            if (idx >= 0 && idx < n) push(&riwayat, daftar[idx]);
            else cout << "Indeks tidak valid.\n";
        }
        else if (pilihan == 10) pop(&riwayat);
        else if (pilihan == 11) {
            Hewan q = peekQueue(&antrian);
            Hewan s = peekStack(&riwayat);
            cout << "Peek Antrian: " << (q.id == -1 ? "Kosong" : q.nama) << endl;
            cout << "Peek Riwayat: " << (s.id == -1 ? "Kosong" : s.nama) << endl;
        }
        else if (pilihan == 12) tampilAntrian(&antrian);
        else if (pilihan == 13) tampilRiwayat(&riwayat);
        else if (pilihan == 14) {
            int idx; cout << "Masukkan indeks hewan: "; cin >> idx;
            if (idx >= 0 && idx < n) enqueueDarurat(&antrian, daftar[idx]);
            else cout << "Indeks tidak valid.\n";
        }
        else if (pilihan != 0) cout << "Pilihan tidak dikenal.\n";
    } while (pilihan != 0);

    return 0;
}
