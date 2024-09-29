collatz: collatz.c
	gcc -o collatz collatz.c cache.c collatzF.c

clean:
	rm collatz