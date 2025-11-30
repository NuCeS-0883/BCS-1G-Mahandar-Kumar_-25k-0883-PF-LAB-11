#include <stdio.h>
#include <string.h>

struct Date {
    int day, month, year;
};
struct Transaction {
    char type[20];   
    float amount;
    struct Date tDate;
};
struct BankAccount {
    char name[50];
    int accountNumber;
    char accountType[20];
    float balance;
    
    struct Date creationDate;
    struct Date lastTransactionDate;

    struct Transaction history[100];
    int transCount;
};
struct Date inputDate() {
    struct Date d;
    printf("Enter date (DD MM YYYY): ");
    scanf("%d %d %d", &d.day, &d.month, &d.year);
    return d;
}
float getMinimumBalance(char type[]) {
    if (strcmp(type, "Savings") == 0) return 1000;
    if (strcmp(type, "Current") == 0) return 5000;
    if (strcmp(type, "Fixed") == 0) return 10000;
    return 0;
}
float getInterestRate(char type[]) {
    if (strcmp(type, "Savings") == 0) return 4;
    if (strcmp(type, "Fixed") == 0) return 7;
    return 0; 
}
void addTransaction(struct BankAccount *acc, char type[], float amount) {
    struct Transaction *t = &acc->history[acc->transCount++];
    strcpy(t->type, type);
    t->amount = amount;
    t->tDate = inputDate();
    acc->lastTransactionDate = t->tDate;
}
void deposit(struct BankAccount *acc) {
    float amount;
    printf("Enter deposit amount: ");
    scanf("%f", &amount);
    acc->balance += amount;
    addTransaction(acc, "Deposit", amount);
    printf("Amount Deposited Successfully!\n");
}

void withdraw(struct BankAccount *acc) {
    float amount;
    printf("Enter withdrawal amount: ");
    scanf("%f", &amount);
    float minBal = getMinimumBalance(acc->accountType);
    if (acc->balance - amount < minBal) {
        printf("ERROR! Cannot withdraw. Minimum balance %.2f required.\n", minBal);
        return;
    }
    acc->balance -= amount;
    addTransaction(acc, "Withdrawal", amount);
    printf("Amount Withdrawn Successfully!\n");
}
void displayAccount(struct BankAccount acc) {
    printf("\n----- ACCOUNT DETAILS -----\n");
    printf("Name: %s\n", acc.name);
    printf("Account Number: %d\n", acc.accountNumber);
    printf("Type: %s\n", acc.accountType);
    printf("Balance: %.2f\n", acc.balance);
    printf("Account Creation Date: %02d-%02d-%04d\n",
           acc.creationDate.day, acc.creationDate.month, acc.creationDate.year);
    printf("Last Transaction Date: %02d-%02d-%04d\n",
           acc.lastTransactionDate.day, acc.lastTransactionDate.month, acc.lastTransactionDate.year);
    printf("\n----- TRANSACTION HISTORY -----\n");
    for (int i = 0; i < acc.transCount; i++) {
        printf("%s of %.2f on %02d-%02d-%04d\n",
               acc.history[i].type,
               acc.history[i].amount,
               acc.history[i].tDate.day,
               acc.history[i].tDate.month,
               acc.history[i].tDate.year);
    }
}
int main() {
    struct BankAccount accounts[100];
    int count = 0;
    int choice;
    while (1) {
        printf("\n==== BANK ACCOUNT MANAGEMENT ====\n");
        printf("1. Create Account\n");
        printf("2. Deposit\n");
        printf("3. Withdraw\n");
        printf("4. Display Account\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        if (choice == 5) break;
        switch (choice) {
            case 1: {
                printf("\n--- Create New Account ---\n");
                printf("Enter name: ");
                scanf(" %[^\n]", accounts[count].name);
                printf("Enter account number: ");
                scanf("%d", &accounts[count].accountNumber);
                printf("Enter account type (Savings / Current / Fixed): ");
                scanf("%s", accounts[count].accountType);
                float minBal = getMinimumBalance(accounts[count].accountType);
                printf("Minimum initial deposit required = %.2f\n", minBal);
                do {
                    printf("Enter initial deposit: ");
                    scanf("%f", &accounts[count].balance);
                    if (accounts[count].balance < minBal)
                        printf("Amount less than required minimum. Try again.\n");
                } while (accounts[count].balance < minBal);
                accounts[count].creationDate = inputDate();
                accounts[count].lastTransactionDate = accounts[count].creationDate;
                accounts[count].transCount = 0;
                printf("Account Created Successfully!\n");
                count++;
                break;
            }
            case 2: {
                int accNo;
                printf("Enter account number: ");
                scanf("%d", &accNo);
                int found = 0;
                for (int i = 0; i < count; i++) {
                    if (accounts[i].accountNumber == accNo) {
                        deposit(&accounts[i]);
                        found = 1;
                        break;
                    }
                }
                if (!found) printf("Account not found!\n");
                break;
            }
            case 3: {
                int accNo;
                printf("Enter account number: ");
                scanf("%d", &accNo);
                int found = 0;
                for (int i = 0; i < count; i++) {
                    if (accounts[i].accountNumber == accNo) {
                        withdraw(&accounts[i]);
                        found = 1;
                        break;
                    }
                }
                if (!found) printf("Account not found!\n");
                break;
            }
            case 4: {
                int accNo;
                printf("Enter account number: ");
                scanf("%d", &accNo);
                int found = 0;
                for (int i = 0; i < count; i++) {
                    if (accounts[i].accountNumber == accNo) {
                        displayAccount(accounts[i]);
                        found = 1;
                        break;
                    }
                }
                if (!found) printf("Account not found!\n");
                break;
            }
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}

