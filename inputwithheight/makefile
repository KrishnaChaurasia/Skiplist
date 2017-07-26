all: compile1 run skiplist

compile1:
	gcc heightskiplist.c -o heightskiplist.out

run:
	./heightskiplist.out $(INPUT)

skiplist:
	dot -Tps myGraph.dot -o graph.ps