# laughing-eureka
The `run` target in the `makefile` uses the current directory (`.`) as the argument for main in work09.c, which means that it will print out the files in this directory when you call it using `make run`. To use a different directory:
1. Compile using `make`
1. Type `./a.out <path of directory whose files you want to list>`
