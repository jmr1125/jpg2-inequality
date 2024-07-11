#include "fft.h"
#include "ignore_condition.h"
#include <complex>
#include <fstream>
#include <iostream>
#include <jerror.h>
#include <jpeglib.h>
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
  int size;
  ifstream ifs(filename.c_str());
  ifs >> size;
  vector<vector<cd>> input;
  input.resize(size, vector<cd>(size));
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      double real, imag;
      ifs >> real >> imag;
      input[i][j] = cd(real, imag);
    }
  }
  {
    int count = 0;
    for (int i = 0; i < size; ++i) {
      for (int j = 0; j < size; ++j) {
        if (ignore_arg(input[i][j].real(), input[i][j].imag(), i, j)) {
          input[i][j] = 0;
        } else {
          ++count;
          cout << i << "," << j << ":" << input[i][j].real() << " "
               << input[i][j].imag() << endl;
        }
      }
    }
    cout << "totally " << count << " arguments" << endl;
  }
  vector<vector<cd>> output;
  output = fft(input, 1);
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      output[i][j] /= (size);
    }
  }
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      // cout << setprecision(6) << output[i][j].real() << " "
      //      << output[i][j].imag() << " ";
    }
    // cout << endl;
  }
  {
    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;
    FILE *outfile;
    JSAMPROW row_pointer[1];
    int row_stride;
    JSAMPLE *buffer;
    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo);
    if ((outfile = fopen("result.jpeg", "wb")) == NULL) {
      fprintf(stderr, "can't open %s\n", "fft.jpeg");
      exit(1);
    }
    jpeg_stdio_dest(&cinfo, outfile);
    cinfo.image_width = size;
    cinfo.image_height = size;
    cinfo.input_components = 3;
    cinfo.in_color_space = JCS_RGB;
    jpeg_set_defaults(&cinfo);
    jpeg_start_compress(&cinfo, TRUE);
    row_stride = size * 3;
    buffer = new JSAMPLE[size * 3];
    while (cinfo.next_scanline < cinfo.image_height) {
      for (int i = 0; i < size; ++i) {
        buffer[i * 3] =
            (JSAMPLE)(output[cinfo.next_scanline][i].real() * 256.0);
        buffer[i * 3 + 1] =
            (JSAMPLE)(output[cinfo.next_scanline][i].real() * 256.0);
        buffer[i * 3 + 2] =
            (JSAMPLE)(output[cinfo.next_scanline][i].real() * 256.0);
      }
      row_pointer[0] = buffer;
      jpeg_write_scanlines(&cinfo, row_pointer, 1);
    }
    jpeg_finish_compress(&cinfo);
    fclose(outfile);
    delete[] buffer;
    jpeg_destroy_compress(&cinfo);
  }
  return 0;
}
