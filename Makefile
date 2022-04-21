all:
	cc -std=c99 tank.c iotest.c pipetest.c normalexec.c  -o tankaaa
clean:
	rm -rf tankaaa
