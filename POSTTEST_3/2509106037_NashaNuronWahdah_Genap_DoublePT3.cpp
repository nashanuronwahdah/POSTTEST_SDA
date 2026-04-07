
#include <iostream>
#include <string>
using namespace std;

const int INITIAL_CAP = 5;
const int MAX = 10;

struct Kereta {
    int nomor;
    string nama;
    string asal;
    string tujuan;
    int harga;
};

struct Pesanan {
    string namaPenumpang;
    int nomorKereta;
    string asal;
    string tujuan;
    int harga;
};

struct Snapshot {
    Pesanan queue[MAX];
    int qSize;
    Pesanan riwayat[MAX];
    int top;
};

void tampilJadwal(Kereta* arr, int n) {
    cout << "\n=== Jadwal Kereta (" << n << " data) ===\n";
    for (int i = 0; i < n; ++i) {
        Kereta* p = arr + i;
        cout << "Index " << i
             << " | No:" << p->nomor
             << " | Nama:" << p->nama
             << " | Rute:" << p->asal << "->" << p->tujuan
             << " | Harga:" << p->harga << "\n";
    }
}

void swapKereta(Kereta* a, Kereta* b) {
    Kereta temp = *a;
    *a = *b;
    *b = temp;
}

void tambahKereta(Kereta*& arr, int& n, int& capacity, const Kereta& k) {
    if (n >= capacity) {
        int newCap = capacity * 2;
        Kereta* newArr = new Kereta[newCap];
        for (int i = 0; i < n; ++i) {
            *(newArr + i) = *(arr + i);
        }
        delete[] arr;
        arr = newArr;
        capacity = newCap;
    }
    *(arr + n) = k;
    ++n;
}

int linearSearchByRute(Kereta* arr, int n, const string& asal, const string& tujuan) {
    cout << "\n-- Proses Linear Search (rute " << asal << " -> " << tujuan << ") --\n";
    for (int i = 0; i < n; ++i) {
        cout << "Iterasi " << i+1 << ": cek index " << i << " -> "
             << (arr + i)->asal << " - " << (arr + i)->tujuan << "\n";
        if ((arr + i)->asal == asal && (arr + i)->tujuan == tujuan) {
            cout << "Ditemukan pada index " << i << ": " << (arr + i)->nama << "\n";
            return i;
        }
    }
    cout << "Rute tidak ditemukan.\n";
    return -1;
}

int jumpSearchByNomor(Kereta* arr, int n, int key) {
    if (n <= 0) return -1;
    int step = n / 2;
    if (step < 1) step = 1;
    int prev = 0;
    cout << "\n-- Proses Jump Search (nomor " << key << ") --\n";
    while (prev < n) {
        int checkIdx = (prev + step - 1 < n) ? (prev + step - 1) : (n - 1);
        if ((arr + checkIdx)->nomor < key) {
            cout << "Cek index " << checkIdx << " (nomor " << (arr + checkIdx)->nomor << ") -> < " << key << "\n";
            prev += step;
            if (prev >= n) {
                cout << "Tidak ditemukan (melampaui batas)\n";
                return -1;
            }
        } else break;
    }
    int end = (prev + step < n) ? (prev + step) : n;
    for (int i = prev; i < end; ++i) {
        cout << "Periksa index " << i << " (nomor " << (arr + i)->nomor << ")\n";
        if ((arr + i)->nomor == key) {
            cout << "Ditemukan pada index " << i << ": " << (arr + i)->nama << "\n";
            return i;
        }
    }
    cout << "Tidak ditemukan dalam block.\n";
    return -1;
}

void merge(Kereta* arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    Kereta* L = new Kereta[n1];
    Kereta* R = new Kereta[n2];
    for (int i = 0; i < n1; ++i) L[i] = *(arr + l + i);
    for (int j = 0; j < n2; ++j) R[j] = *(arr + m + 1 + j);

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i].nama <= R[j].nama) {
            *(arr + k) = L[i++];
        } else {
            *(arr + k) = R[j++];
        }
        ++k;
    }
    while (i < n1) {
        *(arr + k) = L[i++];
        ++k;
    }
    while (j < n2) {
        *(arr + k) = R[j++];
        ++k;
    }
    delete[] L;
    delete[] R;
}

