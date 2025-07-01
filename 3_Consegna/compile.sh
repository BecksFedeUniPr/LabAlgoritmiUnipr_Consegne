mkdir -p ./bin
g++ -c ./Data_Structure/Graph.cpp -o ./bin/Graph.o
g++ -c ./Data_Structure/Vertex.cpp -o ./bin/Vertex.o
g++ -c ./Data_Structure/Stack.cpp -o ./bin/Stack.o
g++ -c main.cpp -o ./bin/main.o
g++ ./bin/main.o ./bin/Graph.o ./bin/Vertex.o ./bin/Stack.o -o programma