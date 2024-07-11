#include "fft.h"
#include <complex>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;
int main(int argc, char **argv) {
  string filename;
  if (argc == 2) {
    filename = argv[1];
  } else {
    cerr << "usage: " << argv[0] << " <filename>" << endl;
    return 0;
  }
  int h, w;
  ifstream ifs(filename.c_str());
  ifs >> h >> w;
  cerr << "h = " << h << endl;
  cerr << "w = " << w << endl;
  vector<vector<cd>> input;
  input.resize(h, vector<cd>(w));
  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      ifs >> input[i][j];
      //input[i][j] /= 256.0;
    }
  }
  //long long size = 1 << ((int)ceil(log2(max(h, w))));
  long long size=512;
  vector<vector<cd>> output;
  output.resize(size, vector<cd>(size));
  cerr << "h'=w'=" << size << endl;
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      output[i][j] = input[i * h / size][j * w / size];
    }
  }
  output = fft(output, -1);
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      output[i][j] /= (size);
    }
  }
  cout << size << endl;
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      cout <<setprecision(6)<< output[i][j].real() << " " << output[i][j].imag() << " ";
    }
    cout << endl;
  }
  return 0;
}
