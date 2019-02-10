tabledemo: entry.o table.o tabledemo.o
	g++ -o tabledemo entry.o table.o tabledemo.o

clean:
	/bin/rm -f *.o tabledemo
