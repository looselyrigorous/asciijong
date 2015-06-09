all : mahjong.o
	clang -o mahjong mahjong.o

mahjong.o : mahjong.c
	clang -c mahjong.c

clean:
