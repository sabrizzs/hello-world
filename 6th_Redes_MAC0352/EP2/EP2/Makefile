MAKEFLAGS += -r

ODIR=src
IDIR=interfaces
IDIRSFLAGS=-I$(IDIR)/common/ -I$(IDIR)/client/ -I$(IDIR)/server/
CXX=g++
CXXFLAGS=$(IDIRSFLAGS) -Wall -lm -pthread

_DEPS = config.hpp packet.hpp user.hpp logger.hpp payloadHandler.hpp util.hpp abstract.hpp tcp.hpp udp.hpp
DEPS = $(patsubst %,$(IDIR)/common/%,$(_DEPS))

_OBJ = packet.o user.o logger.o payloadHandler.o util.o abstract.o tcp.o udp.o
OBJ = $(patsubst %,$(ODIR)/common/%,$(_OBJ))

_DEPS_CLIENT = match.hpp clientHandler.hpp gameProcessor.hpp
DEPS_CLIENT = $(patsubst %,$(IDIR)/client/%,$(_DEPS_CLIENT))

_OBJ_CLIENT = match.o clientHandler.o gameProcessor.o client.o
OBJ_CLIENT = $(patsubst %,$(ODIR)/client/%,$(_OBJ_CLIENT))

_DEPS_SERVER = fileHandler.hpp backend.hpp
DEPS_SERVER = $(patsubst %,$(IDIR)/server/%,$(_DEPS_SERVER))

_OBJ_SERVER = fileHandler.o backend.o server.o
OBJ_SERVER = $(patsubst %,$(ODIR)/server/%,$(_OBJ_SERVER))

###############################
all: client server

client: $(OBJ) $(OBJ_CLIENT)
	$(CXX) -o $@ $(OBJ_CLIENT) $(OBJ) $(CXXFLAGS)

server: $(OBJ) $(OBJ_SERVER)
	$(CXX) -o $@ $(OBJ) $(OBJ_SERVER) $(CXXFLAGS)

$(ODIR)/common/%.o: $(ODIR)/common/%.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

$(ODIR)/client/%.o: $(ODIR)/client/%.cpp $(DEPS_CLIENT)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

$(ODIR)/server/%.o: $(ODIR)/server/%.cpp $(DEPS_SERVER)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

.PHONY: clean

clean:
	rm -f client server $(ODIR)/**/*.o
