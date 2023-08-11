#ifndef __STRUCT_H__
    #define __STRUCT_H__
        #include <stdio.h>
        #include <stdlib.h>
        #include <string.h>
        #include <ctype.h>

        #define NB_ETUDIANT 50
        #define NB_PC 50

        typedef struct{
            int Numero;
            char Mac[100];
            char Marque[100];
            char Label[100];
        }PC;

        typedef struct{
            int Numero;
            char Nom[100];
            char Prenom[100];
            char Tel[100];
            char Email[100];
            char Adresse[100];
            char DateDeNaissance[100];
            char LieuDeNaissance[100];
            char AnneeBacc[10];
            char Genre[100];
            char CIN[100];
            char AdresseGit[100];
        }Etudiant;

        char** SepareeMot(char*mot,char ch);
        Etudiant* RemplirTabEt(FILE *file,int *c);
        void TrierTabEt(Etudiant *tab,int c);
        PC* RemplirTabPC(FILE *file,int *c);
        void EcritureDuFichier(FILE *file,Etudiant *tabEt,PC *tabPC,int c1,int c2);
        void modifInfo(Etudiant *tabEt,int TailleDuTabEt,PC *tabPC,int TailleDuTabPC);
        void AjoutInfo();
    
#endif
