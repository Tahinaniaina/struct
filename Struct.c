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
	*c = 0;
	file = fopen("./InfoEtudiant.csv","r");
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
	*c=0;
	file = fopen("./InfoPC.csv","r");
    PC* tab = malloc(sizeof(PC)*(NB_ETUDIANT+2));
    char ligne[1000];
	int i=0;
    while(fgets(ligne,1000,file) != NULL){
        char **tmp = SepareeMot(ligne,',');
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

void EcritureDuFichier(FILE *file,Etudiant *tabEt,PC *tabPC,int c1,int c2){
	file = fopen("./Etudiant.csv","w");
	fprintf(file,"N° ,NOM,PRENOM,TELEPHONE,EMAIL,ADRESSE,DATE DE NAISSACE,LIEU DE NAISSANCE,ANNÉE DU BACC,GENRE,CIN;URL GIT,MAC,LABEL,MARQUE\n");
    for(int i=1;i<c1;i++){
        int imp = 1;
        for(int j=0;j<c2;j++){
            char **tmp = SepareeMot((tabPC+j)->Label,'-');
            if((tabEt+i)->Numero == atoi(*(tmp+1))){
                fprintf(file,"%d,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",(tabEt+i)->Numero,(tabEt+i)->Nom,(tabEt+i)->Prenom,(tabEt+i)->Tel,(tabEt+i)->Email,(tabEt+i)->Adresse,(tabEt+i)->DateDeNaissance,(tabEt+i)->LieuDeNaissance,(tabEt+i)->AnneeBacc,(tabEt+i)->Genre,(tabEt+i)->CIN,(tabEt+i)->AdresseGit,(tabPC+j)->Mac,(tabPC+j)->Label,(tabPC+j)->Marque);
                imp = 0;
            }
        }
        if(imp){
            fprintf(file,"%d,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,,,,\n",(tabEt+i)->Numero,(tabEt+i)->Nom,(tabEt+i)->Prenom,(tabEt+i)->Tel,(tabEt+i)->Email,(tabEt+i)->Adresse,(tabEt+i)->DateDeNaissance,(tabEt+i)->LieuDeNaissance,(tabEt+i)->AnneeBacc,(tabEt+i)->Genre,(tabEt+i)->CIN,(tabEt+i)->AdresseGit);
        }
    }
	fclose(file);
}

void modifInfo(Etudiant *tabEt,int TailleDuTabEt,PC *tabPC,int TailleDuTabPC){
	FILE *file1 = fopen("./InfoEtudiant.csv","w");
	FILE *file2 = fopen("./InfoPC.csv","w");
    for(int i=0;i<TailleDuTabEt;i++){
        fprintf(file1,"%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",(tabEt+i)->Nom,(tabEt+i)->Prenom,(tabEt+i)->Tel,(tabEt+i)->Email,(tabEt+i)->Adresse,(tabEt+i)->DateDeNaissance,(tabEt+i)->LieuDeNaissance,(tabEt+i)->AnneeBacc,(tabEt+i)->Genre,(tabEt+i)->CIN,(tabEt+i)->AdresseGit);
    }
	for(int j=0;j<TailleDuTabPC;j++){
        fprintf(file2,"%s,%s,%s\n",(tabPC+j)->Mac,(tabPC+j)->Label,(tabPC+j)->Marque);
    }
	fclose(file1);
	fclose(file2);
}

void AjoutInfo(){
	FILE *file,*file1,*file2;
	Etudiant *tabEt;
    int TailleDuTabEt;
    PC *tabPC;
    int TailleDuTabPC;
    tabEt = RemplirTabEt(file,&TailleDuTabEt);
    tabPC = RemplirTabPC(file,&TailleDuTabPC);
	int choice = 1;
	int i = TailleDuTabEt;
	int j = TailleDuTabPC;
	printf("Voulez vous ajouter ou modifier un infomation :\n[1] : Oui\n[2] : Non\n");
	char c[10];
	fgets(c,10,stdin);
	choice = atoi(c);
	if(choice != 1) choice = 0;
	while(choice){
		printf("[1] : Ajout de tout les info\n");
		printf("[2] : Ajout d'un élément spécifique ou modifier des élément\n");
		printf("Autre numéro pour quiter\n");
		fgets(c,10,stdin);
		choice = atoi(c);
		switch(choice){
			case 1:
				printf("Entrer tout vos information :\n");
				printf("INFO SUR L'ÉTUDIANT:\n");
				printf("NOM :");fgets((tabEt+i)->Nom,100,stdin);(tabEt+i)->Nom[strlen((tabEt+i)->Nom)-1] = '\0';
				printf("PRENOM :");fgets((tabEt+i)->Prenom,100,stdin);(tabEt+i)->Prenom[strlen((tabEt+i)->Prenom)-1] = '\0';
				printf("TÉLEPHONE :");fgets((tabEt+i)->Tel,100,stdin);(tabEt+i)->Tel[strlen((tabEt+i)->Tel)-1] = '\0';
				printf("EMAIL :");fgets((tabEt+i)->Email,100,stdin);(tabEt+i)->Email[strlen((tabEt+i)->Email)-1] = '\0';
				printf("ADRESSE :");fgets((tabEt+i)->Adresse,100,stdin);(tabEt+i)->Adresse[strlen((tabEt+i)->Adresse)-1] = '\0';
				printf("DATE DE NAISSANCE :");fgets((tabEt+i)->DateDeNaissance,100,stdin);(tabEt+i)->DateDeNaissance[strlen((tabEt+i)->DateDeNaissance)-1] = '\0';
				printf("LIEU DE NAISSANCE :");fgets((tabEt+i)->LieuDeNaissance,100,stdin);(tabEt+i)->LieuDeNaissance[strlen((tabEt+i)->LieuDeNaissance)-1] = '\0';
				printf("ANNÉE D'OBTENTION DE BACCALAUREAT :");fgets((tabEt+i)->AnneeBacc,10,stdin);(tabEt+i)->AnneeBacc[strlen((tabEt+i)->AnneeBacc)-1] = '\0';
				printf("GENRE :");fgets((tabEt+i)->Genre,100,stdin);(tabEt+i)->Genre[strlen((tabEt+i)->Genre)-1] = '\0';
				printf("N° CIN :");fgets((tabEt+i)->CIN,100,stdin);(tabEt+i)->CIN[strlen((tabEt+i)->CIN)-1] = '\0';
				printf("ADRESSE GIT HUB :");fgets((tabEt+i)->AdresseGit,100,stdin);(tabEt+i)->AdresseGit[strlen((tabEt+i)->AdresseGit)-1] = '\0';
				printf("INFO SUR LE PC:\n");
				printf("ADRESS MAC:");fgets((tabPC+j)->Mac,100,stdin);(tabPC+j)->Mac[strlen((tabPC+j)->Mac)-1] = '\0';
				printf("MARQUE DU PC:");fgets((tabPC+j)->Marque,100,stdin);(tabPC+j)->Marque[strlen((tabPC+j)->Marque)-1] = '\0';
				printf("VOTRE LABEL:");fgets((tabPC+j)->Label,100,stdin);(tabPC+j)->Label[strlen((tabPC+j)->Label)-1] = '\0';
				i++;j++;
				TailleDuTabEt++;
				TailleDuTabPC++;
				break;
			case 2:
				TrierTabEt(tabEt,TailleDuTabEt);
				printf("Entrer votre numéro :");
				fgets(c,10,stdin);
				int num = atoi(c);
				printf("NOM : %s\t PRENOM : %s\tTÉLEPHONE : %s\tEMAIL : %s\tADRESSE : %s\tDATE DE NAISSANCE : %s\tLIEU DE NAISSANCE : %s\tANNÉE D'OBTENTION DE BACCALAUREAT : %s\tANNÉE D'OBTENTION DE BACCALAUREAT : %s\tGENRE : %s\tN° CIN : %s\n",(tabEt+num)->Nom,(tabEt+num)->Prenom,(tabEt+num)->Tel,(tabEt+num)->Email,(tabEt+num)->Adresse,(tabEt+num)->DateDeNaissance,(tabEt+num)->LieuDeNaissance,(tabEt+num)->AnneeBacc,(tabEt+num)->Genre,(tabEt+num)->CIN,(tabEt+num)->AdresseGit);
				printf("Entrer le numéro que vous vous voulez ajouter ou modifier\n");
				printf("[1] : NOM\n");
				printf("[2] : PRENOM\n");
				printf("[3] : TÉLEPHONE\n");
				printf("[4] : EMAIL\n");
				printf("[5] : ADRESSE\n");
				printf("[6] : DATE DE NAISSANCE\n");
				printf("[7] : LIEU DE NAISSANCE\n");
				printf("[8] : ANNÉE D'OBTENTION DE BACCALAUREAT\n");
				printf("[9] : GENRE\n");
				printf("[10] : N° CIN\n");
				printf("[11] : ADRESSE GIT HUB\n");
				printf("INFO SUR LE PC\n");
				printf("[12] : ADRESS MAC\n");
				printf("[13] : MARQUE DU PC\n");
				printf("[14] : VOTRE LABEL\n");
				fgets(c,10,stdin);
				int n = atoi(c);
				switch(n){
					case 1 :
						printf("Entrer votre ");
						printf("NOM :");fgets((tabEt+num)->Nom,100,stdin);(tabEt+num)->Nom[strlen((tabEt+num)->Nom)-1] = '\0';
						break;
					case 2 :
						printf("Entrer votre ");
						printf("PRENOM :");fgets((tabEt+num)->Prenom,100,stdin);(tabEt+num)->Prenom[strlen((tabEt+num)->Prenom)-1] = '\0';
						break;
					case 3 :
						printf("Entrer votre ");
						printf("TÉLEPHONE :");fgets((tabEt+num)->Tel,100,stdin);(tabEt+num)->Tel[strlen((tabEt+num)->Tel)-1] = '\0';
						break;
					case 4 :
						printf("Entrer votre ");
						printf("EMAIL :");fgets((tabEt+num)->Email,100,stdin);(tabEt+num)->Email[strlen((tabEt+num)->Email)-1] = '\0';
						break;
					case 5 :
						printf("Entrer votre ");
						printf("ADRESSE :");fgets((tabEt+num)->Adresse,100,stdin);(tabEt+num)->Adresse[strlen((tabEt+num)->Adresse)-1] = '\0';
						break;
					case 6 :
						printf("Entrer votre ");
						printf("DATE DE NAISSANCE :");fgets((tabEt+num)->DateDeNaissance,100,stdin);(tabEt+num)->DateDeNaissance[strlen((tabEt+num)->DateDeNaissance)-1] = '\0';
						break;
					case 7 :
						printf("Entrer votre ");
						printf("LIEU DE NAISSANCE :");fgets((tabEt+num)->LieuDeNaissance,100,stdin);(tabEt+num)->LieuDeNaissance[strlen((tabEt+num)->LieuDeNaissance)-1] = '\0';
						break;
					case 8 :
						printf("Entrer votre ");
						printf("ANNÉE D'OBTENTION DE BACCALAUREAT :");fgets((tabEt+num)->AnneeBacc,10,stdin);(tabEt+num)->AnneeBacc[strlen((tabEt+num)->AnneeBacc)-1] = '\0';
						break;
					case 9 :
						printf("Entrer votre ");
						printf("GENRE :");fgets((tabEt+num)->Genre,100,stdin);(tabEt+num)->Genre[strlen((tabEt+num)->Genre)-1] = '\0';
						break;
					case 10 :
						printf("Entrer votre ");
						printf("N° CIN :");fgets((tabEt+num)->CIN,100,stdin);(tabEt+num)->CIN[strlen((tabEt+num)->CIN)-1] = '\0';
						break;
					case 11 :
						printf("Entrer votre ");
						printf("ADRESSE GIT HUB :");fgets((tabEt+num)->AdresseGit,100,stdin);(tabEt+num)->AdresseGit[strlen((tabEt+num)->AdresseGit)-1] = '\0';
						break;
					case 12 :
						printf("Entrer votre ");
						printf("ADRESS MAC:");fgets((tabPC+j)->Mac,100,stdin);(tabPC+j)->Mac[strlen((tabPC+j)->Mac)-1] = '\0';
						break;
					case 13 :
						printf("Entrer votre ");
						printf("MARQUE DU PC:");fgets((tabPC+j)->Marque,100,stdin);(tabPC+j)->Marque[strlen((tabPC+j)->Marque)-1] = '\0';
						break;
					case 14 :
						printf("Entrer votre ");
						printf("VOTRE LABEL:");fgets((tabPC+j)->Label,100,stdin);(tabPC+j)->Label[strlen((tabPC+j)->Label)-1] = '\0';
						break;
					default :break;
				}
				break;
			default :
				choice = 0;
				break;
		}
	}
	modifInfo(tabEt,TailleDuTabEt,tabPC,TailleDuTabPC);
	tabEt = RemplirTabEt(file,&TailleDuTabEt);
    tabPC = RemplirTabPC(file,&TailleDuTabPC);
	TrierTabEt(tabEt,TailleDuTabEt);
	EcritureDuFichier(file,tabEt,tabPC,i,j);
}
