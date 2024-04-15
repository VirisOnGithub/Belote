<h1 align="center">BelotePro</h1>

<p align="center">
Ce projet a été réalisé dans le cadre de l'UE LIFAPCD instaurée en Peip2.
</p>

<div align="center">
    <a href="#clone">Clone</a> |
    <a href="#exécution">Exécution</a>
</div>

### Prérequis

Pour pouvoir exécuter le projet, il vous faudra avoir installé les paquets suivants :
- cmake
- sfml

Pour les installer, vous pouvez utiliser les commandes suivantes :

```bash
$ sudo apt-get install cmake libsfml-dev libsfml-audio2.5 libsfml-graphics2.5 libsfml-system2.5 libsfml-window2.5
```

Attention, vous aurez besoin de la commande sudo pour installer les paquets.

### Clone

Pour récupérer le projet, il suffit de cloner le dépôt git :

``bash
$ git clone 
```

Vous pouvez aussi télécharger le projet en .zip en cliquant sur le bouton "Code" puis "Download ZIP".
Vours n'aurez alors plus qu'à extraire l'archive, puis à l'éxécuter.

### Build

#### Linux

Pour compiler le projet, il suffit de cloner le dépôt git et de lancer la commande suivante :

```bash
$ cd Belote
$ cd build
$ cmake -G "Unix Makefiles" ..
$ make
$ ./bin/main
```

### Exécution

#### Linux

Après la compilation, revenez dans le dossier racine du projet (par exemple avec ``cd ..``) et lancez la commande suivante :

```bash
$ ./bin/Belote
```