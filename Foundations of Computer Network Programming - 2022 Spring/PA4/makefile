all: UDPclient UDPserver

UDPclient: UDPclient.c
	gcc -o ufclient UDPclient.c

UDPserver: UDPserver.c
	gcc -o ufserver UDPserver.c
	
clean:
	rm ufclient ufserver