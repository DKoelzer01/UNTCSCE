newshell: interpreter.o builtin.o control.o alias.o
	gcc -o newshell *.o
	
interpreter.o: interpreter.c interpreter.h builtin.h control.h alias.h
	gcc -c interpreter.c
	
builtin.o: builtin.c builtin.h
	gcc -c builtin.c
	
control.o: control.c control.h
	gcc -c control.c

alias.o: alias.c alias.h
	gcc -c alias.c
	
clean:
	rm *.o newshell