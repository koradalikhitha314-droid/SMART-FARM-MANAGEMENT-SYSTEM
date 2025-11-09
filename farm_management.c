
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CROPS 100
#define MAX_SOILS 5

// Structure for Crop
struct Crop {
    int id;
    char name[30];
    char soilType[20];
    char fertilizer[20];
    float cost;
    float sellingPrice;
};

// Structure for Soil and suitable crops
struct Soil {
    char type[20];
    char suitableCrops[5][30]; // max 5 crops per soil
    int cropCount;
};

// Global arrays
struct Crop crops[MAX_CROPS];
int cropCount = 0;

struct Soil soils[MAX_SOILS];
int soilCount = 0;

// Function prototypes
void initializeSoils();
void addCrop();
void displayCrops();
void searchCrop();
void updateCrop();
void deleteCrop();
void checkFertilizer();
void suggestCrops();
void calculateProfitLoss();
void saveData();
void loadData();

// Main function
int main() {
    int choice;

    initializeSoils(); // Setup soils and suitable crops
    loadData();        // Load existing crop data from file

    while(1) {
        printf("\n===== Smart Farm Management System =====\n");
        printf("1. Add New Crop\n");
        printf("2. Display All Crops\n");
        printf("3. Search Crop\n");
        printf("4. Update Crop\n");
        printf("5. Delete Crop\n");
        printf("6. Check Fertilizer Suitability\n");
        printf("7. Suggest Crops for Soil\n");
        printf("8. Calculate Profit/Loss\n");
        printf("9. Save and Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // consume newline

        switch(choice) {
            case 1: addCrop(); break;
            case 2: displayCrops(); break;
            case 3: searchCrop(); break;
            case 4: updateCrop(); break;
            case 5: deleteCrop(); break;
            case 6: checkFertilizer(); break;
            case 7: suggestCrops(); break;
            case 8: calculateProfitLoss(); break;
            case 9: saveData(); 
                    printf("Data saved. Exiting...\n"); 
                    exit(0);
            default: printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}

// Initialize soil types and suitable crops
void initializeSoils() {
    soilCount = 3;

    strcpy(soils[0].type, "Loamy");
    soils[0].cropCount = 3;
    strcpy(soils[0].suitableCrops[0], "Wheat");
    strcpy(soils[0].suitableCrops[1], "Rice");
    strcpy(soils[0].suitableCrops[2], "Tomato");

    strcpy(soils[1].type, "Sandy");
    soils[1].cropCount = 2;
    strcpy(soils[1].suitableCrops[0], "Carrot");
    strcpy(soils[1].suitableCrops[1], "Potato");

    strcpy(soils[2].type, "Clay");
    soils[2].cropCount = 2;
    strcpy(soils[2].suitableCrops[0], "Sugarcane");
    strcpy(soils[2].suitableCrops[1], "Cotton");
}

// Add new crop
void addCrop() {
    if(cropCount >= MAX_CROPS) {
        printf("Cannot add more crops.\n");
        return;
    }

    struct Crop newCrop;
    newCrop.id = cropCount + 1;

    printf("Enter Crop Name: ");
    fgets(newCrop.name, sizeof(newCrop.name), stdin);
    newCrop.name[strcspn(newCrop.name, "\n")] = 0;

    printf("Enter Soil Type (Loamy/Sandy/Clay): ");
    fgets(newCrop.soilType, sizeof(newCrop.soilType), stdin);
    newCrop.soilType[strcspn(newCrop.soilType, "\n")] = 0;

    printf("Enter Fertilizer Name: ");
    fgets(newCrop.fertilizer, sizeof(newCrop.fertilizer), stdin);
    newCrop.fertilizer[strcspn(newCrop.fertilizer, "\n")] = 0;

    printf("Enter Cost: ");
    scanf("%f", &newCrop.cost);
    printf("Enter Selling Price: ");
    scanf("%f", &newCrop.sellingPrice);
    getchar(); // consume newline

    crops[cropCount] = newCrop;
    cropCount++;

    printf("Crop added successfully!\n");
}

// Display all crops
void displayCrops() {
    if(cropCount == 0) {
        printf("No crops to display.\n");
        return;
    }

    printf("\nID\tName\tSoil Type\tFertilizer\tCost\tSelling Price\n");
    printf("---------------------------------------------------------------\n");
    for(int i=0; i<cropCount; i++) {
        printf("%d\t%s\t%s\t%s\t%.2f\t%.2f\n",
               crops[i].id,
               crops[i].name,
               crops[i].soilType,
               crops[i].fertilizer,
               crops[i].cost,
               crops[i].sellingPrice);
    }
}

// Search crop by name
void searchCrop() {
    char cropName[30];
    printf("Enter Crop Name to search: ");
    fgets(cropName, sizeof(cropName), stdin);
    cropName[strcspn(cropName, "\n")] = 0;

    for(int i=0; i<cropCount; i++) {
        if(strcmp(crops[i].name, cropName) == 0) {
            printf("Found Crop: ID=%d, Name=%s, Soil=%s, Fertilizer=%s, Cost=%.2f, Selling Price=%.2f\n",
                   crops[i].id, crops[i].name, crops[i].soilType,
                   crops[i].fertilizer, crops[i].cost, crops[i].sellingPrice);
            return;
        }
    }
    printf("Crop not found.\n");
}

// Update crop
void updateCrop() {
    char cropName[30];
    printf("Enter Crop Name to update: ");
    fgets(cropName, sizeof(cropName), stdin);
    cropName[strcspn(cropName, "\n")] = 0;

    for(int i=0; i<cropCount; i++) {
        if(strcmp(crops[i].name, cropName) == 0) {
            printf("Updating Crop %s:\n", crops[i].name);

            printf("Enter New Crop Name: ");
            fgets(crops[i].name, sizeof(crops[i].name), stdin);
            crops[i].name[strcspn(crops[i].name, "\n")] = 0;

            printf("Enter New Soil Type: ");
            fgets(crops[i].soilType, sizeof(crops[i].soilType), stdin);
            crops[i].soilType[strcspn(crops[i].soilType, "\n")] = 0;

            printf("Enter New Fertilizer Name: ");
            fgets(crops[i].fertilizer, sizeof(crops[i].fertilizer), stdin);
            crops[i].fertilizer[strcspn(crops[i].fertilizer, "\n")] = 0;

            printf("Enter New Cost: ");
            scanf("%f", &crops[i].cost);
            printf("Enter New Selling Price: ");
            scanf("%f", &crops[i].sellingPrice);
            getchar(); // consume newline

            printf("Crop updated successfully!\n");
            return;
        }
    }
    printf("Crop not found.\n");
}

// Delete crop
void deleteCrop() {
    char cropName[30];
    printf("Enter Crop Name to delete: ");
    fgets(cropName, sizeof(cropName), stdin);
    cropName[strcspn(cropName, "\n")] = 0;

    for(int i=0; i<cropCount; i++) {
        if(strcmp(crops[i].name, cropName) == 0) {
            for(int j=i; j<cropCount-1; j++) {
                crops[j] = crops[j+1]; // shift array left
            }
            cropCount--;
            printf("Crop deleted successfully!\n");
            return;
        }
    }
    printf("Crop not found.\n");
}

// Check fertilizer suitability
void checkFertilizer() {
    char cropName[30];
    printf("Enter Crop Name to check fertilizer: ");
    fgets(cropName, sizeof(cropName), stdin);
    cropName[strcspn(cropName, "\n")] = 0;

    for(int i=0; i<cropCount; i++) {
        if(strcmp(crops[i].name, cropName) == 0) {
            // Example check: Recommend "RecommendedFertilizer"
            if(strcmp(crops[i].fertilizer, "RecommendedFertilizer") != 0) {
                printf("Warning: Fertilizer may not be suitable for %s!\n", crops[i].name);
            } else {
                printf("Fertilizer is suitable.\n");
            }
            return;
        }
    }
    printf("Crop not found.\n");
}

// Suggest crops based on soil
void suggestCrops() {
    char soilType[20];
    printf("Enter Soil Type to get crop suggestions: ");
    fgets(soilType, sizeof(soilType), stdin);
    soilType[strcspn(soilType, "\n")] = 0;

    for(int i=0; i<soilCount; i++) {
        if(strcmp(soils[i].type, soilType) == 0) {
            printf("Suitable crops for %s soil:\n", soilType);
            for(int j=0; j<soils[i].cropCount; j++) {
                printf("- %s\n", soils[i].suitableCrops[j]);
            }
            return;
        }
    }
    printf("Soil type not recognized.\n");
}

// Calculate profit or loss
void calculateProfitLoss() {
    char cropName[30];
    printf("Enter Crop Name to calculate profit/loss: ");
    fgets(cropName, sizeof(cropName), stdin);
    cropName[strcspn(cropName, "\n")] = 0;

    for(int i=0; i<cropCount; i++) {
        if(strcmp(crops[i].name, cropName) == 0) {
            float profit = crops[i].sellingPrice - crops[i].cost;
            if(profit > 0)
                printf("Profit for %s: %.2f\n", crops[i].name, profit);
            else
                printf("Loss for %s: %.2f\n", crops[i].name, -profit);
            return;
        }
    }
    printf("Crop not found.\n");
}

// Save crop data to file
void saveData() {
    FILE *fp = fopen("crops.txt", "w");
    if(fp == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    for(int i=0; i<cropCount; i++) {
        fprintf(fp, "%d|%s|%s|%s|%.2f|%.2f\n",
                crops[i].id,
                crops[i].name,
                crops[i].soilType,
                crops[i].fertilizer,
                crops[i].cost,
                crops[i].sellingPrice);
    }

    fclose(fp);
}

// Load crop data from file
void loadData() {
    FILE *fp = fopen("crops.txt", "r");
    if(fp == NULL) return; // no file exists yet

    while(fscanf(fp, "%d|%[^|]|%[^|]|%[^|]|%f|%f\n",
                 &crops[cropCount].id,
                 crops[cropCount].name,
                 crops[cropCount].soilType,
                 crops[cropCount].fertilizer,
                 &crops[cropCount].cost,
                 &crops[cropCount].sellingPrice) != EOF) {
        cropCount++;
    }

    fclose(fp);
}
