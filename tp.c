#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure pour stocker les informations des réservations
struct Reservation {
    char nomLivre[50];
    char nomAuteur[50];
    char date[40];
};

// Fonction pour enregistrer une réservation dans un fichier
void enregistrer_reservation(struct Reservation r) {
    FILE *fp;
    fp = fopen("reservations.txt", "a"); // Ouverture en mode ajout à la fin du fichier

    if (fp == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    // Écriture des données dans le fichier
    fprintf(fp, "%s;%s;%s\n", r.nomLivre, r.nomAuteur, r.date);

    fclose(fp); // Fermeture du fichier
}

// Fonction pour réserver un livre
void reservation() {
    struct Reservation res;
    printf("\n\n\t\t\t\t\t********** RESERVATION D'UN LIVRE **********\n\n\n");

    printf("Entrez le nom du livre : ");
    scanf(" %[^\n]", res.nomLivre);

    printf("Entrez le nom de l'auteur : ");
    scanf(" %[^\n]", res.nomAuteur);

    printf("Entrez la date actuelle : ");
    scanf(" %[^\n]", res.date);

    // Enregistrement de la réservation dans un fichier
    enregistrer_reservation(res);

    printf("\n\n\t\t\t\t\tLe livre a été réservé avec succès!\n\n");
}

// Fonction pour afficher les réservations depuis le fichier
void afficher_reservations() {
    FILE *fp;
    char ligne[150]; // Supposant que chaque ligne du fichier ne dépasse pas 150 caractères

    printf("\n\n\t\t\t\t\t********** LISTE DES RESERVATIONS **********\n\n\n");

    fp = fopen("reservations.txt", "r");

    if (fp == NULL) {
        printf("Aucune réservation trouvée.\n");
        return;
    }

    printf("Nom du livre\t\tNom de l'auteur\t\tDate\n");
    printf("-----------------------------------------------------------------\n");

    while (fgets(ligne, sizeof(ligne), fp)) {
        char *nomLivre = strtok(ligne, ";");
        char *nomAuteur = strtok(NULL, ";");
        char *date = strtok(NULL, "\n");

        printf("%-20s\t%-20s\t%-10s\n", nomLivre, nomAuteur, date);
    }

    fclose(fp);
}

// Fonction principale pour l'accueil et le menu
void accueil() {
    int choix;

    printf("\n\n\t\t\t\t\t********** GESTION DES RESERVATIONS **********\n\n\n");
    printf("1. Réserver un livre\n");
    printf("2. Afficher les réservations\n");
    printf("3. Quitter\n");
    printf("\n\n\nVotre choix : ");
    scanf("%d", &choix);

    switch (choix) {
        case 1:
            reservation();
            break;
        case 2:
            afficher_reservations();
            break;
        case 3:
            exit(0); // Quitter le programme
        default:
            printf("Veuillez saisir un choix valide.\n");
            break;
    }
}


