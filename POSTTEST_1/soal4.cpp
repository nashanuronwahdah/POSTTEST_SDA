#include <iostream>
#include <string>
using namespace std;

void tukar(int*a, int*b) {
	int sementara = *a;
	*a = *b;
	*b = sementara;
}

int main() {
	int angka1, angka2;
	
	// Input Nilai
	cout << "Masukkan nilai pertama: ";
	cin >> angka1;
	cout << "Masukkan nilai kedua: ";
	cin >> angka2;
	
	//Sebelum Tukar
	cout << "/nSebelum ditukar: " << endl;
	cout << "angka1 = " << angka1 << ", angka2 = " << angka2 << endl;
	
	//Panggil Fungsi Tukar
	tukar(&angka1, &angka2);
	
	//Sesudah Tukar
	cout << "/nSesudah ditukar: " << endl;
	cout << "angka1 = " << angka1 << ", angka2 = " << angka2 << endl;
	
	return 0;
	
}
