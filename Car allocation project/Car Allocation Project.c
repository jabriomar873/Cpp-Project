///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////                                                                           /////////////
//////////////******  Bienvenue dans E-Cars - Application de location de voitures  ******//////////////
//////////////                                                                          ///////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

#include<stdio.h>
#include <stdlib.h>
#include<string.h>                             //### author :Omar jabri
#include<malloc.h>                            //###  created in 21/12/2023
#include<math.h>
#include<time.h>

typedef struct 

{
    int carID;
    char brand[50];
    char model[50];
    float rentalCostPerDay;
    int available; /* 1=disponible et  0=non disponible */
} Car;

//////// tableau des voitures  disponibles /////////
Car cars[40]= 
{
    {1, "Toyota", "Corolla", 50.0, 1},
    {2, "Honda", "Civic", 55.0, 1},
    {3, "Ford", "Mustang", 70.0, 0},
    {4, "Chevrolet", "Camaro", 65.0, 1},
    {5, "BMW", "X5", 80.0, 0},
    {6, "Audi", "A4", 60.0, 1},
    {7, "Mercedes-Benz", "E-Class", 85.0, 1},
    {8, "Volkswagen", "Golf", 45.0, 0},
    {9, "Tesla", "Model S", 100.0, 1},
    {10, "Nissan", "Altima", 55.0, 1},
    {11, "Subaru", "Outback", 65.0, 0},
    {12, "Hyundai", "Elantra", 50.0, 1},
    {13, "Kia", "Soul", 40.0, 1},
    {14, "Mazda", "CX-5", 75.0, 0},
    {15, "Volvo", "XC90", 90.0, 1},
    {16, "Lexus", "RX", 95.0, 1},
    {17, "Jeep", "Wrangler", 80.0, 0},
    {18, "Porsche", "911", 150.0, 1},
    {19, "Ferrari", "488 GTB", 250.0, 0},
    {20, "McLaren", "720S", 300.0, 1},
    {21, "Renault", "Clio", 48.0, 1},
    {22, "Peugeot", "208", 52.0, 0},
    {23, "Citroën", "C3", 45.0, 1},
    {24, "Fiat", "500", 42.0, 1},
    {25, "Alfa Romeo", "Giulia", 90.0, 0},
    {26, "Maserati", "Ghibli", 180.0, 1},
    {27, "Jaguar", "F-Type", 160.0, 1},
    {28, "Land Rover", "Discovery", 120.0, 0},
    {29, "Bugatti", "Chiron", 1000.0, 1},
    {30, "Rolls-Royce", "Phantom", 500.0, 1},
    {31, "Bentley", "Continental GT", 350.0, 0},
    {32, "Aston Martin", "DB11", 300.0, 1},
    {33, "Lamborghini", "Huracan", 400.0, 0},
    {34, "Lotus", "Evora", 250.0, 1},
    {35, "Subaru", "Impreza", 58.0, 1},
    {36, "Infiniti", "Q50", 70.0, 0},
    {37, "Genesis", "G70", 65.0, 1},
    {38, "Buick", "Enclave", 95.0, 1},
    {39, "Cadillac", "CT5", 80.0, 0},
    {40, "Lincoln", "Navigator", 150.0, 1}
};

///////// Structure pour une offre spéciale    /////////////////
typedef struct
{
    char offerCode[10];
    float discount;
} Offer;

Offer offers[10]= 
{
        {"OFFER1", 10.0},
        {"OFFER2", 15.0},
        {"OFFER3", 20.0},
        {"OFFER4", 12.0},
        {"OFFER5", 18.0},
        {"OFFER6", 8.0},
        {"OFFER7", 25.0},
        {"OFFER8", 5.0},
        {"OFFER9", 30.0},
        {"OFFER10", 7.0}
};
///////// Structure pour les services supplémentaires   //////////
typedef struct 
{
    char serviceName[50];
    float cost;
} Service;

