Clear:
clear && printf '\e[3J'

Compilation instructions:
gcc -o main.o main.c helper.c lz77.c -Wall

Execution instructions:
./main.o input_file.txt
diff original.txt input_file.txt
