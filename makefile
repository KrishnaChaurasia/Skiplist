all: compile run graph1

compile:
	gcc insertdeletesearch.c

run:
	./a.out

graph1:
	dot -Tps myGraph.dot -o list.ps
