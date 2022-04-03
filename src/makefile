parent_DIR = $(dirname $(dirname "$0"))
DIR := ../bin

pmt: main.cpp
	mkdir -p $(DIR)
	g++ main.cpp -O3 -o $(DIR)/pmt
	
clean:
	rm $(DIR)/pmt
	sudo rm /usr/local/bin/pmt