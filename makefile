all: main tests_catch clean

arme.o: arme.cpp arme.hpp
	g++ -c arme.cpp

balle.o: balle.cpp balle.hpp
	g++ -c balle.cpp -I./SFML-2.5.1/include

bouclier.o: bouclier.cpp bouclier.hpp collectable.hpp
	g++ -c bouclier.cpp -I./SFML-2.5.1/include

collectable.o: collectable.cpp collectable.hpp
	g++ -c collectable.cpp -I./SFML-2.5.1/include

collision.o: collision.cpp collision.hpp robot.hpp balle.hpp
	g++ -c collision.cpp -I./SFML-2.5.1/include

equipement.o: equipement.cpp equipement.hpp
	g++ -c equipement.cpp

grandir.o: grandir.cpp grandir.hpp collectable.hpp
	g++ -c grandir.cpp -I./SFML-2.5.1/include

main.o: main.cpp robot.hpp
	g++ -c main.cpp -I./SFML-2.5.1/include

jeu.o: jeu.cpp jeu.hpp
	g++ -c jeu.cpp -I./SFML-2.5.1/include

map.o: map.cpp map.hpp reparer.hpp
	g++ -c map.cpp -I./SFML-2.5.1/include

menu.o: menu.cpp menu.hpp
	g++ -c menu.cpp

rapetisser.o: rapetisser.cpp rapetisser.hpp collectable.hpp
	g++ -c rapetisser.cpp -I./SFML-2.5.1/include

reparer.o: reparer.cpp reparer.hpp collectable.hpp
	g++ -c reparer.cpp -I./SFML-2.5.1/include

robot.o: robot.cpp robot.hpp balle.hpp
	g++ -c robot.cpp -I./SFML-2.5.1/include

main: arme.o balle.o bouclier.o collectable.o collision.o equipement.o grandir.o jeu.o main.o map.o menu.o robot.o rapetisser.o reparer.o
	g++ -o main $^ -L./SFML-2.5.1/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

play:
	export LD_LIBRARY_PATH=./SFML-2.5.1/lib && ./main

# Tests

#tests_catch: tests_catch_robot.o robot.o
#	g++ -o tests_catch $^ -L./SFML-2.5.1/lib -lsfml-graphics -lsfml-window -lsfml-system


#tests_catch_robot.o: tests_catch_robot.cpp robot.hpp catch.hpp
#	g++ -c tests_catch_robot.cpp -I./SFML-2.5.1/include

#tests:
#	export LD_LIBRARY_PATH=./SFML-2.5.1/lib && ./tests_catch


clean:
	rm -f *.o
