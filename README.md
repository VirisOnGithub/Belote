# BelotePro

<div align="center">

</div>

## Prérequis

Pour installer le projet, vous devez avoir installé :

- make
- git
- gcc ou g++
- doxygen (pour la doc)

### Windows

Sous Windows, vous pouvez installer [Chocolatey](https://chocolatey.org/install) pour installer les outils nécessaires.

Une fois installé, vous pouvez installer git et make avec la commande suivante :

```powershell
choco install git make
```

Ensuite, vous pouvez installer gcc et make avec la commande suivante :

```bash
choco install make msys2
```

### Linux

Sous Linux, vous pouvez installer les outils nécessaires avec la commande suivante :

```bash
sudo apt install make git g++
```

## Installation

Vous pouvez cloner le projet avec la commande suivante :

```bash
git clone https://github.com/VirisOnGithub/Belote.git
cd Belote
```

## Compilation

Vous pouvez compiler le projet avec la commande suivante :

```bash
cd build
cmake ..
make
```

## Utilisation

Vous pouvez lancer le projet avec la commande suivante :

```bash
./Graphique
```

## Documentation

Vous pouvez générer la documentation avec la commande suivante :

```bash
doxygen doc/doxyfile
```
