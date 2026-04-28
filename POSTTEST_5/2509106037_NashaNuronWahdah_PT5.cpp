#include <iostream>
#include <string>
using namespace std;

// Struktur Node untuk Circular Linked List Perpustakaan
struct BukuNode {
    string judulBuku;
    BukuNode* next;

    // Constructor
    BukuNode(string judul) {
        judulBuku = judul;
        next = nullptr;
    }
};

// Fungsi insert di akhir Circular Linked List untuk membangun data
BukuNode* tambahBuku(BukuNode* head, string judul) {
    BukuNode* newNode = new BukuNode(judul);
    if (head == nullptr) {
        newNode->next = newNode;
        return newNode;
    }
    
    BukuNode* temp = head;
    while (temp->next != head) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->next = head;
    return head;
}

/**
 * @brief Fungsi untuk mencari buku berdasarkan judulnya dalam Circular Linked List.
 */
bool cariBuku(BukuNode* head, string judulDicari) {
    // 1. Jika list kosong (head == nullptr), kembalikan false.
    if (head == nullptr) {
        return false;
    }

    // 2. Mulai penelusuran dari head menggunakan pointer temp.
    BukuNode* temp = head;

    // Menggunakan do-while agar node pertama langsung di-cek,
    // dan perulangan berhenti saat temp kembali menyentuh head.
    do {
        // 3. Cek apakah judulBuku sama dengan judulDicari.
        if (temp->judulBuku == judulDicari) {
            return true; // Ketemu! Langsung kembalikan true
        }
        
        // 4. Lanjutkan ke node berikutnya.
        temp = temp->next;
        
    } while (temp != head); // Berhenti jika temp kembali mencapai head

    // 5. Jika seluruh list sudah ditelusuri dan tidak ditemukan, kembalikan false.
    return false;
}

int main() {
    BukuNode* head = nullptr;
    
    head = tambahBuku(head, "Struktur Data dengan C++");
    head = tambahBuku(head, "Pengantar Algoritma");
    head = tambahBuku(head, "Pemrograman Berorientasi Objek");
    head = tambahBuku(head, "Sistem Basis Data");

    string buku1 = "Pengantar Algoritma";
    string buku2 = "Kalkulus Lanjut";

    cout << "Mencari buku '" << buku1 << "': " 
         << (cariBuku(head, buku1) ? "Ditemukan" : "Tidak Ditemukan") << endl; 
         // Harusnya output: Ditemukan

    cout << "Mencari buku '" << buku2 << "': " 
         << (cariBuku(head, buku2) ? "Ditemukan" : "Tidak Ditemukan") << endl; 
         // Harusnya output: Tidak Ditemukan

    return 0;
}