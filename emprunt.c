#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure pour représenter un livre
typedef struct {
    char titre[100];
    char auteur[100];
    char statut[20]; // "disponible" ou "emprunté"
} Livre;

// Fonction pour ajouter un livre
void ajouter_livre() {
    char titre[100], auteur[100];
    printf("Entrez le titre du livre : ");
    scanf("%s", titre);
    printf("Entrez le nom de l'auteur : ");
    scanf("%s", auteur);

    FILE *fichier = fopen("livre.txt", "a");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        exit(1);
    }
    fprintf(fichier, "%s,%s,disponible\n", titre, auteur);
    fclose(fichier);

    printf("Livre ajouté avec succès !\n");
}

// Fonction pour lister les livres disponibles
void lister_livres() {
    FILE *fichier = fopen("livre.txt", "r");
    if (fichier == NULL) {
        printf("Aucun livre trouvé.\n");
        return;
    }

    printf("Liste des livres disponibles :\n");
    char titre[100], auteur[100], statut[20];
    while (fscanf(fichier, "%[^,],%[^,],%s\n", titre, auteur, statut) != EOF) {
        if (strcmp(statut, "disponible") == 0) {
            printf("- %s par %s\n", titre, auteur);
        }
    }
    fclose(fichier);
}
 // Fonction pour emprunter un livre
void emprunter_livre() {
    char titre[100];
    printf("Entrez le titre du livre à emprunter : ");
    scanf("%s", titre);

    FILE *fichier_livres = fopen("livre.txt", "r+");
    if (fichier_livres == NULL) {
        printf("Aucun livre trouvé.\n");
        return;
    }

    FILE *fichier_emprunts = fopen("emprunt.txt", "a");
    if (fichier_emprunts == NULL) {
        printf("Erreur lors de l'ouverture du fichier des emprunts.\n");
        fclose(fichier_livres);
        return;
    }

    Livre livre;
    int trouve = 0;
    while (fscanf(fichier_livres, "%[^,],%[^,],%s\n", livre.titre, livre.auteur, livre.statut) != EOF) {
        if (strcmp(livre.titre, titre) == 0 && strcmp(livre.statut, "disponible") == 0) {
            trouve = 1;
            fseek(fichier_livres, -strlen(livre.statut) - 1, SEEK_CUR);
            fprintf(fichier_livres, "emprunté");
            fprintf(fichier_emprunts, "%s,%s\n", livre.titre, livre.auteur);
            printf("Livre emprunté avec succès !\n");
            break;
        }
    }

    fclose(fichier_livres);
    fclose(fichier_emprunts);

    if (!trouve) {
        printf("Livre non trouvé ou déjà emprunté.\n");
    }
}

// Fonction pour retourner un livre
void retourner_livre() {
    char titre[100];
    printf("Entrez le titre du livre à retourner : ");
    scanf("%s", titre);

    FILE *fichier_livres = fopen("livre.txt", "r+");
    if (fichier_livres == NULL) {
        printf("Aucun livre trouvé.\n");
        return;
    }

    FILE *fichier_emprunts = fopen("emprunt.txt", "r+");
    if (fichier_emprunts == NULL) {
        printf("Aucun emprunt trouvé.\n");
        fclose(fichier_livres);
        return;
    }

    Livre livre;
    int trouve = 1;
    while (fscanf(fichier_livres, "%[^,],%[^,],%s\n", livre.titre, livre.auteur, livre.statut) != EOF) {
        if (strcmp(livre.titre, titre) == 0 && strcmp(livre.statut, "emprunté") == 0) {
            trouve = 0;
            fseek(fichier_livres, -strlen(livre.statut) - 1, SEEK_CUR);
            fprintf(fichier_livres, "disponible");

            // Supprimer l'emprunt correspondant du fichier des emprunts
            FILE *fichier_temp = fopen("temp.txt", "w");
            if (fichier_temp == NULL) {
                printf("Erreur lors de l'ouverture du fichier temporaire.\n");
                fclose(fichier_livres);
                fclose(fichier_emprunts);
                return;
            }

            char titre_temp[100], auteur_temp[100];
            while (fscanf(fichier_emprunts, "%[^,],%[^,]\n", titre_temp, auteur_temp) != EOF) {
                if (strcmp(titre_temp, titre) != 0) {
                    fprintf(fichier_temp, "%s,%s\n", titre_temp, auteur_temp);
                }
            }

            fclose(fichier_temp);
            fclose(fichier_emprunts);
            remove("emprunt.txt");
            rename("temp.txt", "emprunt.txt");

            printf("Livre retourné avec succès !\n");
            break;
        }
    }

    fclose(fichier_livres);

    if (!trouve) {
        printf("Livre non trouvé ou déjà disponible.\n");
    }
}

void description_livres() {
    FILE *fichier = fopen("description.txt", "r");
}

