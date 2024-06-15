#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define MAX_USERS 100

struct User {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
};

struct User users[MAX_USERS];
int numUsers = 0;

void inscription() {
    printf("Bienvenue ! Veuillez vous inscrire.\n");
    printf("Entrez votre nom d'utilisateur : ");
    scanf("%s", users[numUsers].username);
    printf("Entrez votre mot de passe : ");
    scanf("%s", users[numUsers].password);
    numUsers++;

    // Enregistrement des utilisateurs dans un fichier
    enregistrerUtilisateursDansFichier();
}

void connexion() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    printf("Bienvenue ! Veuillez vous connecter.\n");
    printf("Entrez votre nom d'utilisateur : ");
    scanf("%s", username);
    printf("Entrez votre mot de passe : ");
    scanf("%s", password);

    FILE *fichier;
    fichier = fopen("utilisateurs.txt", "r");
    if (fichier == NULL) {
        printf("Impossible d'ouvrir le fichier utilisateurs.txt\n");
        exit(1);
    }

    char buffer[MAX_USERNAME_LENGTH + MAX_PASSWORD_LENGTH + 2]; // +2 pour ':' et '\n'

    while (fgets(buffer, sizeof(buffer), fichier)) {
        char *token = strtok(buffer, ":");
        if (strcmp(token, username) == 0) {
            token = strtok(NULL, ":"); // Obtention du mot de passe
            token[strlen(token) - 1] = '\0'; // Suppression du saut de ligne à la fin
            if (strcmp(token, password) == 0) {
                printf("Connexion réussie !\n");
                fclose(fichier);
                return;
            } else {
                printf("Mot de passe incorrect.\n");
                fclose(fichier);
                return;
            }
        }
    }

    printf("Nom d'utilisateur non trouvé.\n");
    fclose(fichier);
}

void enregistrerUtilisateursDansFichier() {
    FILE *fichier;
    fichier = fopen("utilisateurs.txt", "w");
    if (fichier == NULL) {
        printf("Impossible d'ouvrir le fichier utilisateurs.txt\n");
        exit(1);
    }

    int i;
    for (i = 0; i < numUsers; i++) {
        fprintf(fichier, "%s:%s\n", users[i].username, users[i].password);
    }
    fclose(fichier);
}
