gcc -c echo.c -I./ 
gcc -c ps.c -I./
gcc shell.c -I./ ps.o echo.o
./a.out