Service services[10]= 
{
        {"Oil Change", 30.0},
        {"Tire Rotation", 20.0},
        {"Brake Inspection", 25.0},
        {"Car Wash", 15.0},
        {"Engine Tune-Up", 100.0},
        {"Wheel Alignment", 50.0},
        {"Air Conditioning Service", 80.0},
        {"Transmission Flush", 120.0},
        {"Spark Plug Replacement", 35.0},
        {"Battery Replacement", 90.0}
};
/////////////// Structure pour représenter une location //////////////////
typedef struct 
{
    int customerID;
    int carID;
    int daysRented;
    float totalCost;
} Rental;

Rental rentals[10]= 
{
        {101, 1, 5, 250.0},
        {102, 3, 3, 210.0},
        {103, 2, 7, 385.0},
        {104, 5, 4, 320.0},
        {105, 4, 6, 390.0},
        {106, 7, 2, 170.0},
        {107, 9, 10, 1000.0},
        {108, 6, 1, 60.0},
        {109, 8, 8, 400.0},
        {110, 10, 9, 630.0}
};

//////  Clear the screen ///////
void clearScreen() 
{
    system("clear || cls"); 
}

void afficherMenu() 
{
    printf("===========================================================\n");
    printf("Bienvenue dans E-Cars - Application de location de voitures\n");
    printf("===========================================================\n");
    printf("1. Afficher les voitures disponibles\n");
    printf("2. Louer une voiture\n");
    printf("3. Retourner une voiture\n");
    printf("4. Afficher les offres disponibles\n");
    printf("5. Appliquer une offre\n");
    printf("6. Afficher les services supplementaires\n");
    printf("7. Quitter\n");
    printf("Choisissez une option : ");
}
/////////// ce fontion permet d'afficher les voitures disponobles  ///////////
void afficherVoituresDisponibles() 
{
    printf("Voitures disponibles :\n");
    for (int i = 0; i <40; ++i) 
    {
        if (cars[i].available == 1) 
        {
            printf("Car ID: %d\n", cars[i].carID);
            printf("Brand: %s\n", cars[i].brand);
            printf("Model: %s\n", cars[i].model);
            printf("Rental Cost Per Day: %.2f\n", cars[i].rentalCostPerDay);
            printf("\n");
        }
    }
}

///////////// ce fontion permet de louer une voiture s'il est possible  //////////
void louerVoiture() {
    int customerID, carID, days;
    printf("Entrez votre ID de client : ");
    scanf("%d", &customerID);

    printf("Entrez l'ID de la voiture que vous souhaitez louer : ");
    scanf("%d", &carID);

    printf("Entrez le nombre de jours de location : ");
    scanf("%d", &days);
    for (int i = 0; i <40; ++i) 
    {
        if (cars[i].carID == carID && cars[i].available == 1) 
        {
            cars[i].available = 0;
            float cost = cars[i].rentalCostPerDay * days;
            printf("Voiture louee :\n");
            printf("Customer ID: %d\n", customerID);
            printf("Car ID: %d\n", cars[i].carID);
            printf("Brand: %s\n", cars[i].brand);
            printf("Model: %s\n", cars[i].model);
            printf("Days Rented: %d\n", days);
            printf("Total Cost: %.2f\n", cost);
            return;
        }
    }
    printf("La voiture demandee n'est pas disponible ou n'existe pas.\n");
}

//////////// ce fontion permet de modifier l'etat des voiture retourné //////////
void retournerVoiture() {
    int carID;
    printf("Entrez l'ID de la voiture à retourner : ");
    scanf("%d", &carID);
    for (int i = 0; i <40; ++i) 
    {
        if (cars[i].carID == carID) 
        {
            cars[i].available = 1;
            printf("Voiture retournee avec succes :\n");
            printf("Car ID: %d\n", cars[i].carID);
            printf("Brand: %s\n", cars[i].brand);
            printf("Model: %s\n", cars[i].model);
            printf("La voiture est maintenant disponible pour location.\n");
            return;
        }
    }
    printf("La voiture avec l'ID spécifie n'existe pas.\n");
}

