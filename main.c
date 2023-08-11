#include "Struct.h"

int main(){
    
    Etudiant *tabEt;
    int TailleDuTabEt;
    PC *tabPC;
    int TailleDuTabPC;
    FILE *file1,*file2;
    
    tabEt = RemplirTabEt(file1,&TailleDuTabEt);
    tabPC = RemplirTabPC(file1,&TailleDuTabPC);
    
    //AjoutInfo(file1,file2);
    
    TrierTabEt(tabEt,TailleDuTabEt);
    EcritureDuFichier(file1,tabEt,tabPC,TailleDuTabEt);
    
    return 0;
}