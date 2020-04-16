all:main clean

activable.o: activable.cpp activable.hpp equipement.hpp
	g++ -c activable.cpp

arme.o: arme.cpp arme.hpp
	g++ -c arme.cpp

collectable.o: collectable.cpp collectable.hpp
	g++ -c collectable.cpp -I./SFML-2.5.1/include

equipement.o: equipement.cpp equipement.hpp
	g++ -c equipement.cpp

forme.o: forme.cpp forme.hpp
	g++ -c forme.cpp -I./SFML-2.5.1/include

immediat.o: immediat.cpp immediat.hpp equipement.hpp
	g++ -c immediat.cpp

main.o: main.cpp
	g++ -c main.cpp -I./SFML-2.5.1/include

jeu.o: jeu.cpp jeu.hpp
	g++ -c jeu.cpp

map.o: map.cpp map.hpp
	g++ -c map.cpp -I./SFML-2.5.1/include

menu.o: menu.cpp menu.hpp
	g++ -c menu.cpp

obstacle.o: obstacle.cpp obstacle.hpp
	g++ -c obstacle.cpp -I./SFML-2.5.1/include

robot.o: robot.cpp robot.hpp
	#g++ -c robot.cpp -I./SFML-2.5.1/include

main: activable.o arme.o collectable.o equipement.o forme.o immediat.o main.o jeu.o map.o menu.o obstacle.o robot.o
	g++ -o main main.o -L./SFML-2.5.1/lib -lsfml-graphics -lsfml-window -lsfml-system

play:
	export LD_LIBRARY_PATH=./SFML-2.5.1/lib && ./main

clean:
	rm -f *.o
