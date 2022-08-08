

output: grammar.cc
	g++ grammar.cc -o grammar

grammar.cc: grammar.y
	bison grammar.y -o grammar.cc


target: dependencies
	action