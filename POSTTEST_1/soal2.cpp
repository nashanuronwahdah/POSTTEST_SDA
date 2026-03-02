#include <iostream>
#include <string>
using namespace std;

struct mahasiswa {
	string nama;
	string nim;
	float ipk;
};

int main() {
	mahasiswa mhs[5];
	
	for (int i=0; i < 5; i++){
		cout << "Data Mahasiswa ke " << i+1 << endl;
		cout << "Masukkan Nama: ";
		getline(cin, mhs[i].nama);
		cout << "Masukkan NIM: ";
		cin >> mhs[i].nim;
		cout << "Masukkan IPK: ";
		cin >> mhs[i].ipk;
		cin.ignore();
	}
	
	int indexMax = 0;
	float maxIpk = mhs[0].ipk;
	for (int i = 1; i < 5; i++) {
		if(mhs[i].ipk > maxIpk) {
			maxIpk = mhs[i].ipk;
			indexMax = i;
		}
	}
	
	cout << "Berikut adalah Mahasiswa yang memiliki IPK tertinggi: " << endl;
	cout << "nama: " << mhs[indexMax].nama << endl;
	cout << "NIM: " << mhs[indexMax].nim << endl;
	cout << "IPK: " << mhs[indexMax].ipk << endl;
	
	return 0;
}
