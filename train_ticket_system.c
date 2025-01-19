#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to hold train details
struct Train {
    int trainNumber;
    char origin[50];
    char destination[50];
    char departureTime[10];
    char arrivalTime[10];
    float fare;
    struct Train *next;
};

// Structure to hold booking details
struct Booking {
    int ticketNumber;
    int trainNumber;
    char passengerName[50];
    struct Booking *next;
};

// Function to display available trains
void displayTrains(struct Train *head) {
    struct Train *current = head;
    printf("\nAvailable Trains:\n");
    printf("-------------------------------------------\n");
    printf("Train No.\tOrigin\t\tDestination\tDeparture\tArrival\tFare\n");
    printf("------------------------------------------------------------\n");
    while (current != NULL) {
        printf("%d\t\t%s\t\t%s\t\t%s\t%s\t%.2f\n", current->trainNumber, current->origin,
            current->destination, current->departureTime, current->arrivalTime, current->fare);
        current = current->next;
    }
    printf("------------------------------------------------------------\n");
}

// Function to book a ticket
void bookTicket(struct Booking **head, int ticketNumber, int trainNumber, const char *passengerName, struct Train *trainList) {
    struct Booking *newBooking = (struct Booking *)malloc(sizeof(struct Booking));
    if (newBooking == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newBooking->ticketNumber = ticketNumber;
    newBooking->trainNumber = trainNumber;
    strcpy(newBooking->passengerName, passengerName);
    newBooking->next = *head;
    *head = newBooking;

    // Find the train details for the booked ticket
    struct Train *current = trainList;
    while (current != NULL) {
        if (current->trainNumber == trainNumber) {
            printf("\nTicket booked successfully!\n");
            printf("Ticket Number: %d\n", ticketNumber);
            printf("Train No.: %d\n", current->trainNumber);
            printf("Origin: %s\n", current->origin);
            printf("Destination: %s\n", current->destination);
            printf("Departure Time: %s\n", current->departureTime);
            printf("Arrival Time: %s\n", current->arrivalTime);
            printf("Fare: %.2f\n", current->fare);
            printf("Passenger Name: %s\n", passengerName);
            return;
        }
        current = current->next;
    }
    printf("\nError: Train details not found!\n");
}

// Function to cancel a ticket based on ticket number
void cancelTicket(struct Booking **head, int ticketNumber) {
    struct Booking *current = *head;
    struct Booking *prev = NULL;
    while (current != NULL && current->ticketNumber != ticketNumber) {
        prev = current;
        current = current->next;
    }
    if (current == NULL) {
        printf("\nNo ticket found with ticket number %d\n", ticketNumber);
        return;
    }
    if (prev == NULL) {
        *head = current->next;
    } else {
        prev->next = current->next;
    }
    free(current);
    printf("\nTicket canceled successfully!\n");
}

// Function to create a new train node
struct Train *createTrain(int trainNumber, char *origin, char *destination, char *departureTime, char *arrivalTime, float fare) {
    struct Train *newTrain = (struct Train *)malloc(sizeof(struct Train));
    if (newTrain == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newTrain->trainNumber = trainNumber;
    strcpy(newTrain->origin, origin);
    strcpy(newTrain->destination, destination);
    strcpy(newTrain->departureTime, departureTime);
    strcpy(newTrain->arrivalTime, arrivalTime);
    newTrain->fare = fare;
    newTrain->next = NULL;
    return newTrain;
}

// Function to free memory allocated for linked list of trains
void freeTrainList(struct Train *head) {
    struct Train *current = head;
    while (current != NULL) {
        struct Train *temp = current;
        current = current->next;
        free(temp);
    }
}

// Function to free memory allocated for linked list of bookings
void freeBookingList(struct Booking *head) {
    struct Booking *current = head;
    while (current != NULL) {
        struct Booking *temp = current;
        current = current->next;
        free(temp);
    }
}

int main() {
    // Sample train data
    struct Train *trainList = NULL;
    struct Train *train1 = createTrain(101, "City A", "City B", "08:00", "12:00", 500.0);
    struct Train *train2 = createTrain(102, "City B", "City C", "10:00", "14:00", 600.0);
    struct Train *train3 = createTrain(103, "City A", "City C", "09:00", "13:00", 550.0);

    train3->next = trainList;
    trainList = train3;
    train2->next = trainList;
    trainList = train2;
    train1->next = trainList;
    trainList = train1;

    int option;
    struct Booking *bookingList = NULL;
    int ticketCounter = 1;

    do {
        printf("\n======= Train Ticket Reservation System =======\n");
        printf("1. Display Available Trains\n");
        printf("2. Book a Ticket\n");
        printf("3. Cancel a Ticket\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                displayTrains(trainList);
                break;
            case 2: {
                int trainNumber;
                char passengerName[50];
                printf("\nEnter the train number to book ticket: ");
                scanf("%d", &trainNumber);
                printf("Enter passenger name: ");
                scanf("%s", passengerName);
                bookTicket(&bookingList, ticketCounter++, trainNumber, passengerName, trainList);
                break;
            }
            case 3: {
                int ticketNumber;
                printf("\nEnter the ticket number to cancel: ");
                scanf("%d", &ticketNumber);
                cancelTicket(&bookingList, ticketNumber);
                break;
            }
            case 4:
                printf("Exiting program. Goodbye!\n");
                break;
            default:
                printf("Invalid option! Please try again.\n");
        }
    } while (option != 4);

    // Free allocated memory for train list
    freeTrainList(trainList);
    // Free allocated memory for booking list
    freeBookingList(bookingList);

    return 0;
}