void mergeSortByNama(Kereta* arr, int l, int r) {
    if (l >= r) return;
    int m = (l + r) / 2;
    mergeSortByNama(arr, l, m);
    mergeSortByNama(arr, m + 1, r);
    merge(arr, l, m, r);
}

void selectionSortByHarga(Kereta* arr, int n) {
    for (int i = 0; i < n - 1; ++i) {
        int minIdx = i;
        for (int j = i + 1; j < n; ++j) {
            if ((arr + j)->harga < (arr + minIdx)->harga) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            swapKereta(arr + i, arr + minIdx);
        }
    }
}

void inputKeretaFromUser(Kereta& k) {
    cout << "Masukkan nomor kereta (integer): ";
    cin >> k.nomor;
    cin.ignore();
    cout << "Masukkan nama kereta: ";
    getline(cin, k.nama);
    cout << "Masukkan asal: ";
    getline(cin, k.asal);
    cout << "Masukkan tujuan: ";
    getline(cin, k.tujuan);
    cout << "Masukkan harga tiket (integer): ";
    cin >> k.harga;
    cin.ignore();
}

void enqueue(Pesanan* q, int& size, const Pesanan& p) {
    if (size >= MAX) {
        cout << "Enqueue gagal: Antrian penuh (overflow).\n";
        return;
    }
    *(q + size) = p;
    ++size;
    cout << "Penumpang \"" << p.namaPenumpang << "\" masuk antrian.\n";
}

void dequeue(Pesanan* q, int& size, Pesanan* riwayat, int& top) {
    if (size <= 0) {
        cout << "Dequeue gagal: Antrian kosong (underflow).\n";
        return;
    }
    Pesanan front = *(q + 0);
    cout << "Proses tiket untuk: " << front.namaPenumpang << " | Rute: " << front.asal << " -> " << front.tujuan << "\n";
    if (top + 1 >= MAX) {
        cout << "Riwayat penuh: tidak dapat mencatat transaksi ke riwayat.\n";
    } else {
        *(riwayat + (++top)) = front;
    }
    for (int i = 0; i < size - 1; ++i) {
        *(q + i) = *(q + i + 1);
    }
    --size;
}

void pushRiwayat(Pesanan* st, int& top, const Pesanan& p) {
    if (top + 1 >= MAX) {
        cout << "Push gagal: Riwayat penuh (overflow).\n";
        return;
    }
    *(st + (++top)) = p;
}

void popRiwayat(Pesanan* st, int& top) {
    if (top < 0) {
        cout << "Pop gagal: Riwayat kosong (underflow).\n";
        return;
    }
    Pesanan last = *(st + top);
    cout << "Transaksi dibatalkan: " << last.namaPenumpang << " | Rute: " << last.asal << " -> " << last.tujuan << "\n";
    --top;
}

void peekQueue(Pesanan* q, int size) {
    if (size <= 0) {
        cout << "Antrian kosong.\n";
        return;
    }
    Pesanan* p = q;
    cout << "Penumpang terdepan: " << p->namaPenumpang << " | Rute: " << p->asal << " -> " << p->tujuan << "\n";
}

void peekRiwayat(Pesanan* st, int top) {
    if (top < 0) {
        cout << "Riwayat kosong.\n";
        return;
    }
    Pesanan* p = st + top;
    cout << "Transaksi terakhir: " << p->namaPenumpang << " | Rute: " << p->asal << " -> " << p->tujuan << "\n";
}

void tampilSemuaAntrian(Pesanan* q, int size) {
    cout << "\n=== Daftar Antrian (front -> rear) ===\n";
    for (int i = 0; i < size; ++i) {
        Pesanan* p = q + i;
        cout << "Index " << i << " | Nama: " << p->namaPenumpang
             << " | KeretaNo: " << p->nomorKereta
             << " | Rute: " << p->asal << "->" << p->tujuan
             << " | Harga: " << p->harga << "\n";
    }
    if (size == 0) cout << "Antrian kosong.\n";
}

void tampilSemuaRiwayat(Pesanan* st, int top) {
    cout << "\n=== Riwayat Transaksi (bawah -> atas) ===\n";
    if (top < 0) {
        cout << "Riwayat kosong.\n";
        return;
    }
    for (int i = 0; i <= top; ++i) {
        Pesanan* p = st + i;
        cout << "Index " << i << " | Nama: " << p->namaPenumpang
             << " | KeretaNo: " << p->nomorKereta
             << " | Rute: " << p->asal << "->" << p->tujuan
             << " | Harga: " << p->harga << "\n";
    }
}

