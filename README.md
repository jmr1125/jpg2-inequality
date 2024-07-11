# compile
`cmake -S. -Bbuild && make -C build`\
`libjpeg` required
# usage
`jpg2gray test1.jpg > test1.gray`\
`gray2ifft test1.gray > test1.fft`\
inequality: `ifft2gray test1.fft > test1.inq && echo \>0.5 >> test1.inq`\
result: `ifft2gray test1.fft`
