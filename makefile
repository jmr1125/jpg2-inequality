all:
	$(MAKE) -C build
test1.gray: test1.jpg ./build/jpg2gray
	./build/jpg2gray test1.jpg > test1.gray
test1.fft: test1.gray ./build/gray2ifft
	./build/gray2ifft test1.gray > test1.fft
result.jpg: test1.fft ./build/ifft2gray
	./build/ifft2gray test1.fft
