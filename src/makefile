DIR := ../bin


pmt: main.cpp
	mkdir -p $(DIR)
	g++ main.cpp -O3 -o $(DIR)/pmt
	@cd ..;  sudo ln -s $$(pwd)/bin/pmt /usr/local/bin/pmt; chmod +x $$(pwd)/bin/pmt
clean:
	rm $(DIR)/pmt
	sudo rm /usr/local/bin/pmt