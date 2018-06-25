
output: final_project.o
	gcc final_project.o -o output

final_project.o: final_project.c
	gcc -c final_project.c

clean:
	rm *.o *.bin *.schema output out1.txt out1_new.txt

target: dependencies
	action
