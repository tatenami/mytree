SRCS=mytree

${SRCS}: ${SRCS}.cpp tree.cpp
	g++ -o $@ $^ -g
