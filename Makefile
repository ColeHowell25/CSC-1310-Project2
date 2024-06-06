all				:	CreatureFight

CreatureFight	:	CreatureFight.o Random.o
					g++ -o CreatureFight.exe CreatureFight.o Random.o
				
CreatureFight.o	:	CreatureFight.cpp
					g++ -I ./ -c CreatureFight.cpp

Random.o		:	Random.cpp
					g++ -I ./ -c Random.cpp

clean			:	CreatureFight.exe
					del *.o
					del CreatureFight.exe