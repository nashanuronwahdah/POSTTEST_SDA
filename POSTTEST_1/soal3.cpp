#include <iostream>
#include <string>
using namespace std;

void reverseArray(int* data, int jumlah){
	int* awal = data;
	int* akhir = data + jumlah - 1;
	
	while (awal < akhir) {
		int sementara = *awal;
		*awal = *akhir;
		*akhir = sementara;
		
		awal++;
		akhir--;
	}
}

int main() {
	int prima [7] = {2, 3, 5, 7, 11, 13, 17};
	int jumlah = 7;
	
	cout << "Array sebelum dibalik: " << endl;
	for (int i = 0; i < jumlah; i++) {
		cout << "prima[" << i << "] = " << prima[i]
			 << " (alamat: " << &prima[i] << ")" << endl;
	}
	
	reverseArray(prima, jumlah);
	
	cout << "\n Array sesudah dibalik: " << endl;
	for (int i = 0; i < jumlah; i++) {
		cout << "prima[" << i << "] = " << prima[i]
		     << " (alamat: " << &prima[i] << ")" << endl;
	}
	
	return 0;
	
	
}
