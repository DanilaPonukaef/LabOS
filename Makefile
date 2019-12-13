all: compl start clean
compl: main.c
	gcc main.c -o lala
start: lala
	./lala
clean: lala
	rm -rf lala
