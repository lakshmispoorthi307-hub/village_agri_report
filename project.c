#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to store farmer details
struct Farmer {
    int id;
    char name[50];
    char fatherName[50];
    float ownLand, leasedLand;
    float boreLand, canalLand, dryLand;
    int crops;
    float income;
    int animals;
    char soilTest[5]; // Yes / No
    char category[20];
};

// Structure to store village details
struct Village {
    char name[50];
    char mandal[50];
    char district[50];
    char state[50];
    int pin;
};

// Function to classify farmer based on total land
void classifyFarmer(struct Farmer *f) {
    float total = f->ownLand + f->leasedLand;
    if (total >= 20)
        strcpy(f->category, "Rich");
    else if (total >= 10)
        strcpy(f->category, "Medium");
    else
        strcpy(f->category, "Poor");
}

// Function to add farmer records dynamically
void addFarmers(struct Farmer **f, int *n) {
    int extra, i;
    printf("\nEnter how many farmers you want to add: ");
    scanf("%d", &extra);

    if (*n == 0)
        *f = (struct Farmer *)malloc(extra * sizeof(struct Farmer));
    else
        *f = (struct Farmer *)realloc(*f, (*n + extra) * sizeof(struct Farmer));

    for (i = *n; i < *n + extra; i++) {
        printf("\nEnter details of Farmer %d:\n", i + 1);
        printf("Farmer ID: ");
        scanf("%d", &(*f)[i].id);
        printf("Farmer Name: ");
        scanf(" %[^\n]", (*f)[i].name);
        printf("Father Name: ");
        scanf(" %[^\n]", (*f)[i].fatherName);
        printf("Own Land (in acres): ");
        scanf("%f", &(*f)[i].ownLand);
        printf("Leased Land (in acres): ");
        scanf("%f", &(*f)[i].leasedLand);
        printf("Land with Borewell (in acres): ");
        scanf("%f", &(*f)[i].boreLand);
        printf("Land near Canal/Pond (in acres): ");
        scanf("%f", &(*f)[i].canalLand);
        printf("Dry Land (in acres): ");
        scanf("%f", &(*f)[i].dryLand);
        printf("Number of Crops Grown: ");
        scanf("%d", &(*f)[i].crops);
        printf("Annual Income (₹): ");
        scanf("%f", &(*f)[i].income);
        printf("Number of Pet Animals: ");
        scanf("%d", &(*f)[i].animals);
        printf("Soil Test Completed (Yes/No): ");
        scanf(" %[^\n]", (*f)[i].soilTest);

        classifyFarmer(&(*f)[i]);
    }
    *n += extra;
    printf("\n✅ Farmer details added successfully!\n");
}

// Display farmers in console
void displayFarmers(struct Farmer *f, int n) {
    if (n == 0) {
        printf("\nNo farmer records available.\n");
        return;
    }

    printf("\n-------------------------------------------------------------------------------------------------------------------------------\n");
    printf("| %-4s | %-15s | %-15s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | %-5s | %-10s | %-8s | %-8s | %-8s |\n",
           "ID", "Farmer Name", "Father Name", "Own", "Lease", "Total", "Bore", "Canal", "Dry", "Crops", "Income(₹)", "Animals", "Soil", "Category");
    printf("-------------------------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        float totalLand = f[i].ownLand + f[i].leasedLand;
        printf("| %-4d | %-15s | %-15s | %-6.2f | %-6.2f | %-6.2f | %-6.2f | %-6.2f | %-6.2f | %-5d | %-10.0f | %-8d | %-8s | %-8s |\n",
               f[i].id, f[i].name, f[i].fatherName,
               f[i].ownLand, f[i].leasedLand, totalLand,
               f[i].boreLand, f[i].canalLand, f[i].dryLand,
               f[i].crops, f[i].income, f[i].animals, f[i].soilTest, f[i].category);
    }
    printf("-------------------------------------------------------------------------------------------------------------------------------\n");
}

// Search farmer by ID
void searchFarmer(struct Farmer *f, int n) {
    int id, found = 0;
    printf("\nEnter Farmer ID to search: ");
    scanf("%d", &id);

    for (int i = 0; i < n; i++) {
        if (f[i].id == id) {
            printf("\nFarmer Found:\n");
            printf("ID: %d\nName: %s\nFather: %s\nCategory: %s\nSoil Test: %s\nTotal Land: %.2f acres\nIncome: ₹%.2f\n",
                   f[i].id, f[i].name, f[i].fatherName, f[i].category, f[i].soilTest,
                   f[i].ownLand + f[i].leasedLand, f[i].income);
            found = 1;
            break;
        }
    }
    if (!found)
        printf("\nFarmer with ID %d not found.\n", id);
}

