#include "Struct.h"

char** SepareeMot(char*mot,char ch){
	char **MotSeparee=malloc(sizeof(char*)*100);
	for(int i=0;i<100;i++){
		MotSeparee[i] = malloc(100);
	}
	int k=0,j=0;
	for(int i=0; i<strlen(mot); i++){
		if(mot[i]==ch){
			k++;j=0;
		}
		else {
			MotSeparee[k][j] = mot[i];
			j++;
		}
	}
	return MotSeparee;
}

Etudiant* RemplirTabEt(FILE *file,int *c){
	file = fopen("/home/tahina/ProgMrTahiry/INFO/InfoEtudiant.csv","r");
    Etudiant* tab = malloc(sizeof(Etudiant)*(NB_ETUDIANT+2));
	if(tab == NULL){
		fprintf(stderr,"erreur d'allocation\n");
		exit(1);
	}
    char ligne[1000];
	int i=0;
    while(fgets(ligne,1000,file) != NULL){
        char **tmp = SepareeMot(ligne,',');
		strcpy((tab+i)->Nom,tmp[0]);
		strcpy((tab+i)->Prenom,tmp[1]);
		strcpy((tab+i)->Tel,tmp[2]);
		strcpy((tab+i)->Email,tmp[3]);
		strcpy((tab+i)->Adresse,tmp[4]);
		strcpy((tab+i)->DateDeNaissance,tmp[5]);
		strcpy((tab+i)->LieuDeNaissance,tmp[6]);
		strcpy((tab+i)->AnneeBacc,tmp[7]);
		strcpy((tab+i)->Genre,tmp[8]);
		strcpy((tab+i)->CIN,tmp[9]);
		strcpy((tab+i)->AdresseGit,tmp[10]);
		(tab+i)->AdresseGit[strlen((tab+i)->AdresseGit)-1] = '\0';
		i++;
    }
	*c = i;
	fclose(file);
    return tab;
}

void TrierTabEt(Etudiant *tab,int c){
	tab->Numero = 0;
	for(int i=1;i<c;i++){
		for(int j=i+1;j<c;j++){
			Etudiant tmp;
			if(strcmp((tab+i)->Nom,(tab+j)->Nom) > 0){
				tmp = *(tab+i);
				*(tab+i) = *(tab+j);
				*(tab+j) = tmp;
			}
			(tab+i)->Numero = i;
		}
	}
	(tab+(c-1))->Numero = (c-1);
}

PC* RemplirTabPC(FILE *file,int *c){
	file = fopen("/home/tahina/ProgMrTahiry/INFO/InfoPC.csv","r");
    PC* tab = malloc(sizeof(PC)*(NB_ETUDIANT+2));
    char ligne[1000];
	int i=0;
    while(fgets(ligne,1000,file) != NULL){
        char **tmp = SepareeMot(ligne,';');
		strcpy((tab+i)->Mac,tmp[0]);
		strcpy((tab+i)->Label,tmp[1]);
		strcpy((tab+i)->Marque,tmp[2]);
		(tab+i)->Marque[strlen((tab+i)->Marque)-1] = '\0';
		i++;
    }
	*c = i;
	fclose(file);
    return tab;
}

void EcritureDuFichier(FILE *file,Etudiant *tabEt,PC *tabPC,int c){
	file = fopen("/home/tahina/ProgMrTahiry/INFO/Etudiant.csv","w");
	fprintf(file,"N° ;NOM;PRENOM;TELEPHONE;EMAIL;ADRESSE;DATE DE NAISSACE;LIEU DE NAISSANCE;ANNÉD DU BACC;GENRE;CIN;MAC;LABEL;MARQUE\n");
    for(int i=1;i<c;i++){
        int imp = 1;
        for(int j=0;j<NB_PC;j++){
            char **tmp = SepareeMot((tabPC+j)->Label,'-');
            if((tabEt+i)->Numero == atoi(*(tmp+1))){
                fprintf(file,"%d,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",(tabEt+i)->Numero,(tabEt+i)->Nom,(tabEt+i)->Prenom,(tabEt+i)->Tel,(tabEt+i)->Email,(tabEt+i)->Adresse,(tabEt+i)->DateDeNaissance,(tabEt+i)->LieuDeNaissance,(tabEt+i)->AnneeBacc,(tabEt+i)->Genre,(tabEt+i)->CIN,(tabEt+i)->AdresseGit,(tabPC+j)->Mac,(tabPC+j)->Label,(tabPC+j)->Marque);
                imp = 0;
            }
        }
        if(imp){
            fprintf(file,"%d,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,,,,\n",(tabEt+i)->Numero,(tabEt+i)->Nom,(tabEt+i)->Prenom,(tabEt+i)->Tel,(tabEt+i)->Email,(tabEt+i)->Adresse,(tabEt+i)->DateDeNaissance,(tabEt+i)->LieuDeNaissance,(tabEt+i)->AnneeBacc,(tabEt+i)->Genre,(tabEt+i)->CIN);
        }
    }
	fclose(file);
}

