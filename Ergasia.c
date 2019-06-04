#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define DBase "forofygades.dbs"
#define StatFile "statistika.txt"
#define JailFile "fylaki.txt"

typedef enum {False, True} bool;

struct taxpayer
{
    char name[51];
    bool polyteknos;
    short arithmos_teknwn;
    float income;
    float debt;

};

/*
Edw ftiaxnw enan forologoumeno, dosmenwn twn xaraktiristikwn tou.
Skeftika na dexetai mono arithmo teknwn kai an einai >3 tote na ton vazei poltekno
Kai an oxi na vazei 0, alla opws diavaza tin askisi den itan kat'anagki etsi,
mou fanike san na diaxwrizontan ta 2 opote ta afisa anexartita.
*/
struct taxpayer *Create_taxpayer(char name[51], bool polyteknos, short arithmos_teknwn, float income, float debt)
{
    struct taxpayer *tp=malloc(sizeof(struct taxpayer));
    tp->arithmos_teknwn= arithmos_teknwn;
    tp->income=income;
    tp->debt=debt;
    tp->polyteknos=polyteknos;
    strcpy(tp->name,name);
    
    return tp;

}

//Edw typwnw ta stoixeia enos forologoumenou
void PrintTaxpayer(struct taxpayer *tp)
{
    printf("\n------------------------------\n");
    printf("Onoma: %s\n",tp->name);
    printf("Polyteknos: %d\n",tp->polyteknos);
    printf("Arithmos Teknwn: %d\n",tp->arithmos_teknwn);
    printf("Eisodima: %.1f\n",tp->income);
    printf("Xreos: %.1f\n",tp->debt);
    printf("------------------------------\n");
}



/*
Edw dimiourgw mia vasi dedomenwn. 
DEN EINAI I VASI POU XRISIMOPOIW. Afti tin ekana grafontas ena programma
se Python to opoio mou egrapse ena programma se C pou mou egrapse 
karfwta(opws to deigma apo katw) 1500 entries, me tyxaia onomata,
tyxaio arithmo paidiwn, eisodimatos kai xrewn, xrisimopoiontas diwnymiki katanomi
etsi wste na einai, oso ginetai,diladi, pio realistika, enw taftoxrona na vgazoun
kai arketa apotelesmata wste na exoun eggrafes ta 2 .txt pou dimiougithikan.
*/
void createDB()
{
    struct taxpayer *taxpayers[20];
    FILE *fp = NULL;
    char Name[20][51] = {"Takis Tatakis", "Sakis Souvlakis", "Iwanna Karagianni", "Vasilis Karavasilis", "Sotiris Notsotirisafterall", "Makis Magkouras", "Tolis Sketos", "Tolis OnTheRocks", "Pasxos Mandravellis", "Bruce Batmanidis", "Xatzi Fragetas", "Karolos Magnos", "Miltos Davloutsikis", "Dora iExerevnitria", "Thorin Oxeiaspis", "Chew Baccas", "Boba Fett", "Ioannis Travoltas", "O Lanister", "Tony Trombony"};
    short Tekna[20] = {1, 2, 4, 0, 5, 2, 1, 2, 3, 0, 1, 2, 3, 4, 2, 3, 1, 3, 1, 4};    
    bool Polyte[20] = {0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1};
    float Income[20] = {22000, 35000.0, 12000, 18000, 49000, 9000, 7500, 12000, 6000, 18000, 32000, 38000, 35000, 32000, 15000, 15000, 12000, 13000, 22000, 12000};
    float Debt[20] = {12000, 300000, 150000, 22000, 15000, 12000, 100000, 15000, 500, 13000, 270000, 251000, 148000, 32000, 500, 130, 12500, 250, 0, 150000};
    fp = fopen(DBase, "w+");
    for (int i = 0; i < 20; i++)
    {
        taxpayers[i]=Create_taxpayer(Name[i],Polyte[i],Tekna[i],Income[i],Debt[i]);
        fwrite(taxpayers[i], sizeof(struct taxpayer), 1, fp);
        //PrintTaxpayer(taxpayers[i]);
    }
    fclose(fp);
}


//Edw kanw ta statistika. Otan zitithike pososto gia touw forofygades me
//3 paidia kai >100.000 xreos, to ypologisa san pososto epi oloklirou tou plithous
//tis vasis.
void makeStats()
{
    int tetracount=0,i=0,tric=0;
    float percent=0;
    FILE *dbfp =NULL;
    FILE *statfp=NULL;
    struct taxpayer tp;
    dbfp= fopen(DBase,"r");
    while (fread(&tp,sizeof(struct taxpayer),1,dbfp))
    {
        i++;
        if (tp.arithmos_teknwn==4)
            tetracount++;
        if (tp.arithmos_teknwn==3 && tp.debt>100000)
            tric++;

    }
    percent=((float)tric/(float)i);
    statfp=fopen(StatFile,"w+");
    fprintf(statfp,"Debtors with 4 children: %d\n",tetracount);
    fprintf(statfp,"Debtors with 3 children and debt higher than 100.000: %d \n Debtors with 3 children and debt higher than 100.000 as percentage of total debtors: %.3f%%",tric,percent*100);
    fclose(dbfp);
    fclose(statfp);
}


//Edw vazoume osous einai na mpoune fylaki. 
void makePrison()
{
    FILE *dbfp =NULL;
    FILE *jailfp=NULL;
    struct taxpayer tp;
    dbfp=fopen(DBase,"r");
    jailfp=fopen(JailFile,"w+");
    while (fread(&tp,sizeof(struct taxpayer),1,dbfp))
    {
        if (tp.arithmos_teknwn<3 && tp.debt>250000 && tp.income<30000)
            fprintf(jailfp,"%s \t Debt: %.1f\n",tp.name,tp.debt);
    }
    fclose(dbfp);
    fclose(jailfp);

}
//Afti i synartisi typwnei oli ti vasi(einai 1500 atoma, opote an to trexte
// tha thelei ligo scroll up gia na ta deite ola)
void PrintDb()
{
    FILE *fp=NULL;
    struct taxpayer tp;
    fp= fopen(DBase,"r");
    while (fread(&tp,sizeof(struct taxpayer),1,fp))
    {
        PrintTaxpayer(&tp);
    }
}

/*
Sti main Synartisi exw apenergopoiisei ti synartisi createDB giati
exw deftero arxeio pou ftiaxnei megalyteri vasi kai afto to deftero xrisimopoiisa.
Einai edw gia logous plirotitas tis askisis me vasi tin ekfwnisi.
To printDb episis den einai aparaitito, itan edw arxika gia na mporw na elenxw
ean oi kataxwriseis kai to diavasma apo kai pros ti vasi doulevoun swsta.
To afisa omws, gia na min exei to programma keno parathyro ektelesis.
*/
int main()
{
    //createDB(); //Edw xrisimopoiw to programma makedb apo to makedb.c gia na gemisw ti vasi
    PrintDb();
    makeStats();
    makePrison();
}