void inputPesananFromUser(Pesanan& p) {
    cout << "Masukkan nama penumpang: ";
    getline(cin, p.namaPenumpang);
    cout << "Masukkan nomor kereta: ";
    cin >> p.nomorKereta;
    cin.ignore();
    cout << "Masukkan asal: ";
    getline(cin, p.asal);
    cout << "Masukkan tujuan: ";
    getline(cin, p.tujuan);
    cout << "Masukkan harga tiket: ";
    cin >> p.harga;
    cin.ignore();
}

void pushUndo(Snapshot* undoStack, int& undoTop, Pesanan* q, int qSize, Pesanan* riwayat, int top) {
    if (undoTop + 1 >= MAX) {
        for (int i = 0; i < undoTop; ++i) {
            *(undoStack + i) = *(undoStack + i + 1);
        }
        --undoTop;
    }
    Snapshot s;
    for (int i = 0; i < qSize; ++i) s.queue[i] = *(q + i);
    for (int i = qSize; i < MAX; ++i) s.queue[i] = Pesanan();
    s.qSize = qSize;
    for (int i = 0; i <= top; ++i) s.riwayat[i] = *(riwayat + i);
    for (int i = top + 1; i < MAX; ++i) s.riwayat[i] = Pesanan();
    s.top = top;
    *(undoStack + (++undoTop)) = s;
}

void pushRedo(Snapshot* redoStack, int& redoTop, Pesanan* q, int qSize, Pesanan* riwayat, int top) {
    if (redoTop + 1 >= MAX) {
        for (int i = 0; i < redoTop; ++i) {
            *(redoStack + i) = *(redoStack + i + 1);
        }
        --redoTop;
    }
    Snapshot s;
    for (int i = 0; i < qSize; ++i) s.queue[i] = *(q + i);
    for (int i = qSize; i < MAX; ++i) s.queue[i] = Pesanan();
    s.qSize = qSize;
    for (int i = 0; i <= top; ++i) s.riwayat[i] = *(riwayat + i);
    for (int i = top + 1; i < MAX; ++i) s.riwayat[i] = Pesanan();
    s.top = top;
    *(redoStack + (++redoTop)) = s;
}

void clearRedo(Snapshot* redoStack, int& redoTop) {
    redoTop = -1;
}

void doUndo(Snapshot* undoStack, int& undoTop, Snapshot* redoStack, int& redoTop, Pesanan* q, int& qSize, Pesanan* riwayat, int& top) {
    if (undoTop < 0) {
        cout << "Undo gagal: tidak ada aksi untuk dibatalkan.\n";
        return;
    }
    pushRedo(redoStack, redoTop, q, qSize, riwayat, top);
    Snapshot s = *(undoStack + undoTop);
    --undoTop;
    for (int i = 0; i < s.qSize; ++i) *(q + i) = s.queue[i];
    for (int i = s.qSize; i < MAX; ++i) *(q + i) = Pesanan();
    qSize = s.qSize;
    for (int i = 0; i <= s.top; ++i) *(riwayat + i) = s.riwayat[i];
    for (int i = s.top + 1; i < MAX; ++i) *(riwayat + i) = Pesanan();
    top = s.top;
    cout << "Undo berhasil.\n";
}

void doRedo(Snapshot* redoStack, int& redoTop, Snapshot* undoStack, int& undoTop, Pesanan* q, int& qSize, Pesanan* riwayat, int& top) {
    if (redoTop < 0) {
        cout << "Redo gagal: tidak ada aksi untuk diulang.\n";
        return;
    }
    pushUndo(undoStack, undoTop, q, qSize, riwayat, top);
    Snapshot s = *(redoStack + redoTop);
    --redoTop;
    for (int i = 0; i < s.qSize; ++i) *(q + i) = s.queue[i];
    for (int i = s.qSize; i < MAX; ++i) *(q + i) = Pesanan();
    qSize = s.qSize;
    for (int i = 0; i <= s.top; ++i) *(riwayat + i) = s.riwayat[i];
    for (int i = s.top + 1; i < MAX; ++i) *(riwayat + i) = Pesanan();
    top = s.top;
    cout << "Redo berhasil.\n";
}

