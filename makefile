COMPILER = gcc
FLAGS = -Wall -O3 -mtune=native

LIB = -lgsl -lgslcblas -lm

rps:
	@${COMPILER} ${FLAGS} src/rps.c src/ic.c src/op.c ${LIB} -o rps.out

dft:
	@${COMPILER} ${FLAGS} src/dft.c ${LIB} -o dft.out

c_r:
	@${COMPILER} ${FLAGS} src/c_r.c -lgsl -lgslcblas -lfftw3 -lm -o c_r.out

avg-sd:
	@${COMPILER} ${FLAGS} src/avg-sd.c ${LIB} -o avg-sd.out

clean:
	@rm -f *.out
	@rm -f dat/*.dat

clean-fig:
	@rm -f plt/*.png
	@rm -f plt/*.pdf
	@rm -f plt/*.mp4
