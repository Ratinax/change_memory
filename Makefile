
test:
	c++ test.cpp -o test && ./test
	rm test

list_memory:
	c++ list_memory.cpp find_memory.cpp utils.cpp -I . -o list && sudo ./list ${PID} ${STR}
	rm list

change_memory:
	c++ change_memory.cpp find_memory.cpp utils.cpp -I . -o change && sudo ./change ${PID} ${STRFROM} ${NBCHANGES} ${STRTO}
	rm change

proc:
	c++ proc.cpp -o proc && sudo ./proc
	rm change

rm:
	-rm -f change
	-rm -f list
	-rm -f test
	-rm -f proc
