
a.out: *.cpp *.h
	g++ -O4 all.cpp -D MAIN_IS_PLAY -march=native -mcpu=native

