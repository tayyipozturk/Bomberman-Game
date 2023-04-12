all:
	gcc -c src/message.c -o obj/message.o
	gcc -c src/logging.c -o obj/logging.o
	g++ -c src/components/bomb.cpp -o obj/bomb.o
	g++ -c src/components/bomber.cpp -o obj/bomber.o
	g++ -c src/components/map.cpp -o obj/map.o
	g++ -c src/components/obstacle.cpp -o obj/obstacle.o
	g++ -c src/parser.cpp -o obj/parser.o
	g++ -c src/controller.cpp -o obj/controller.o
	g++ -c src/main.cpp -o obj/main.o
	g++ -o bgame obj/*.o