// Delete farmer by ID
void deleteFarmer(struct Farmer *f, int *n) {
    int id, i, j, found = 0;
    printf("\nEnter Farmer ID to delete: ");
    scanf("%d", &id);

    for (i = 0; i < *n; i++) {
        if (f[i].id == id) {
            for (j = i; j < *n - 1; j++) {
                f[j] = f[j + 1];
            }
            (*n)--;
            found = 1;
            break;
        }
    }

    if (found)
        printf("\n✅ Farmer record deleted successfully.\n");
    else
        printf("\nFarmer with ID %d not found.\n", id);
}

// Generate report (write to file neatly aligned)
void generateReport(struct Farmer *f, int n, struct Village v) {
    FILE *fp;
    float totalOwn = 0, totalLeased = 0, totalIncome = 0, totalBore = 0, totalCanal = 0, totalDry = 0;
    int totalAnimals = 0, rich = 0, medium = 0, poor = 0;

    if (n == 0) {
        printf("\nNo data available to generate report.\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        totalOwn += f[i].ownLand;
        totalLeased += f[i].leasedLand;
        totalBore += f[i].boreLand;
        totalCanal += f[i].canalLand;
        totalDry += f[i].dryLand;
        totalIncome += f[i].income;
        totalAnimals += f[i].animals;

        if (strcmp(f[i].category, "Rich") == 0)
            rich++;
        else if (strcmp(f[i].category, "Medium") == 0)
            medium++;
        else
            poor++;
    }

    fp = fopen("village.txt", "w");
    if (fp == NULL) {
        printf("\nError opening file!\n");
        return;
    }

    fprintf(fp, "============================================\n");
    fprintf(fp, "      VILLAGE AGRICULTURE MANAGEMENT SYSTEM\n");
    fprintf(fp, "============================================\n");
    fprintf(fp, "Village: %s, Mandal: %s, District: %s, State: %s, PIN: %d\n\n",
            v.name, v.mandal, v.district, v.state, v.pin);
    fprintf(fp, "Total Farmers: %d\nRich: %d, Medium: %d, Poor: %d\n\n",
            n, rich, medium, poor);
    fprintf(fp, "Total Land: %.2f acres | Own: %.2f | Leased: %.2f\n", totalOwn + totalLeased, totalOwn, totalLeased);
    fprintf(fp, "Borewell: %.2f | Canal: %.2f | Dry: %.2f\n", totalBore, totalCanal, totalDry);
    fprintf(fp, "Total Income: ₹%.2f | Average Income: ₹%.2f | Total Animals: %d\n\n", totalIncome, totalIncome / n, totalAnimals);

    fprintf(fp, "-------------------------------------------------------------------------------------------------------------------------------\n");
    fprintf(fp, "| %-4s | %-15s | %-15s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | %-5s | %-10s | %-8s | %-8s | %-8s |\n",
            "ID", "Farmer Name", "Father Name", "Own", "Lease", "Total", "Bore", "Canal", "Dry", "Crops", "Income(₹)", "Animals", "Soil", "Category");
    fprintf(fp, "-------------------------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        float totalLand = f[i].ownLand + f[i].leasedLand;
        fprintf(fp, "| %-4d | %-15s | %-15s | %-6.2f | %-6.2f | %-6.2f | %-6.2f | %-6.2f | %-6.2f | %-5d | %-10.0f | %-8d | %-8s | %-8s |\n",
                f[i].id, f[i].name, f[i].fatherName,
                f[i].ownLand, f[i].leasedLand, totalLand,
                f[i].boreLand, f[i].canalLand, f[i].dryLand,
                f[i].crops, f[i].income, f[i].animals, f[i].soilTest, f[i].category);
    }
    fprintf(fp, "-------------------------------------------------------------------------------------------------------------------------------\n");

    fclose(fp);
    printf("\n✅ Report successfully written to 'village.txt' with perfect table alignment!\n");
}

// ---------------- MAIN FUNCTION ----------------
int main() {
    struct Village v;
    struct Farmer *f = NULL;
    int n = 0, choice;

    printf("\nEnter Village Details:\n");
    printf("Village Name: ");
    scanf(" %[^\n]", v.name);
    printf("Mandal: ");
    scanf(" %[^\n]", v.mandal);
    printf("District: ");
    scanf(" %[^\n]", v.district);
    printf("State: ");
    scanf(" %[^\n]", v.state);
    printf("PIN Code: ");
    scanf("%d", &v.pin);

    do {
        printf("\n============================================\n");
        printf("      VILLAGE AGRICULTURE MANAGEMENT MENU\n");
        printf("============================================\n");
        printf("1. Add Farmer Record\n");
        printf("2. Display All Farmers\n");
        printf("3. Search Farmer by ID\n");
        printf("4. Delete Farmer Record\n");
        printf("5. Generate Village Report\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addFarmers(&f, &n); break;
            case 2: displayFarmers(f, n); break;
            case 3: searchFarmer(f, n); break;
            case 4: deleteFarmer(f, &n); break;
            case 5: generateReport(f, n, v); break;
            case 6: printf("\nThank you, Spoorthi 🌾! Exiting program...\n"); break;
            default: printf("\nInvalid choice! Please try again.\n");
        }
    } while (choice != 6);

    free(f);
    return 0;
}
