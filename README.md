# Simple Shell

## Description

Ce projet implémente un shell simple en langage C dans le cadre de la formation Holberton School. Ce shell peut interpréter et exécuter des commandes de base en mode interactif et non-interactif.

## Fonctionnalités

- Mode interactif avec prompt `($) `
- Mode non-interactif (exécution via pipe)
- Exécution de commandes avec chemin absolu
- Commande intégrée `exit` pour quitter le shell
- Gestion des erreurs et messages d'erreur appropriés
- Gestion des lignes vides et espaces

## Compilation

Pour compiler le shell, utilisez la commande suivante :

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

## Utilisation

### Mode interactif

Lancez le shell en mode interactif :

```bash
./hsh
```

Le shell affichera un prompt `($) ` et attendra vos commandes.

### Mode non-interactif

Vous pouvez également utiliser le shell en mode non-interactif :

```bash
echo "/bin/ls" | ./hsh
```

ou

```bash
echo "exit" | ./hsh
```

## Commandes supportées

### Commandes intégrées

- `exit` : Quitte le shell

### Commandes externes

Le shell peut exécuter toute commande en spécifiant le chemin absolu :

- `/bin/ls`
- `/bin/pwd`
- `/usr/bin/whoami`
- etc.

## Exemples d'utilisation

```bash
$ ./hsh
($) /bin/ls
AUTHORS  README.md  hsh  man_1_simple_shell  shell.c  shell.h
($) /bin/pwd
/home/user/holbertonschool-simple_shell
($) exit
$
```

## Gestion des erreurs

Le shell gère les erreurs suivantes :

- Commandes non trouvées : affiche un message d'erreur avec le nom du programme, le numéro de commande et le nom de la commande
- Erreurs de fork() : affiche un message d'erreur système
- Fin de fichier (EOF) : quitte proprement le shell

## Structure du projet

```
.
├── AUTHORS          # Liste des contributeurs
├── README.md        # Ce fichier
├── man_1_simple_shell # Page de manuel
├── shell.c          # Code source principal
├── shell.h          # Fichier d'en-tête
└── hsh              # Exécutable compilé
```

## Auteurs

Voir le fichier `AUTHORS` pour la liste complète des contributeurs.

## Licence

Ce projet est réalisé dans le cadre de la formation Holberton School.
