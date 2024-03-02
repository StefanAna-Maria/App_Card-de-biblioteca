#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int clear_input_buffer()
{
    int ch;
    while (((ch = getchar()) != EOF) && (ch != '\n'));
    return ch;
}

typedef struct utilizatori
{
    char email[50];
    char parola[20];
    int  nr;
    char nrr[10];
    char data_imprumut[100];

}utilizator[10];

typedef struct carti
{
    char titlu_carte[100];
    int stoc;//?

}carti;

carti* carte;

int logare(struct utilizatori utilizator[], char email[], char parola[])
{
    int i = 0;
    for (i = 0; i < 5; i++)
    {
        //printf(utilizator[i].email);
        //printf(email);
        //printf(" ");
        //printf(utilizator[i].parola);
        //printf(parola);
        if (strcmp(utilizator[i].email, email) == 0 && strcmp(utilizator[i].parola, parola) == 0)
            return i;
    }
    return -1;
}

int meniu(struct utilizatori utilizator[], struct carti* carte, int a)
{
    printf("Bine ati venit, %s\n\n", utilizator[a].email);
    printf("MENIU:\n");
    printf("1.Numar carti nereturnate\n");
    printf("2.Doresc sa imprumut o carte\n");
    printf("3.Data ultimului imprumut\n");
    printf("4.Descarca PDF\n");//??
    printf("5.Iesi din aplicatie\n\nSelect: ");
    int nr = 0;
    int ok = 0;
    scanf("%d", &nr);

    switch (nr)
    {
    case 1:
    {
        //verifica numarul cartilor nereturnate
        printf("Numarul cartilor pe care nu le-ati returnat este de: %d carti\n\n", utilizator[a].nr);
        printf("1.Intoarce-te la pagina anterioara\n");
        printf("2.Iesi din aplicatie\n\n");
        scanf("%d", &ok);
        if ((int)ok == 1)
            meniu(utilizator, carte, a);
        else
            return 0;
    }
    break;//??

    case 2:
    {
        char titlu_carte[100];
        printf("Titlul cartii pe care doriti sa o imprumutati: ");
        scanf("%s", &titlu_carte);
        printf("\n");
        int valid = 0, i;
        //deschizi fisier citire
        for (i = 0; i < 20; i++)
        {
            //citesti din fisier titlu_carte
            if (strcmp(carte[i].titlu_carte, titlu_carte) == 0)
                valid = 1;
        }

        if (valid == 1)
            printf("Disponibil \n");
        else
            printf("Indisponibil \n");

        //int ok;

        printf("1.Intoarce-te la pagina anterioara\n");
        printf("2.Iesi din aplicatie\n\n");
        scanf("%d", &ok);
        if ((int)ok == 1)
            meniu(utilizator, carte, a);
        else
            return 0;
    }
    break;
    case 3:
    {
        printf("Data ultimului imprumut este: %s \n", utilizator[a].data_imprumut);
        printf("1.Intoarce-te la pagina anterioara\n");
        printf("2.Iesi din aplicatie\n\n");
        scanf("%d", &ok);
        if (ok == 1)
            meniu(utilizator, carte, a);
        else
            return 0;
    }
    break;
    case 4:
    {
        //alocare dinamica

        char carteCautata[100];
        int valid = 0;
        printf("Introdu cartea pe care vrei sa o descarci: ");
        clear_input_buffer();
        fgets(carteCautata,sizeof(carteCautata),stdin);
        for (int i = 0; i < 20; i++)
        {
            if (strcmp(carte[i].titlu_carte, carteCautata) == 0)
            {
                valid = 1;
            }
        }
        if (valid == 1)
        {
            printf("Cartea aceasta nu exista");
        }
        else
        {
            printf("Memorie insuficienta\n");
        }
        int ok;
        printf("1.Intoarce-te la pagina anterioara\n");
        printf("2.Iesi din aplicatie\n\n");
        scanf("%d", &ok);
        if (ok==1)
        {
            meniu(utilizator, carte, a);
        }
        else
        {
            return 0;
        }
        //break;
    }
    break;
    case 5:
    {
        printf("1.Intoarce-te la pagina anterioara\n");
        printf("2.Iesi din aplicatie\n\n");
        scanf("%d", &ok);
        if (ok == 1)
            meniu(utilizator, carte, a);
        else
            return 0;
    }
    break;
    default:
        return 0;

    }
}

int main()
{
    struct utilizatori utilizator[20];
    FILE* f1;
    f1 = fopen("utilizatori.txt", "r");
    if (f1 == NULL)
    {
        printf("%s", "baza de date inexistenta");
        return 1;
    }

    for (int i = 0; i < 5; i++)
    {
        char* p;
        //fscanf(f1,"%s %s %s %s",utilizator[i].email,utilizator[i].parola,&utilizator[i].nr,utilizator[i].data_imprumut);
        fscanf(f1, "%s %s %s %s", utilizator[i].email, utilizator[i].parola, utilizator[i].nrr, utilizator[i].data_imprumut);
        utilizator[i].nr = (int)strtol(utilizator[i].nrr, &p, 10);//converteste primul argument in nr in b10
        //p retine restul stringului neconv
    }
    fclose(f1);
    //printf(utilizator[0].email);
    //printf(utilizator[0].parola);
    //printf("%d",utilizator[0].nr);
    //printf(utilizator[0].data_imprumut);
    printf("Introduceti datele de autentificare:\n");
    FILE* f2;
    f2 = fopen("carti.txt", "r");
    if (f2 == NULL)
    {
        printf("%s", "baza de date inexistenta");
        return 1;
    }
    carte = (struct carti*)malloc(sizeof(struct carti) * 5);//aloc memorie dinamica in functie de numarul de produse
    if (carte == NULL)//daca pointerul returnat de malloc este null atunci nu am suficienta memorie
    {
        printf("Nu exista suficienta memorie.");
        return NULL;
    }
    free(carte);

    for (int i = 0; i < 20; i++)
    {
        fscanf(f2, "%s %d", &(carte + i)->titlu_carte, &(carte + i)->stoc);
        //fscanf(f2,"%s %d",carti[i].titlu_carte, carti[i].sold);
       // printf(carti.titlu_carte);
       // printf(carti.sold);
    }
    fclose(f2);
    char email[50], parola[20];
    int a = -2;
    printf("Email:");
    scanf("%s", &email);
    // printf(email);
    printf("Parola:");
    scanf("%s", &parola);
    a = logare(utilizator, email, parola);

    printf("\n%d\n", a);
    if (a == -1)
    {
        printf("Emailul sau parola sunt gresite!\n");
        // scanf("%d",&a);
        return 0;
    }
    meniu(utilizator, carte, a);
    fclose(f1);
    // int a;
    // scanf("%d",a);

    return 0;
}
