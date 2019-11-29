# Projet initial de système embarqué

## Auteurs
 * Jordan Lecourtois  
 * Hugo Paquin  
 * William Trépanier  
 * Benjamin Theriault  

## Détails du microcontrolleur
 * ATMega324PA  
 * Cristal de 8MHz

## Configuration de l'environnement   

### Logiciels nécessaires  
 * avr-binutils   
 * avr-gcc   
 * avr-libc  
 * avrdude  
 * make

### Compilation  
Pour compiler, il suffit d'exécuter à la racine :  
```
make
```  

Pour compiler et configurer le microcontrolleur, il suffit d'exécuter à la racine (utilise avrdude) :
```
make install
```

### Classes :
#### Dans le répertoire src
 * Boucle : Classe qui exécute les deux boucles
 * Couloir : Classe qui exécute le couloir
 * Coupure : Classe qui exécute les coupures
 * Mur : Classe qui exécute le mur
 * Selection : Classe permettant la sélection de la première épreuve et qui exécute les quatres étapes
 
#### Dans la librairie
 * LCM : Classe permettant d'écrire sur l'écran LCD
 * Led : Classe permettant le contrôle de la LED
 * Music : Classe permettant le contrôle du piézoélectrique et de faire de la musique
 * SuiveurLigne : Classe qui permet de suivre la ligne

### Informations complémentaires
 * La fonction main() se retrouve dans selection.cpp
 * [Utilisation des ports](https://github.com/wtrep/INF1900/wiki/Utilisation-des-ports)
 * [Trajet](https://github.com/wtrep/INF1900/wiki/Trajet-pour-le-cours-INF1900-de-l'automne-2019)
