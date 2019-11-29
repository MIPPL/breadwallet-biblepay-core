
test:	clean 
	cc -I. -I./support -I./vendor/secp256k1 -o $@ bitcoin/*.c bcash/*.c support/*.c ethereum/event/*.c vendor/sqlite/sqlite.c

clean:
	rm -f *.o */*.o test

run:	test
	./test
