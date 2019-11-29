/*
MIT License
Copyright (c) 2019 
Jordan Lecourtois, Hugo Paquin, William Trépanier, Benjamin Theriault 

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef NOTES_H
#define NOTES_H

/*
*   Définition des notes en fonction de leur fréquence et
*   ajout des notes dans un tableau pour pouvoir les appeler par leur index
*/

const uint16_t A2 = 110, //45
    Ad2 = 116, //46
    B2 = 123, //47
    C3 = 130,//48
    Cd3 = 138,//49
    D3 = 146,//50
    Dd3 = 155,//51
    E3 = 164,//52
    F3 = 174,//53
    Fd3 = 184,//54
    G3 = 195,//55
    Gd3 = 207,//56
    A3 = 220,//57
    Ad3 = 233,//58
    B3 = 246,  //59
    C4 = 261, //60
    Cd4 = 277, //61
    D4 = 293, //62
    Dd4 = 311, //63
    E4 = 329, //64
    F4 = 349, //65
    Fd4 = 369, //66
    G4 = 391, //67
    Gd4 = 415, //68
    A4 = 440, //69
    Ad4 = 466, //70
    B4 = 494, //71
    C5 = 523, //72
    Cd5 = 554, //73
    D5 = 587, //74
    Dd5 = 622, //75
    E5 = 659, //76
    F5 = 698, //77
    Fd5 = 739, //78
    G5 = 784, //79
    Gd5 = 831, //80
    A5 = 880; //81

const uint16_t NOTES [36]= {
    A2,Ad2,B2,
    C3,Cd3,D3,Dd3,E3,F3,Fd3,G3,Gd3,A3,Ad3,B3,
    C4,Cd4,D4,Dd4,E4,F4,Fd4,G4,Gd4,A4,Ad4,B4,
    C5,Cd5,D5,Dd5,E5,F5,Fd5,G5,Gd5
};

/*
*   Définition des durée des notes en ms
*/    

enum class DUREE_NOTE {
    DEMI_NOIR = 250,
    NOIR = 500,
    BLANCHE = 1000,
    RONDE = 2000
};

#endif// NOTES_H 
