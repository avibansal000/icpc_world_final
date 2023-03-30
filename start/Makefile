run: foo
	./foo <input.txt > output.txt
foo: foo.o
	@g++ foo.o -o foo
foo.o: foo.cpp
	g++ -c foo.cpp