#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define FILENAME "empreint.txt"
#define MAX_LOANS 100

// Structure pour stocker les informations de l'emprunt
typedef struct {
    char bookID[20];
    char userID[20];
    time_t borrowDate;
    time_t dueDate;
    time_t returnDate;
    int isReturned;
} LoanRecord;

// Fonction pour lire les emprunts à partir d'un fichier
int readLoans(const char *filename, LoanRecord loans[], int maxLoans) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Erreur d'ouverture du fichier");
        return 0;
    }

    int count = 0;
    while (fscanf(file, "%s %s %ld %ld %ld %d",
                  loans[count].bookID,
                  loans[count].userID,
                  &loans[count].borrowDate,
                  &loans[count].dueDate,
                  &loans[count].returnDate,
                  &loans[count].isReturned) == 6 && count < maxLoans) {
        count++;
    }

    fclose(file);
    return count;
}

// Fonction pour écrire les emprunts dans un fichier
void writeLoans(const char *filename, LoanRecord loans[], int count) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Erreur d'ouverture du fichier");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s %s %ld %ld %ld %d\n",
                loans[i].bookID,
                loans[i].userID,
                loans[i].borrowDate,
                loans[i].dueDate,
                loans[i].returnDate,
                loans[i].isReturned);
    }

    fclose(file);
}

// Fonction pour calculer les jours de retard
int calculateLateDays(time_t returnDate, time_t dueDate) {
    return difftime(returnDate, dueDate) / (24 * 60 * 60);
}

// Fonction pour calculer les amendes
double calculateFine(int lateDays, double finePerDay) {
    return lateDays * finePerDay;
}

int main() {
    LoanRecord loans[MAX_LOANS];
    int loanCount = readLoans(FILENAME, loans, MAX_LOANS);

    if (loanCount == 0) {
        printf("Aucun emprunt trouvé.\n");
        return 1;
    }

    // Parcourir tous les emprunts et calculer les pénalités pour les retours tardifs
    for (int i = 0; i < loanCount; i++) {
        if (loans[i].isReturned && difftime(loans[i].returnDate, loans[i].dueDate) > 0) {
            int lateDays = calculateLateDays(loans[i].returnDate, loans[i].dueDate);
            double fine = calculateFine(lateDays, 0.50); // 0,50€ par jour de retard
            printf("Livre %s retourné tardivement par utilisateur %s : %d jours de retard. Amende : %.2f€\n",
                   loans[i].bookID, loans[i].userID, lateDays, fine);
        }
        // Notifications (simulation)
        if (difftime(time(NULL), loans[i].dueDate) > 0 && !loans[i].isReturned) {
            printf("Notification : Le livre %s emprunté par utilisateur %s est en retard.\n", loans[i].bookID, loans[i].userID);
        }
    }

    // Simuler un nouveau retour de livre
    printf("Simuler un retour de livre...\n");
    loans[1].returnDate = time(NULL); // Date actuelle comme date de retour
    loans[1].isReturned = 1;

    // Mettre à jour le fichier avec les nouvelles informations
    writeLoans(FILENAME, loans, loanCount);

    return 0;
}
