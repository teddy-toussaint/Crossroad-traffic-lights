#Declaration des variables
CC= gcc
CFLAGS= -Wall

#Commandes
all: Coordinateur Generateur_trafic

Coordinateur: coordinateur.c messages_types.h
	$(CC) $(CFLAGS) $< -o $@

Generateur_trafic: generateur_trafic.c Generateur_prio messages_types.h
	$(CC) $(CFLAGS) $< -o $@

Generateur_prio: generateur_traffic_prioritaire.c
	$(CC) $(CFLAGS) $< -o $@

#Nettoyage
clean:
	rm -f Coordinateur Generateur_prio Generateur_trafic a.out
