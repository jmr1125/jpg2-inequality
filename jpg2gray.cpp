#include <iostream>
#include <jerror.h>
#include <jpeglib.h>
#include <stdio.h>
#include <vector>
using namespace std;
int main(int argc, char **argv) {
  string lpFilename;
  if (argc == 2) {
    lpFilename = argv[1];
  } else {
    cerr << "Usage: " << argv[0] << " <filename>" << endl;
  }
  // https://www.tspi.at/2020/03/20/libjpegexample.html
  struct jpeg_decompress_struct info;
  struct jpeg_error_mgr err;

  unsigned long int imgWidth, imgHeight;
  int numComponents;

  unsigned long int dwBufferBytes;
  unsigned char *lpData;

  unsigned char *lpRowBuffer[1];

  FILE *fHandle;

  fHandle = fopen(lpFilename.c_str(), "rb");
  if (fHandle == NULL) {
#ifdef DEBUG
    fprintf(stderr, "%s:%u: Failed to read file %s\n", __FILE__, __LINE__,
            lpFilename);
#endif
    return NULL; /* ToDo */
  }

  info.err = jpeg_std_error(&err);
  jpeg_create_decompress(&info);

  jpeg_stdio_src(&info, fHandle);
  jpeg_read_header(&info, TRUE);

  jpeg_start_decompress(&info);
  imgWidth = info.output_width;
  imgHeight = info.output_height;
  numComponents = info.num_components;

#ifdef DEBUG
  fprintf(stderr,
          "%s:%u: Reading JPEG with dimensions %lu x %lu and %u components\n",
          __FILE__, __LINE__, imgWidth, imgHeight, numComponents);
#endif

  dwBufferBytes = imgWidth * imgHeight * 3; /* We only read RGB, not A */
  lpData = (unsigned char *)malloc(sizeof(unsigned char) * dwBufferBytes);
  cout << imgHeight << endl;
  cout << imgWidth << endl;
  vector<vector<double>> output;
  double _max=256,_min=0;
  output.resize(imgHeight, vector<double>(imgWidth));
  while (info.output_scanline < info.output_height) {
    lpRowBuffer[0] = (unsigned char *)(&lpData[3 * info.output_width *
                                               info.output_scanline]);
    jpeg_read_scanlines(&info, lpRowBuffer, 1);
    for (int i = 0; i < imgWidth * 3; i += 3) {
      output[info.output_scanline - 1][i / 3] =
          double(0.3 * lpRowBuffer[0][i] + 0.59 * lpRowBuffer[0][i + 1] +
                 0.11 * lpRowBuffer[0][i + 2]);
      _max=max(_max,output[info.output_scanline - 1][i / 3]);
      _min=min(_min,output[info.output_scanline - 1][i / 3]);
    }
  }

  jpeg_finish_decompress(&info);
  jpeg_destroy_decompress(&info);
  fclose(fHandle);

  for(int i=0;i<imgHeight;i++) {
    for(int j=0;j<imgWidth;j++) {
      cout << (output[i][j]-_min)/(_max-_min) << " ";
    }
    cout << endl;
  }
}
