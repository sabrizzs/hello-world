PYTHON = python3
RM = rm -f

all: servidor cliente_udp cliente_tcp pacman

servidor:
	$(PYTHON) servidor.py 8080 8080

cliente_udp:
	$(PYTHON) cliente.py localhost 8080 udp

cliente_tcp:
	$(PYTHON) cliente.py localhost 8080 tcp

pacman:
	$(PYTHON) pacman.py

clean:
	$(RM) classificacao.txt status.txt usuarios.txt
