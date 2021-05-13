all: rsa.cpp 
	g++ rsa.cpp -o rsa
clean: 
	$(RM) rsa