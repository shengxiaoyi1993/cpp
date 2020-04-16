.PHONY:all
all:readpipe writepipe

readpipe:readpipe.c
	gcc -o $@ $^
writepipe:writepipe.c
	gcc -o $@ $^

.PHONY:clean
clean:
	rm -f readpipe writepipe
