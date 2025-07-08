mkdir -p ./bin

g++ -c ./Data_Structure/Graph.cpp -o ./bin/Graph.o
g++ -c ./Data_Structure/DisjointSet.cpp -o ./bin/DisjointSet.o
g++ -c ./main.cpp -o ./bin/main.o

g++ ./bin/main.o ./bin/Graph.o ./bin/DisjointSet.o  -o main
