all: compile1 run graph1 graph2 graph3 graph4 graph5 gnucompile gnurun

compile1:
	gcc probskiplist.c -o probskiplist.out

run:
	./probskiplist.out ${INPUT}

graph1:
	dot -Tps 1.dot -o graph1.ps

graph2:
	dot -Tps 2.dot -o graph2.ps

graph3:
	dot -Tps 3.dot -o graph3.ps

graph4:
	dot -Tps 4.dot -o graph4.ps

graph5:
	dot -Tps 5.dot -o graph5.ps

gnucompile:
	gcc gnuplot.c -o gnuplot.out

gnurun:
	./gnuplot.out > output.png