all:remodel.o
remodel:remodel.cpp
    g++ remodel.cpp -o remodel -lssl -lcrypto
