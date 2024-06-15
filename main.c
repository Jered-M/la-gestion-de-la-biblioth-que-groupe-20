#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Programme principal
int main() {
    char choix_connexion;
    printf("Voulez-vous vous connecter (c) ou vous inscrire (i) ? (Appuyez simplement sur Entrée pour passer au menu) : ");
    scanf("%c", &choix_connexion);

    if (choix_connexion == 'c') {
        connexion();
    } else if (choix_connexion == 'i') {
        inscription();
    }
     int choix;
    do {
        printf("--------------------biobiotheque-------------------");
        printf("\nMenu :\n");
        printf("1. Ajouter un livre\n");
        printf("2. Emprunter un livre\n");
        printf("3. Retourner un livre\n");
        printf("4. Penaliter \n");
        printf("5. reservation des livres\n ");
        printf("6. Afficher la liste des livres disponibles\n");
        printf("7. Description de groupe\n");
        printf("8. Quitter\n");
        printf("Entrez votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                ajouter_livre();
                break;
            case 2:
                emprunter_livre();
                break;
            case 3:
                retourner_livre();
                break;
            case 4:
                penalite();
                break;
            case 5:
                reservation();
                break;

            case 6:
                lister_livres();
                break;
            case 7:
                description_livres();
                break;
            case 8:
                printf("Merci d'avoir utilisé le système de gestion d'emprunt.\n");
                break;
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
        }
    } while (choix != 8);


    return 0;
}
