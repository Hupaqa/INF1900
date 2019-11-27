#ifndef SELECTION_H
#define SELECTION_H

#define BOUTON_INTERRUPT PIND2
#define BOUTON_BREADBOARD PIND3

#include "display.h"
#include "boucle.h"
#include "couloir.h"
#include "mur.h"
#include "coupure.h"
#include "uart.h"
#include "suiveurLigne.h"

enum EtatSelection
{
    selection,
    appeler,
    afficherFin,
};

enum EtapesParcours
{
    couloir,
    mur,
    boucles,
    coupures
};

class Selection 
{
    public:
    
        /*  
        *  Constructeur par paramètres
        *  @param : LCM* ecran : permet d'afficher l'état sur le LCD
        * 
        *  Ce constructeur initialise l'état de la machine à etat du selectionneur
        *  ainsi que l'étape courrante du parcours à couloir
        * 
        *  Le constructeur initilise églement les pins des boutons en lecture
        */ 
        Selection(LCM* lcd);

        /*
        *  run
        *  
        *  Cette fonction est la boucle principale de cette classe. Elle appelle les
        *  fonction doAction et changeState tant que tous les états ne sont pas terminés.
        * 
        *  L'état appeler appelle la fonction run pour chacune des étapes du parcours dans
        *  l'ordre sélectionné
        */ 
        void run();

        /*
        *  changeState
        *  
        *  Cette fonction change l'état courant à l'état suivant de la machine à état
        */
        void changeState();

        /*
        *  doAction
        * 
        *  Cette fonction représente un switch case qui exécute les actions en fonction
        *  de l'état courant. L'état appeler permet l'exécutionn de toutes les étapes du parcours
        */
        void doAction();

        /*
        *  runStep
        *  
        *  Cette fonction représente un switch case qui initialise les objets associé aux étapes
        *  et les exécutes
        */
        void runStep();

        /*
        *  nextStep
        *  
        *  @return EtapesParcours : représente la prochaine étape du parcours
        *  
        *  Cette fonction retourne simplement la prochaine étape du parcous en fonction de
        *  l'étapeCourante
        */
        EtapesParcours nextStep();

        /*
        *  updateFirstStep
        *    
        *  Cette fonction change l'etapeCourante et l'affichage du LCD durant la phase de sélection
        *  de la première étape.
        */
        void updateFirstStep();

        /*
        *  breadboardDebounced
        *  
        *  @return: bool : retourne si le bouton a été appuyé après un délais de debounce
        *   
        *  Cette fonction retourne un boolean si le bouton a été appuyé
        */
        bool breadboardDebounced();

         /*
        *  interruptDebounced
        *  
        *  @return: bool : retourne si le bouton a été appuyé après un délais de debounce
        *   
        *  Cette fonction retourne un boolean si le bouton de l'interruption a été appuyé
        */
        bool interruptDebounced();

        static const uint8_t NOMBRE_ETAPES = 4;
    private:
        EtatSelection _etat;
        EtapesParcours _etapeCourrante;
        LCM* _lcd;
        bool _isDone = false;
        
        
};

#endif //SELECTION_H