int main() {
    int capacity = INITIAL_CAP;
    Kereta* daftar = new Kereta[capacity];
    int n = 0;

    tambahKereta(daftar, n, capacity, Kereta{101, "Argo Bromo", "Jakarta", "Surabaya", 350000});
    tambahKereta(daftar, n, capacity, Kereta{102, "Taksaka", "Yogyakarta", "Jakarta", 300000});
    tambahKereta(daftar, n, capacity, Kereta{103, "Mataram", "Solo", "Bandung", 280000});

    Pesanan queue[MAX];
    Pesanan riwayat[MAX];
    int qSize = 0;
    int top = -1;

    Snapshot undoStack[MAX];
    Snapshot redoStack[MAX];
    int undoTop = -1;
    int redoTop = -1;

    int pilihan = 0;
    while (true) {
        cout << "\n=== Menu Sistem Kereta & Tiket (Undo/Redo) ===\n";
        cout << "1. Tampil jadwal\n";
        cout << "2. Tambah data kereta (input)\n";
        cout << "3. Tampil jadwal antrian\n";
        cout << "4. Enqueue (beli tiket)\n";
        cout << "5. Dequeue (proses tiket)\n";
        cout << "6. Tampil riwayat transaksi\n";
        cout << "7. Pop riwayat (batalkan transaksi terakhir)\n";
        cout << "8. Peek (lihat depan antrian & transaksi terakhir)\n";
        cout << "9. Merge sort by nama (A-Z)\n";
        cout << "10. Selection sort by harga (termurah)\n";
        cout << "11. Undo\n";
        cout << "12. Redo\n";
        cout << "0. Keluar\n";
        cout << "Pilih: ";
        cin >> pilihan;
        cin.ignore();

        if (pilihan == 0) break;
        if (pilihan == 1) {
            tampilJadwal(daftar, n);
        } else if (pilihan == 2) {
            Kereta k;
            inputKeretaFromUser(k);
            tambahKereta(daftar, n, capacity, k);
            cout << "Data kereta berhasil ditambahkan.\n";
        } else if (pilihan == 3) {
            tampilSemuaAntrian(queue, qSize);
        } else if (pilihan == 4) {
            if (qSize >= MAX) {
                cout << "Antrian penuh: tidak bisa menambah pemesanan.\n";
            } else {
                Pesanan p;
                inputPesananFromUser(p);
                pushUndo(undoStack, undoTop, queue, qSize, riwayat, top);
                clearRedo(redoStack, redoTop);
                enqueue(queue, qSize, p);
            }
        } else if (pilihan == 5) {
            if (qSize <= 0) {
                cout << "Antrian kosong: tidak ada yang diproses.\n";
            } else {
                pushUndo(undoStack, undoTop, queue, qSize, riwayat, top);
                clearRedo(redoStack, redoTop);
                dequeue(queue, qSize, riwayat, top);
            }
        } else if (pilihan == 6) {
            tampilSemuaRiwayat(riwayat, top);
        } else if (pilihan == 7) {
            if (top < 0) {
                cout << "Riwayat kosong: tidak ada transaksi untuk dibatalkan.\n";
            } else {
                pushUndo(undoStack, undoTop, queue, qSize, riwayat, top);
                clearRedo(redoStack, redoTop);
                popRiwayat(riwayat, top);
            }
        } else if (pilihan == 8) {
            cout << "\n-- Peek Antrian --\n";
            peekQueue(queue, qSize);
            cout << "-- Peek Riwayat --\n";
            peekRiwayat(riwayat, top);
        } else if (pilihan == 9) {
            if (n > 0) mergeSortByNama(daftar, 0, n - 1);
            cout << "Selesai merge sort berdasarkan nama.\n";
        } else if (pilihan == 10) {
            selectionSortByHarga(daftar, n);
            cout << "Selesai selection sort berdasarkan harga.\n";
        } else if (pilihan == 11) {
            doUndo(undoStack, undoTop, redoStack, redoTop, queue, qSize, riwayat, top);
        } else if (pilihan == 12) {
            doRedo(redoStack, redoTop, undoStack, undoTop, queue, qSize, riwayat, top);
        } else {
            cout << "Pilihan tidak dikenal.\n";
        }
    }

    delete[] daftar;
    cout << "Program selesai.\n";
    return 0;
}