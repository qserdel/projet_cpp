all: main tests_catch clean

balle.o: balle.cpp balle.hpp parametres.hpp
	g++ -c -g balle.cpp -I./SFML-2.5.1/include

bouclier.o: bouclier.cpp bouclier.hpp collectable.hpp parametres.hpp
	g++ -c -g bouclier.cpp -I./SFML-2.5.1/include

collectable.o: collectable.cpp collectable.hpp robot.hpp parametres.hpp
	g++ -c -g collectable.cpp -I./SFML-2.5.1/include

collision.o: collision.cpp collision.hpp robot.hpp balle.hpp map.hpp parametres.hpp
	g++ -c -g collision.cpp -I./SFML-2.5.1/include

grandir.o: grandir.cpp grandir.hpp collectable.hpp parametres.hpp
	g++ -c -g grandir.cpp -I./SFML-2.5.1/include

humain.o: humain.cpp humain.hpp joueur.hpp parametres.hpp
	g++ -c -g humain.cpp -I./SFML-2.5.1/include

ia.o: ia.cpp ia.hpp joueur.hpp parametres.hpp
	g++ -c -g ia.cpp -I./SFML-2.5.1/include

jeu.o: jeu.cpp jeu.hpp map.hpp menu.hpp robot.hpp parametres.hpp
	g++ -c -g jeu.cpp -I./SFML-2.5.1/include

joueur.o: joueur.cpp joueur.hpp parametres.hpp
	g++ -c -g joueur.cpp -I./SFML-2.5.1/include

main.o: main.cpp robot.hpp parametres.hpp
	g++ -c -g main.cpp -I./SFML-2.5.1/include

map.o: map.cpp map.hpp bouclier.hpp grandir.hpp rapetisser.hpp reparer.hpp robot.hpp parametres.hpp
	g++ -c -g map.cpp -I./SFML-2.5.1/include

menu.o: menu.cpp menu.hpp parametres.hpp
	g++ -c -g menu.cpp -I./SFML-2.5.1/include

rapetisser.o: rapetisser.cpp rapetisser.hpp collectable.hpp parametres.hpp
	g++ -c -g rapetisser.cpp -I./SFML-2.5.1/include

reparer.o: reparer.cpp reparer.hpp collectable.hpp parametres.hpp
	g++ -c -g reparer.cpp -I./SFML-2.5.1/include

robot.o: robot.cpp robot.hpp balle.hpp humain.hpp ia.hpp joueur.hpp parametres.hpp
	g++ -c -g robot.cpp -I./SFML-2.5.1/include

main: balle.o bouclier.o collectable.o collision.o grandir.o humain.o ia.o jeu.o joueur.o main.o map.o menu.o robot.o rapetisser.o reparer.o
	g++ -g -o main $^ -L./SFML-2.5.1/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio


play:
	export LD_LIBRARY_PATH=./SFML-2.5.1/lib && ./main


# Tests
tests_catch: tests_catch_balle.o balle.o tests_catch_collision.o collision.o tests_catch_jeu.o jeu.o tests_catch_map.o map.o menu.o tests_catch_robot.o robot.o tests_catch_bouclier.o bouclier.o collectable.o tests_catch_grandir.o grandir.o map.o tests_catch_rapetisser.o rapetisser.o tests_catch_reparer.o reparer.o joueur.o humain.o ia.o
	g++ -o tests_catch $^ -L./SFML-2.5.1/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

tests_catch_balle.o: tests_catch_balle.cpp balle.hpp catch.hpp
	g++ -c tests_catch_balle.cpp -I./SFML-2.5.1/include

tests_catch_bouclier.o: tests_catch_bouclier.cpp bouclier.hpp catch.hpp
	g++ -c tests_catch_bouclier.cpp -I./SFML-2.5.1/include

tests_catch_collision.o: tests_catch_collision.cpp collision.hpp catch.hpp
	g++ -c tests_catch_collision.cpp -I./SFML-2.5.1/include

tests_catch_grandir.o: tests_catch_grandir.cpp grandir.hpp catch.hpp
	g++ -c tests_catch_grandir.cpp -I./SFML-2.5.1/include

tests_catch_jeu.o: tests_catch_jeu.cpp jeu.hpp catch.hpp
	g++ -c tests_catch_jeu.cpp -I./SFML-2.5.1/include

tests_catch_map.o: tests_catch_map.cpp map.hpp catch.hpp
	g++ -c tests_catch_map.cpp -I./SFML-2.5.1/include

tests_catch_rapetisser.o: tests_catch_rapetisser.cpp rapetisser.hpp catch.hpp
	g++ -c tests_catch_rapetisser.cpp -I./SFML-2.5.1/include

tests_catch_reparer.o: tests_catch_reparer.cpp reparer.hpp catch.hpp
	g++ -c tests_catch_reparer.cpp -I./SFML-2.5.1/include

tests_catch_robot.o: tests_catch_robot.cpp robot.hpp catch.hpp
	g++ -c tests_catch_robot.cpp -I./SFML-2.5.1/include

tests:
	export LD_LIBRARY_PATH=./SFML-2.5.1/lib && ./tests_catch


clean:
	rm -f *.o
