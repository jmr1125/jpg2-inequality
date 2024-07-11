#include "fft.h"
vector<vector<cd>> fft(vector<vector<cd>> in, double flag) {
  const auto n = in.size();
  if (n == 1)
    return in;
  vector<vector<cd>> a00 = vector(n / 2, vector<cd>(n / 2));
  auto a10 = a00, a01 = a00, a11 = a00;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (((i & 1) == 0) && ((j & 1) == 0)) {
        a00[i / 2][j / 2] = in[i][j];
      } else if (((i & 1) == 0) && ((j & 1) == 1)) {
        a01[i / 2][j / 2] = in[i][j];
      } else if (((i & 1) == 1) && ((j & 1) == 0)) {
        a10[i / 2][j / 2] = in[i][j];
      } else if (((i & 1) == 1) && ((j & 1) == 1)) {
        a11[i / 2][j / 2] = in[i][j];
      }
    }
  }
  a00 = fft(a00, flag);
  a10 = fft(a10, flag);
  a01 = fft(a01, flag);
  a11 = fft(a11, flag);
  for (int i = 0; i < n / 2; ++i) {
    for (int j = 0; j < n / 2; ++j) {
      a10[i][j] *= exp(flag * 2 * M_PI * complex<double>(0, 1) * (1.0 * i / n));
      a01[i][j] *= exp(flag * 2 * M_PI * complex<double>(0, 1) * (1.0 * j / n));
      a11[i][j] *=
          exp(flag * 2 * M_PI * complex<double>(0, 1) * (1.0 * (i + j) / n));
    }
  }

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      in[i][j] =
          a00[i % (n / 2)][j % (n / 2)] +
          ((i < n / 2) ? 1.0 : -1.0) * a10[i % (n / 2)][j % (n / 2)] +
          ((j < n / 2) ? 1.0 : -1.0) * a01[i % (n / 2)][j % (n / 2)] +
          ((((i < n / 2) && (j < n / 2)) || ((i >= n / 2) && (j >= n / 2)))
               ? 1.0
               : -1.0) *
              a11[i % (n / 2)][j % (n / 2)];
    }
  }
  return in;
}
