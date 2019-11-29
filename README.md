# Projet initial de système embarqué

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
Pour compiler uniquement, il suffit d'exécuter à la racine :  
```
make
```  

Pour compiler et configurer le microcontrolleur, il suffit d'exécuter à la racine (utilise avrdude) :
```
make install
```
