#include "fft.h"
#include "ignore_condition.h"
#include <iostream>
using namespace std;
int n;
int main() {
  /*
  sin(x*2+y*3)*1.5+cos(x*2+y*3)*2.0

  e^(pi*i*x)=cos(x)+i*sin(x)
  */
  cin >> n;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; ++j) {
      double real, imag;
      cin >> real >> imag;
      if (!ignore_arg(real, imag, i, j))
        if (i == 0 && j == 0) {
          cout << "+(" << real << "+" << imag << "i)";
        } else if (i == 0 && j != 0) {
          cout << "+(" << real << "+" << imag << "i)*e^(y*" << j << ")";
        } else if (i != 0 && j == 0) {
          cout << "+(" << real << "+" << imag << "i)*e^(x*" << i << ")";
        } else {
          cout << "+(" << real << "+" << imag << "i)*e^(x*" << i << "+y*" << j
               << ")";
        }
    }
    cout.flush();
  }
}
