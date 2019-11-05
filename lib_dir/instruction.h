#ifndef INSTRUCTION_H
#define INSTRUCTION_H

const uint8_t DBT = 0b00000001; // début
const uint8_t ATT = 0b00000010; // attendre
const uint8_t DAL = 0b01000100; // allumer la DEL
const uint8_t DET = 0b01000101; // éteindre la DEL
const uint8_t SGO = 0b01001000; // jouer une sonorité
const uint8_t SAR = 0b00001001; // arrêter de jouer la sonorité
const uint8_t MAR0 = 0b01100000; // arrêter les moteurs
const uint8_t MAR1 = 0b01100001; // arrêter les moteurs
const uint8_t MAV = 0b01100010; // avancer
const uint8_t MRE = 0b01100011; // reculer
const uint8_t TRD = 0b01100100; // tourner à droite
const uint8_t TRG = 0b01100101; // tourner à gauche
const uint8_t DBC = 0b11000000; // début de boucle
const uint8_t FBC = 0b11000001; // fin de boucle
const uint8_t FIN = 0b11111111; // fin

#endif // INSTRUCTION_H