default: major1 parity endian rotate clz
	gcc *.o -o bitwisemenu

major1: major1.c major1.h
	gcc -c major1.c
	
parity: parity.c
	gcc -c parity.c
	
endian: endian.c
	gcc -c endian.c
	
rotate: rotate.c
	gcc -c rotate.c
	
clz: clz.c
	gcc -c clz.c
	
clean:
	rm *.o bitwisemenu