//////////// ce fontion permet  d'afficher les offers disponibles //////////
void afficherOffresDisponibles() 
{
    printf("Offres disponibles :\n");
    for (int i = 0; i <10; ++i) 
    {
        printf("Offer Code: %s\n", offers[i].offerCode);
        printf("Discount: %.2f%%\n", offers[i].discount);
        printf("\n");
    }
}

void appliquerOffre() 
{
    int rentalChoice, offerChoice;

    printf("Available rentals:\n");
    for (int i = 0; i <10; ++i) 
    {
        printf("%d. Customer ID: %d, Car ID: %d, Days: %d, Cost: %.2f\n", i + 1,
               rentals[i].customerID, rentals[i].carID, rentals[i].daysRented, rentals[i].totalCost);
    }

    printf("Choose a rental number: ");
    scanf("%d", &rentalChoice);
    rentalChoice--;

    printf("\nAvailable offers:\n");
    for (int i = 0; i <10; ++i) 
    {
        printf("%d. Offer Code: %s, Discount: %.2f%%\n", i + 1, offers[i].offerCode, offers[i].discount);
    }

    printf("Choose an offer number: ");
    scanf("%d", &offerChoice);
    offerChoice--;
    float reduction = (offers[offerChoice].discount / 100) * rentals[rentalChoice].totalCost;
    rentals[rentalChoice].totalCost -= reduction;

    printf("L'offre %s a été appliquee avec succes.\n", offers[offerChoice].offerCode);
    printf("Le nouveau coût total est de : %.2f\n", rentals[rentalChoice].totalCost);
}

void afficherServicesSupplementaires()
                {
                    printf("Services supplémentaires disponibles :\n");
                    for (int i =0;i<10;i++) 
                    {
                        printf("%d. Service: %s, Cost: %.2f\n", i + 1, services[i].serviceName, services[i].cost);
                    }
                }


int main() 
{
    int choix;
    do {
        clearScreen();
        afficherMenu();
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                clearScreen();
                afficherVoituresDisponibles();
                printf("\nAppuyez sur n'importe quelle touche pour revenir au menu...");
                getchar(); getchar(); // Wait for user input before going back to the menu
                break;
            case 2:
                clearScreen();
                louerVoiture();
                printf("\nAppuyez sur n'importe quelle touche pour revenir au menu...");
                getchar(); getchar(); // Wait for user input before going back to the menu
                break;
            case 3:
                clearScreen();
                retournerVoiture();
                printf("\nAppuyez sur n'importe quelle touche pour revenir au menu...");
                getchar(); getchar(); // Wait for user input before going back to the menu
                break;
            case 4:
                clearScreen();
                afficherOffresDisponibles();
                printf("\nAppuyez sur n'importe quelle touche pour revenir au menu...");
                getchar(); getchar(); // Wait for user input before going back to the menu
                break;
            case 5:
                clearScreen();
                appliquerOffre();
                printf("\nAppuyez sur n'importe quelle touche pour revenir au menu...");
                getchar(); getchar(); // Wait for user input before going back to the menu
                break;
            case 6:
                clearScreen();
                afficherServicesSupplementaires();
                printf("\nAppuyez sur n'importe quelle touche pour revenir au menu...");
                getchar(); getchar(); // Wait for user input before going back to the menu
                break;
            case 7:
                clearScreen();
                printf("Merci d'avoir utilise E-Cars. Au revoir !\n");
                printf("\nAppuyez sur n'importe quelle touche pour revenir au menu...");
                getchar(); getchar(); // Wait for user input before going back to the menu
                break;
            default:
                clearScreen();
                printf("Option invalide. Veuillez choisir une option valide.\n");
                printf("\nAppuyez sur n'importe quelle touche pour revenir au menu...");
                getchar(); getchar(); // Wait for user input before going back to the menu
                break;
        }
    } while (choix != 7);

    return 0;
}

