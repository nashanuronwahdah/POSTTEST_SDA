#include <iostream>
#include <string>
using namespace std;

int FindMin(int A[], int n, int &indexMin) {
    int min = A[0]; 
    indexMin = 0;
    for (int i = 1; i < n; i++) { 
        if (A[i] < min) {         
            min = A[i];           
            indexMin = i;		  
        }
    }
    return min; 
}

int main() {
    int A[8] = {1, 1, 2, 3, 5, 8, 13, 21};
    int n = 8;
    
    int indexMin;
    int minValue = FindMin(A, n, indexMin);

    cout << "Nilai minimum dalam array adalah: " << minValue
         << " Pada indeks ke " << indexMin << endl;

    return 0;
}




//PSEUDO CODE
//procedure FindMin(A : array of n elements)
//  min <= A[0]
//  for i <= 1 to n - 1 do
//    if A[i] < min then
//      min <= A[i]
//    end if
//  end for
//  return min
//end procedure


// | Pseudocode              | Cost | T_min | T_max |
// |-------------------------|------|-------|-------|
// | procedure FindMin       | C1   | 1     | 1     |
// | min <- A[0]             | C2   | 1     | 1     |
// | for i <= 1 to n - 1     | C3   | n     | n     |
// | if A[i] < min           | C4   | n-1   | n-1   |
// | min <= A[i]             | C5   | 0     | n-1   |
// | end if                  | C6   | n-1   | n-1   |
// | end for                 | C7   | n     | n     |
// | return min              | C8   | 1     | 1     |
// | end procedure           | C9   | 1     | 1     |
// | Total waktu (Tₙ)         |      | O(n)  | O(n)  |



// Analisis kompleksitas waktu (Big-O):
// Baris 1 dieksekusi 1 kali = C1 x 1 = C1
// Baris 2 dieksekusi 1 kali = C2 x 1 = C2
// Baris 3 dieksekusi n kali = C3 x n
// Baris 4 dieksekusi n-1 kali = C4 (n-1)
// Baris 5:
//   Best case => kondisi selalu salah, artinya tidak pernah dieksekusi => C5 x 0 = 0
//   Worst case => kondisi selalu benar, artinya dieksekusi sebanyak n-1 kali => C5 (n-1)
// Baris 6 dieksekusi n-1 kali = C6 (n-1)
// Baris 7 dieksekusi n kali = C7 x n
// Baris 8 dieksekusi 1 kali = C8 x 1 = C8
// Baris 9 dieksekusi 1 kali = C9 x 1 = C9
//
// Total:
// Best case: C1 + C2 + C3n + C4(n-1) + 0 + C6(n-1) + C7n + C8 + C9
//           = (C3 + C4 + C6 + C7)n + (C1 + C2 + C8 + C9 − C4 − C6)
//           => fungsi linear => Big-O = O(n)
//
// Worst case: C1 + C2 + C3n + C4(n-1) + C5(n-1) + C6(n-1) + C7n + C8 + C9
//           = (C3 + C4 + C5 + C6 + C7)n + (C1 + C2 + C8 + C9 − C4 − C5 − C6)
//           => fungsi linear => Big-O = O(n)

