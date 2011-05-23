run: Colider
	./$< &

Colider: Colider.cc
	g++ -Iglut -lglut -o $@ $<
