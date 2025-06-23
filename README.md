# Philosophers

Le projet Philosophers est un challenge du cursus 42 qui consiste à simuler le problème des philosophes en utilisant des threads. L'objectif est de gérer un certain nombre de philosophes, chacun devant manger et réfléchir, tout en respectant les règles du dîner de philosophes de Dijkstra, sans provoquer de conditions de course ou de blocage (deadlock).

## Description

- **Philosophes** : Chaque philosophe est représenté par un thread qui alterne entre réflexion et alimentation.
- **Fourchettes** : Les philosophes doivent partager des fourchettes pour manger, et chaque philosophe a besoin de deux fourchettes pour manger.
- **Synchronisation** : Utilisation de mutex pour s'assurer que les philosophes n'accèdent pas aux fourchettes en même temps (éviter les conflits).
- **Conditions de course et blocage** : Implémentation de solutions pour éviter les conditions de course et le blocage en contrôlant l'accès aux ressources partagées (les fourchettes).

## Installation

```bash
git clone git@github.com:sferrad/Philosophers.git
cd philosophers
cd philo
make
```
## Utilisation

Lancer le programme avec un nombre de philosophes, le temps qu'ils mangent, et d'autres paramètres :
```bash
./philo <nombre_de_philosophes> <temps_de_vie> <temps_de_mangeage> <temps_de_reflexion> <nombre_de_mangeages>
```
Exemple :
```bash
./philo 5 800 200 200 5
```
## Fichiers

philo/includes/philosophers.h : Header principal du projet.

philo/src/philo.c : Fonction principale qui gère la création des philosophes et leur routine.

philo/src/init_utils.c : Initialisation des philosophes et des ressources (mutex).

philo/src/parsing_utils.c : Gestion des arguments passés en ligne de commande.

philo/src/philo_utils.c : Fonctions utilitaires liées à la gestion des philosophes.

philo/src/philo_utils_2.c : Fonctions utilitaires supplémentaires pour la gestion des philosophes.

philo/src/routine_utils.c : Implémentation de la routine des philosophes (réfléchir, manger, dormir).

philo/src/utils.c : Fonctions utilitaires générales.

Makefile : Fichier pour compiler et nettoyer le projet.


## Commandes Makefile
```
make : Compile les programmes.

make clean : Supprime les fichiers objets.

make fclean : Supprime les fichiers objets et les exécutables.

make re : fclean puis make.
```
## Fonctionnement

Le programme simule plusieurs philosophes qui alternent entre la réflexion et le manger. Chaque philosophe a une durée de vie et un nombre maximal de repas. Ils utilisent des mutex pour gérer l'accès aux fourchettes, et un système de conditionnement évite les deadlocks et garantit qu'aucun philosophe ne restera bloqué.

L'algorithme s'assure que les philosophes respectent les règles du dîner, en gérant leur temps de réflexion et de repas en fonction des paramètres fournis.
