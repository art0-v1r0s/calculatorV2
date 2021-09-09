CC = gcc									# Nom du compilateur
CFLAGS = -std=c99 -Wall -Wextra -Werror -Wstrict-prototypes -fanalyzer		# Les flags
RM = rm -f 									# Commande pour supprimer des fichiers
NAME = calculator									# Nom de l'exécutable
SRC = exo1.c	 								# Les fichiers source. Soir *.c, soit on liste les fichiers
EXEC = ./
4POW = -lm

all: compilation execute 

execute:
	$(EXEC)$(NAME)

compilation:							# Règle all, exécutée par défaut avec la commande "make"
	$(CC) $(CFLAGS) $(SRC) -o $(NAME) $(4POW)			# On n'utilise que des variables ici. On modifie les variables, pas la ligne de commande

clean:								# Règle clean, pour supprimer les fichiers générés par le compilateur. On utilise "make clean"
	$(RM) $(NAME)

re: clean all							# "make re", pour supprimer les anciens fichiers et les génére à nouveau.
