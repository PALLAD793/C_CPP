#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct film
{
    char tytul[100];
    char n_r[100];
    char gatunek[100];
    int rok;
    int id;
    struct film *prev, *next;
    struct wypf *pf, *pierw, *pom;
} ;

struct uzyt
{
    int id_uz;
    char nazwisko[100];
    char imie[100];
    struct uzyt *prev, *next;
    struct wypu *pu, *pierw, *pom;
} ;

struct wypf
{
    struct uzyt *x;
    struct wypf *next;
};

struct wypu
{
    struct film *x;
    struct wypu *next;
};

void w_menu()
{
    printf("\n1. Dodaj film\n");
    printf("2. Dodaj uzytkownika\n");
    printf("3. Usun film\n");
    printf("4. Usun uzytkownika\n");
    printf("5. Edytuj film\n");
    printf("6. Edytuj uzytkownika\n");
    printf("7. Wyswietl liste filmow\n");
    printf("8. Wyswietl liste uzytkownikow\n");
    printf("9. Wypozyczanie filmow\n");
    printf("10. Zakoncz program\n ");
}

int main()
{
    int p, popr, nast_f=0, nast_u=0, film_us, film_mod, uz_mod, uz_us, wu, wf;
    char x;

    struct film *pierw_f = NULL, *ost_f = NULL;
    struct uzyt *pierw_u = NULL, *ost_u = NULL;

    w_menu();
    printf("\nPodaj numer polecenia, ktore chcesz wykonac:\n");
    popr = scanf("%d", &p);

    while(p != 10)
    {
        if(popr !=1)
        {
            printf("Wprowadzone dane sa nieprawidlowe\n");
            break;
        }

        if(p == 1)
        {
            struct film *nowy = (struct film*) malloc(sizeof(struct film));

            if(pierw_f == NULL)
            {
                nowy->id = (nast_f+1);
                printf("Numer ID filmu: %d\n", nowy->id);
                printf("Podaj tytul filmu\n");
                fgets(nowy->tytul, 99, stdin);
                fgets((nowy->tytul), 99, stdin);
                printf("Podaj nazwisko rezysera\n");
                fgets((nowy->n_r), 99, stdin);
                printf("Podaj gatunek filmu\n");
                fgets((nowy->gatunek), 99, stdin);
                printf("Podaj rok produkcji filmu\n");
                scanf("%d", &(nowy->rok));
                printf("Film dodany do bazy danych\n");
                nast_f++;

                nowy->pom = NULL;
                nowy->pf = NULL;
                nowy->pierw = NULL;
                nowy->next = NULL;
                nowy->prev = NULL;
                pierw_f = nowy;
                ost_f = nowy;
            }
            else
            {
                nowy->id = (nast_f+1);
                printf("Numer ID filmu: %d\n", nowy->id);
                printf("Podaj tytul filmu\n");
                fgets(nowy->tytul, 99, stdin);
                fgets(nowy->tytul, 99, stdin);
                printf("Podaj nazwisko rezysera\n");
                fgets((nowy->n_r), 99, stdin);
                printf("Podaj gatunek filmu\n");
                fgets((nowy->gatunek), 99, stdin);
                printf("Podaj rok produkcji filmu\n");
                scanf("%d", &(nowy->rok));
                printf("Film dodany do bazy danych\n");
                nast_f++;

                nowy->pf = NULL;
                nowy->pom = NULL;
                nowy->pierw = NULL;
                ost_f->next = nowy;
                nowy->prev = ost_f;
                nowy->next = NULL;
                ost_f = nowy;
            }
        }

        if(p == 2)
        {
            struct uzyt *nowy = (struct uzyt*) malloc(sizeof(struct uzyt));

            if(pierw_u == NULL)
            {
                nowy->id_uz = (nast_u+1);
                printf("Numer ID uzytkownika: %d\n", nowy->id_uz);
                printf("Podaj nazwisko uzytkownika\n");
                fgets((nowy->nazwisko), 99, stdin);
                fgets((nowy->nazwisko), 99, stdin);
                printf("Podaj imie uzytkownika\n");
                fgets((nowy->imie), 99, stdin);
                printf("Uzytkownik dodany do bazy danych\n");
                nast_u++;

                nowy->pu = NULL;
                nowy->pom = NULL;
                nowy->pierw = NULL;
                nowy->next = NULL;
                nowy->prev = NULL;
                pierw_u = nowy;
                ost_u = nowy;
            }
            else
            {
                nowy->id_uz = (nast_u+1);
                printf("Numer ID uzytkownika: %d\n", nowy->id_uz);
                printf("Podaj nazwisko uzytkownika\n");
                fgets((nowy->nazwisko), 99, stdin);
                fgets((nowy->nazwisko), 99, stdin);
                printf("Podaj imie uzytkownika\n");
                fgets((nowy->imie), 99, stdin);
                printf("Uzytkownik dodany do bazy danych\n");
                nast_u++;

                nowy->pu = NULL;
                nowy->pom = NULL;
                nowy->pierw = NULL;
                ost_u->next = nowy;
                nowy->prev = ost_u;
                nowy->next = NULL;
                ost_u = nowy;
            }
        }

        if(p == 3)
        {
            if(pierw_f != NULL)
            {
                struct film *wyp = pierw_f;

                while(wyp != NULL)
                {
                    printf("Film o numerze ID %d\nTytul: %sNazwisko rezysera: %sGatunek: %sRok produkcji: %d\n\n", wyp->id, wyp->tytul, wyp->n_r, wyp->gatunek, wyp->rok);
                    wyp = wyp->next;
                }

                printf("Podaj ID filmu, ktory chcesz usunac:\n");
                scanf("%d", &film_us);

                if(film_us <= nast_f && film_us > 0)
                {
                    wyp = pierw_f;

                    while(wyp->id != film_us)
                    {
                        wyp = wyp->next;
                        if(wyp == NULL) break;
                    }

                    if(wyp != NULL)
                    {
                        wyp->pf = wyp->pierw;

                        while(wyp->pf != NULL)
                        {
                            struct uzyt *wyp14 = pierw_u;

                            while(wyp14->id_uz != wyp->pf->x->id_uz)
                            {
                                wyp14 = wyp14->next;
                                if(wyp14 == NULL ) break;
                            }
                            wyp14->pu = wyp14->pierw;
                            while(wyp14->pu->next->x->id != wyp->id)
                            {
                                wyp14->pu = wyp14->pu->next;
                                if(wyp14->pu->next == NULL) break;
                            }
                            if(wyp14->pu->x->id == wyp->id && wyp14->pierw != wyp14->pu)
                            {
                                wyp14->pom = wyp14->pu;
                                wyp14->pierw = wyp14->pu->next;
                                free(wyp14->pom);
                                wyp14->pu = NULL;
                            }
                            else if(wyp14->pierw == wyp14->pu)
                            {
                                wyp14->pom = wyp14->pierw;
                                wyp14->pierw = wyp14->pierw->next;
                                free(wyp14->pom);
                            }
                            else if(wyp14->pu->next != NULL)
                            {
                                wyp14->pom = wyp14->pu->next;
                                wyp14->pu->next = wyp14->pu->next->next;
                                free(wyp14->pom);
                            }
                            else if(wyp14->pu->next == NULL && wyp14->pierw != wyp14->pu)
                            {
                                wyp14->pom = wyp14->pu;
                                wyp14->pierw = NULL;
                                free(wyp14->pom);
                            }

                            wyp->pf = wyp->pf->next;
                        }
                    }

                    if(wyp == NULL)
                    {
                        printf("Taki film nie istnieje\n");
                    }
                    else if(wyp == pierw_f && wyp != ost_f)
                    {
                        pierw_f = wyp->next;
                        pierw_f->prev = NULL;
                        printf("Film usuniety z bazy danych\n");
                        free(wyp);
                    }
                    else if(wyp == ost_f && wyp != pierw_f)
                    {
                        ost_f = wyp->prev;
                        ost_f->next = NULL;
                        printf("Film usuniety z bazy danych\n");
                        free(wyp);
                    }
                    else if(wyp != pierw_f && wyp != ost_f)
                    {
                        (wyp->prev)->next = wyp->next;
                        (wyp->next)->prev = wyp->prev;
                        printf("Film usuniety z bazy danych\n");
                        free(wyp);
                    }
                    else
                    {
                        pierw_f = NULL;
                        ost_f = NULL;
                        printf("Film usuniety z bazy danych\n");
                        free(wyp);
                    }



                }
                else printf("Taki film nie istnieje\n");

            }
            else printf("Brak filmow w bazie danych\n");
        }

        if(p == 4)
        {
            if(pierw_u != NULL)
            {
                struct uzyt *wyp1 = pierw_u;

                while(wyp1 != NULL)
                {
                    printf("Uzytkownik o numerze ID %d:\nNazwisko: %sImie: %s\n", wyp1->id_uz, wyp1->nazwisko, wyp1->imie);
                    wyp1 = wyp1->next;
                }
                printf("Podaj numer uzytkownika, ktorego chcesz usunac\n");
                scanf(" %d", &uz_us);

                if(uz_us <= nast_u && uz_us > 0)
                {

                    wyp1 = pierw_u;

                    while(wyp1->id_uz != uz_us)
                    {
                        wyp1 = wyp1->next;
                        if(wyp1 == NULL) break;
                    }

                    if(wyp1 == NULL)
                    {
                        printf("Taki uzytkownik nie istnieje\n");
                    }
                    else if(wyp1 == pierw_u && wyp1 != ost_u)
                    {
                        pierw_u = wyp1->next;
                        pierw_u->prev = NULL;
                        printf("Uzytkownik usuniety z bazy danych\n");
                        free(wyp1);
                    }
                    else if(wyp1 == ost_u && wyp1 != pierw_u)
                    {
                        ost_u = wyp1->prev;
                        ost_u->next = NULL;
                        printf("Uzytkownik usuniety z bazy danych\n");
                        free(wyp1);
                    }
                    else if(wyp1 != pierw_u && wyp1 != ost_u)
                    {
                        (wyp1->prev)->next = wyp1->next;
                        (wyp1->next)->prev = wyp1->prev;
                        printf("Uzytkownik usuniety z bazy danych\n");
                        free(wyp1);
                    }
                    else
                    {
                        pierw_u = NULL;
                        ost_u = NULL;
                        printf("Uzytkownik usuniety z bazy danych\n");
                        free(wyp1);
                    }

                }
                else printf("Uzytkownik o danym ID nie istnieje\n");
            }
            else printf("Brak uzytkownikow w bazie danych\n");
        }

        if(p == 5)
        {
            if(pierw_f != NULL)
            {
                struct film *wyp5 = pierw_f;

                while(wyp5 != NULL)
                {
                    printf("Film o numerze ID %d\nTytul: %sNazwisko rezysera: %sGatunek: %sRok produkcji: %d\n\n", wyp5->id, wyp5->tytul, wyp5->n_r, wyp5->gatunek, wyp5->rok);
                    wyp5 = wyp5->next;
                }

                printf("\nPodaj ID filmu, ktory chcesz zmodyfikowac\n");
                scanf("%d", &film_mod);

                wyp5 = pierw_f;

                while(wyp5->id != film_mod)
                {
                    wyp5 = wyp5->next;
                    if(wyp5 == NULL) break;
                }

                if (film_mod <= nast_f && film_mod > 0 && wyp5 != NULL)
                {


                    printf("Ktore informacje chcesz zmienic?\n a. Tytul\n b. Rezyser\n c. Gatunek\n d. Rok produkcji\nWybierz odpowiednia litere: \n");
                    scanf(" %c", &x);

                    if(x == 'a')
                    {
                        printf("Podaj nowy tytul\n");
                        fgets(wyp5->tytul, 99, stdin);
                        fgets(wyp5->tytul, 99, stdin);
                        printf("Zmiany zostaly zapisane\n");
                    }

                    if(x == 'b')
                    {
                        printf("Podaj nowego rezysera\n");
                        fgets((wyp5->n_r), 99, stdin);
                        fgets((wyp5->n_r), 99, stdin);
                        printf("Zmiany zostaly zapisane\n");
                    }

                    if(x == 'c')
                    {
                        printf("Podaj nowy gatunek\n");
                        fgets((wyp5->gatunek), 99, stdin);
                        fgets((wyp5->gatunek), 99, stdin);
                        printf("Zmiany zostaly zapisane\n");
                    }

                    if(x == 'd')
                    {
                        printf("Podaj nowy rok produkcji\n");
                        scanf("%d", &(wyp5->rok));
                        printf("Zmiany zostaly zapisane\n");
                    }
                }
                else printf("Film o danym ID nie istnieje\n");
            }
            else printf("Brak filmow do zedytowania\n");
        }

        if(p == 6)
        {
            if(pierw_u != NULL)
            {
                struct uzyt *wyp6 = pierw_u;

                while(wyp6 != NULL)
                {
                    printf("Uzytkownik o numerze ID %d:\nNazwisko: %sImie: %s\n", wyp6->id_uz, wyp6->nazwisko, wyp6->imie);
                    wyp6 = wyp6->next;
                }

                printf("\nPodaj ID uzytkownika, ktorego chcesz zmodyfikowac\n");
                scanf("%d", &uz_mod);

                wyp6 = pierw_u;

                while(wyp6->id_uz != uz_mod)
                {
                    wyp6 = wyp6->next;
                    if(wyp6 == NULL) break;
                }

                if (uz_mod <= nast_u && uz_mod > 0 && wyp6 != NULL)
                {
                    printf("Ktore informacje chcesz zmienic?\n a. Nazwisko\n b. Imie\nWybierz odpowiednia litere: \n");
                    scanf(" %c", &x);

                    if(x == 'a')
                    {
                        printf("Podaj nowe nazwisko\n");
                        fgets((wyp6->nazwisko), 99, stdin);
                        fgets((wyp6->nazwisko), 99, stdin);
                        printf("Zmiany zostaly zapisane\n");
                    }

                    if(x == 'b')
                    {
                        printf("Podaj nowe imie\n");
                        fgets((wyp6->imie), 99, stdin);
                        fgets((wyp6->imie), 99, stdin);
                        printf("Zmiany zostaly zapisane\n");
                    }

                }
                else printf("Uzytkownik o danym ID nie istnieje\n");
            }
            else printf("Brak uzytkownikow do zedytowania\n");
        }

        if(p == 7)
        {
            if(pierw_f == NULL) printf("Brak filmow w bazie danych\n");
            else
            {
                struct film *wyp3 = pierw_f;

                while(wyp3 != NULL)
                {
                    printf("Film o numerze ID %d\nTytul: %sNazwisko rezysera: %sGatunek: %sRok produkcji: %d\n\n", wyp3->id, wyp3->tytul, wyp3->n_r, wyp3->gatunek, wyp3->rok);
                    wyp3 = wyp3->next;
                }
            }
        }

        if(p == 8)
        {
            if(pierw_u == NULL) printf("Brak uzytkownikow w bazie danych\n");
            else
            {
                struct uzyt *wyp4 = pierw_u;

                while(wyp4 != NULL)
                {
                    printf("Uzytkownik o numerze ID %d:\nNazwisko: %sImie: %s\n", wyp4->id_uz, wyp4->nazwisko, wyp4->imie);
                    wyp4 = wyp4->next;
                }
            }
        }

        if(p == 9)
        {
            printf("Wybierz polecenie:\n");
            printf("a. Dodaj wypozyczenie filmu przez uzytkownika\n");
            printf("b. Usun wypozyczenie filmu przez uzytkownika\n");
            printf("c. Wyswietl filmy wypozyczone przez uzytkownika\n");
            printf("d. Wyswietl uzytkownikow, ktorzy wypozyczyli dany film\n");

            scanf(" %c", &x);

                if(x == 'a')
                {
                    if(pierw_u != NULL)
                    {
                        if(pierw_f != NULL)
                        {
                            struct uzyt *wyp7 = pierw_u;

                            while(wyp7 != NULL)
                            {
                                printf("Uzytkownik o numerze ID %d:\nNazwisko: %sImie: %s\n", wyp7->id_uz, wyp7->nazwisko, wyp7->imie);
                                wyp7 = wyp7->next;
                            }

                            printf("Podaj ID uzytkownika, ktory wypozycza film\n");
                            scanf("%d", &wu);

                            wyp7 = pierw_u;

                            while(wyp7->id_uz != wu)
                            {
                                wyp7 = wyp7->next;
                                if(wyp7 == NULL) break;
                            }

                            if(wu<=nast_u && wu>0 && wyp7 != NULL)
                            {
                                struct film *wyp8 = pierw_f;

                                while(wyp8 != NULL)
                                {
                                    printf("Film o numerze ID %d\nTytul: %sNazwisko rezysera: %sGatunek: %sRok produkcji: %d\n\n", wyp8->id, wyp8->tytul, wyp8->n_r, wyp8->gatunek, wyp8->rok);
                                    wyp8 = wyp8->next;
                                }

                                printf("Podaj ID filmu, ktory uzytkownik chce wypozyczyc\n");
                                scanf("%d", &wf);

                                wyp8 = pierw_f;

                                while(wyp8->id != wf)
                                {
                                    wyp8 = wyp8->next;
                                    if(wyp8 == NULL) break;
                                }

                                int er1=0, er2=0;

                                if(wf<=nast_f && wf>0 && wyp8 != NULL)
                                {
                                    if(wyp7->pierw == NULL)
                                    {

                                        wyp7->pu = (struct wypu*)malloc(sizeof(struct wypu));
                                        wyp7->pierw = wyp7->pu;
                                        wyp7->pu->next = NULL;
                                        wyp7->pu->x = wyp8;
                                        if(wyp8->pierw == NULL)
                                        {
                                            wyp8->pf = (struct wypf*)malloc(sizeof(struct wypf));
                                            wyp8->pierw = wyp8->pf;
                                            wyp8->pf->next = NULL;
                                            wyp8->pf->x = wyp7;
                                        }
                                        else
                                        {
                                            wyp8->pf = wyp8->pierw;
                                            if(wyp8->pierw->x == wyp7) er2++;
                                            while(wyp8->pf->next != NULL)
                                            {
                                                if(wyp8->pf->x == wyp7) er2++;
                                                wyp8->pf = wyp8->pf->next;
                                            }

                                            if(er2 == 0)
                                            {
                                                (wyp8->pf->next) = (struct wypf*)malloc(sizeof(struct wypf));
                                                wyp8->pf->next->next = NULL;
                                                wyp8->pf->next->x = wyp7;
                                            }
                                        }

                                    }
                                    else
                                    {

                                        wyp7->pu = wyp7->pierw;
                                        if(wyp7->pu->x == wyp8) er1++;
                                        while(wyp7->pu->next != NULL)
                                        {
                                            if(wyp7->pu->x == wyp8) er1++;
                                            wyp7->pu = wyp7->pu->next;
                                        }

                                        if(er1 == 0)
                                        {
                                            wyp7->pu->next = (struct wypu*)malloc(sizeof(struct wypu));
                                            wyp7->pu->next->x = wyp8;
                                            wyp7->pu->next->next = NULL;

                                            wyp8->pf = wyp8->pierw;

                                            if(wyp8->pf == NULL)
                                            {
                                                wyp8->pf = (struct wypf*)malloc(sizeof(struct wypf));
                                                wyp8->pierw = wyp8->pf;
                                                wyp8->pf->next = NULL;
                                                wyp8->pf->x = wyp7;
                                            }
                                            else
                                            {
                                                wyp8->pf = wyp8->pierw;
                                                if(wyp8->pierw->x == wyp7) er2++;
                                                while(wyp8->pf->next != NULL)
                                                {
                                                    if(wyp8->pf->x == wyp7) er2++;
                                                    wyp8->pf = wyp8->pf->next;
                                                }
                                                if(er2 == 0)
                                                {
                                                    wyp8->pf->next = (struct wypf*)malloc(sizeof(struct wypf));
                                                    wyp8->pf->next->next = NULL;
                                                    wyp8->pf->next->x = wyp7;
                                                }
                                            }
                                        }
                                    }

                                    if(er1 == 0 && er2 == 0) printf("Wypozyczenie pomyslnie dodane\n");
                                    else printf("Uzytkownik wypozyczyl juz ten film wczesniej\n");
                                }
                                else printf("Podany film nie istnieje\n");
                            }
                            else printf("Podany uzytkownik nie istnieje\n");
                        }
                        else printf("Brak filmow w bazie danych\n");
                    }
                    else printf("Brak uzytkownikow w bazie danych\n");

                }

                if(x == 'b')
                {
                    if(pierw_u == NULL) printf("Brak uzytkownikow w bazie danych\n");
                    else

                    {
                    struct uzyt *wyp9 = pierw_u;

                    while(wyp9 != NULL)
                    {
                        printf("Uzytkownik o numerze ID %d:\nNazwisko: %sImie: %s\n", wyp9->id_uz, wyp9->nazwisko, wyp9->imie);
                        wyp9 = wyp9->next;
                    }
                    printf("Podaj ID uzytkownika, ktorego wypozyczenie filmu chcesz usunac\n");
                    scanf("%d", &wu);

                    wyp9 = pierw_u;

                    while(wyp9->id_uz != wu)
                    {
                        wyp9 = wyp9->next;
                        if(wyp9 == NULL) break;
                    }

                    if(wyp9 == NULL) printf("Nie ma takiego uzytkownika\n");
                    else if(wyp9->pierw == NULL)
                    {
                        printf("Uzytkownik nie ma wypozyczonych zadnych filmow\n");
                    }
                    else
                    {
                        wyp9->pu = wyp9->pierw;
                        if(wyp9->pu == NULL) printf("Brak wypozyczonych filmow przez uzytkownika\n");
                        else{
                        while(wyp9->pu != NULL)
                        {
                            printf("Film o numerze ID %d\nTytul: %sNazwisko rezysera: %sGatunek: %sRok produkcji: %d\n\n", wyp9->pu->x->id, wyp9->pu->x->tytul, wyp9->pu->x->n_r, wyp9->pu->x->gatunek, wyp9->pu->x->rok);
                            wyp9->pu = wyp9->pu->next;
                        }
                        printf("Podaj ID filmu, ktorego wypozyczynie usunac\n");
                        scanf("%d", &wf);

                        wyp9->pu = wyp9->pierw;

                        while(wyp9->pu->x->id != wf)
                        {
                            if(wyp9->pu->next != NULL)
                            {
                                if(wyp9->pu->next->x->id == wf) break;
                            }

                            wyp9->pu = wyp9->pu->next;
                            if(wyp9->pu == NULL) break;
                        }

                        if(wyp9->pu == NULL)
                        {
                            printf("Film nie zostal wypozyczony przez uzytkownika\n");
                        }
                        else
                        {
                            if(wyp9->pu->x->id == wf)
                            {
                                if(wyp9->pu->next == NULL)
                                {
                                    wyp9->pierw = NULL;
                                    free(wyp9->pu);
                                    wyp9->pu = NULL;
                                }
                                else
                                {
                                    wyp9->pierw = wyp9->pu->next;
                                    free(wyp9->pu);
                                }

                            }
                            else if(wyp9->pu->next->x->id == wf)
                            {
                                wyp9->pom = wyp9->pu->next;
                                wyp9->pu->next = wyp9->pu->next->next;
                                free(wyp9->pom);
                                wyp9->pom = NULL;
                            }

                            struct film *wyp10 = pierw_f;

                            while(wyp10->id != wf)
                            {
                                wyp10 = wyp10->next;
                                if(wyp10 == NULL) break;
                            }

                            wyp10->pf = wyp10->pierw;

                            if(wyp10->pf->x->id_uz == wu)
                            {
                                if(wyp10->pf->next != NULL)
                                {
                                    wyp10->pierw = wyp10->pierw->next;
                                    free(wyp10->pf);
                                }
                                else
                                {
                                    wyp10->pierw = NULL;
                                    free(wyp10->pf);
                                    wyp10->pf = NULL;
                                }
                            }
                            else
                            {
                                while(wyp10->pf->next->x->id_uz != wu)
                                {
                                    wyp10->pf = wyp10->pf->next;
                                }

                                wyp10->pom = wyp10->pf->next;
                                wyp10->pf->next = wyp10->pf->next->next;
                                free(wyp10->pom);
                                wyp10->pom = NULL;
                            }

                            printf("Wypozyczenie filmu pomyslnie usuniete\n");
                        }

                    }
                    }
                }
                }

                if(x == 'c')
                {
                    struct uzyt *wyp11 = pierw_u;
                    if(pierw_u == NULL) printf("Brak uzytkownikow w bazie danych\n");
                    else{
                    while(wyp11 != NULL)
                    {
                        printf("Uzytkownik o numerze ID %d:\nNazwisko: %sImie: %s\n", wyp11->id_uz, wyp11->nazwisko, wyp11->imie);
                        wyp11 = wyp11->next;
                    }

                    printf("Podaj ID uzytkownika, ktorego chcesz zobaczyc wypozyczone filmy\n");
                    scanf("%d", &wu);

                    wyp11 = pierw_u;

                    while(wyp11->id_uz != wu)
                    {
                        wyp11 = wyp11->next;
                        if(wyp11 == NULL) break;
                    }

                    if(wyp11 == NULL) printf("Uzytkownik nie istnieje\n");
                    else if(wyp11->pu == NULL) printf("Uzytkownik nie ma wypozyczonych filmow\n");
                    else
                    {
                        printf("Filmy wypozyczone przez uzytkownika:\n");

                        wyp11->pu = wyp11->pierw;

                        while(wyp11->pu != NULL)
                        {
                            printf("Film o numerze ID %d\nTytul: %sNazwisko rezysera: %sGatunek: %sRok produkcji: %d\n\n", wyp11->pu->x->id, wyp11->pu->x->tytul, wyp11->pu->x->n_r, wyp11->pu->x->gatunek, wyp11->pu->x->rok);
                            wyp11->pu = wyp11->pu->next;
                        }
                    }
                }
                }

                if(x == 'd')
                {
                    struct film *wyp12 = pierw_f;
                    if(pierw_f == NULL) printf("Brak filmow w bazie danych\n");
                    else{
                    while(wyp12 != NULL)
                    {
                        printf("Film o numerze ID %d\nTytul: %sNazwisko rezysera: %sGatunek: %sRok produkcji: %d\n\n", wyp12->id, wyp12->tytul, wyp12->n_r, wyp12->gatunek, wyp12->rok);
                        wyp12 = wyp12->next;
                    }

                    printf("Podaj ID filmu, dla ktorego wyswietlic uzytkownikow, ktorzy go wypozyczyli\n");
                    scanf("%d", &wf);

                    wyp12 = pierw_f;

                    while(wyp12->id != wf)
                    {
                        wyp12 = wyp12->next;
                        if(wyp12 == NULL) break;
                    }
                    if(wyp12 == NULL) printf("Nie ma takiego filmu\n");
                    else if(wyp12->pf == NULL) printf("Nikt nie wypozyczyl tego filmu\n");
                    else
                    {
                        printf("Uzytkownicy, ktorzy wypozyczyli dany film:\n");

                        wyp12->pf = wyp12->pierw;
                        while(wyp12->pf != NULL)
                        {
                            printf("Uzytkownik o numerze ID %d:\nNazwisko: %sImie: %s\n", wyp12->pf->x->id_uz, wyp12->pf->x->nazwisko, wyp12->pf->x->imie);
                            wyp12->pf = wyp12->pf->next;
                        }
                    }
                }
                }
        }


        w_menu();
        printf("Podaj numer polecenia, ktore chcesz wykonac:\n");
        popr = scanf("%d", &p);

    }
    return 0;

}
