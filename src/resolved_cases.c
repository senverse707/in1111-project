#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "resolved_cases.h"

void initialize_list(struct ResolvedList *list){
    list->head = NULL;
    list->tail = NULL;
}

struct ResolvedNode *create_node(int CaseID, int ItemID, char ItemName[], char OwnerName[], char ReturnedDate[], char VerifiedBy[], char Remarks[]){
    struct ResolvedNode *NewNode = (struct ResolvedNode *)malloc(sizeof(struct ResolvedNode));
    if (NewNode == NULL){
        printf("Memory Allocation failed!\n");
        return NULL;
    }

    NewNode->CaseID = CaseID;
    NewNode->ItemID = ItemID;
    strcpy(NewNode->ItemName, ItemName);
    strcpy(NewNode->OwnerName, OwnerName);
    strcpy(NewNode->ReturnedDate, ReturnedDate);
    strcpy(NewNode->VerifiedBy, VerifiedBy);
    strcpy(NewNode->Remarks, Remarks);
    NewNode->next = NULL;
    NewNode->prev = NULL;

    return NewNode;

}

/*Traverse Forward*/
void traverseforward(struct ResolvedList *list){
    if (list->head == NULL){
        printf("\nCase list is empty!\n");
        return;
    }
    struct ResolvedNode *temp = list->head;
    printf("\n---All Cases (Forward)---\n\n");
    do {
        printf("CaseID: %d\nItem: %s\nOwner: %s\n\n",temp->CaseID,temp->ItemName,temp->OwnerName);
        temp = temp->next;
    } while(temp != list->head);
}

/*Traverse Backward*/
void traversebackward(struct ResolvedList *list){
    if (list->tail == NULL){
        printf("\nCase list is empty!\n");
        return;
    }
    struct ResolvedNode *temp = list->tail;
    printf("\n---All Cases (Backward)---\n\n");
    do {
        printf("CaseID: %d\nItem: %s\nOwner: %s\n\n",temp->CaseID,temp->ItemName,temp->OwnerName);
        temp = temp->prev;
    } while(temp != list->tail);
}

/*Check duplicates*/
bool isduplicate(struct ResolvedList *list, int CaseID, int ItemID){
    if (list->head == NULL){
        return false;
    }
    struct ResolvedNode *temp = list->head;
    do {
        if (temp->CaseID == CaseID || temp->ItemID == ItemID){
            return true;
        }
        temp = temp->next;
    } while (temp != list->head);
    return false;
}

/*Adding a new case*/
void addcase(struct ResolvedList *list, int CaseID, int ItemID, char ItemName[], char OwnerName[], char ReturnedDate[], char VerifiedBy[], char Remarks[]){

    struct ResolvedNode *NewNode = create_node(CaseID,ItemID,ItemName,OwnerName,ReturnedDate,VerifiedBy,Remarks);

    if (NewNode == NULL){
        return;
    }

    if (list->head == NULL){
        list->head = NewNode;
        list->tail = NewNode;
        NewNode->next = NewNode;
        NewNode->prev = NewNode;
    }
    else{
        NewNode->prev = list->tail;
        NewNode->next = list->head;

        list->tail->next = NewNode;
        list->head->prev = NewNode;

        list->tail = NewNode;
    }

    printf("\nCase inserted successfully!\n");
};

/*Display current case*/
void displaycase(struct ResolvedNode *temp){
    if (temp==NULL){
        printf("\nNo case to display!\n");
        return;
    }
    printf("\n---Case Details---\n\n");
    printf("Case ID: %d\n", temp->CaseID);
    printf("Item ID: %d\n", temp->ItemID);
    printf("Item: %s\n", temp->ItemName);
    printf("Owner: %s\n", temp->OwnerName);
    printf("Returned Date: %s\n", temp->ReturnedDate);
    printf("Verified By: %s\n", temp->VerifiedBy);
    printf("Remarks: %s\n", temp->Remarks);
}

/*Search case*/
struct ResolvedNode *search(struct ResolvedList *list, int CaseID){
    if (list->head == NULL){
        printf("\nCase list is empty!\n");
        return NULL;
    }

    struct ResolvedNode *temp = list->head;
    do{
        if (temp->CaseID == CaseID){
            printf("\nCase found!\n");
            return temp;
        }
        temp = temp->next;
    }while(temp != list->head);

    printf("\nCase not found!\n");
    return NULL;
}

/*Updating cases*/
void update(struct ResolvedList *list, int CaseID, char NewRemarks[]){
    struct ResolvedNode *temp = search(list, CaseID);
    if (temp != NULL){
        strcpy(temp->Remarks, NewRemarks);
        printf("\nRemarks updated successfully!\n");
    }
}

/*Deleting case*/
void deletecase(struct ResolvedList *list, int CaseID){
    if (list->head == NULL){
        printf("\nList is empty!\n");
        return;
    }
    struct ResolvedNode *temp = list->head;
    do{
        if(temp->CaseID == CaseID){
            if(list->head == list->tail){
                list->head = NULL;
                list->tail = NULL;
            }
            else if(temp ==list->head){
                list->head = temp->next;
                list->tail->next = list->head;
                list->head->prev = list->tail;
            }
            else if(temp == list->tail){
                list->tail = temp->prev;
                list->tail->next = list->head;
                list->head->prev = list->tail;
            }
            else{
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
            }
            free(temp);
            printf("\nCase successfully deleted!\n");
            return;
        }
        temp = temp->next;
    }while(temp != list->head);
    printf("\nCase not found!\n");
}

/*Main control*/
int main(){
    struct ResolvedList list;
    initialize_list(&list);

    int choice, CaseID, ItemID;
    char ItemName[30], OwnerName[40], ReturnedDate[15], VerifiedBy[40], Remarks[50];

    struct ResolvedNode *temp = NULL;

    do {
        printf("\n===== RESLOVED CASE MANAGEMENT =====\n\n");
        printf("1.Display All Cases (Forward)\n");
        printf("2.Display All Cases (Backward)\n");
        printf("3.Add Case\n");
        printf("4.Next Case\n");
        printf("5.Previous Case\n");
        printf("6.Display Current Case\n");
        printf("7.Search Case\n");
        printf("8.Update Remarks\n");
        printf("9.Delete case\n");
        printf("0.Exit\n");
        printf("Please enter your choice number: ");
        scanf("%d", &choice);

        switch(choice){
            case 1: traverseforward(&list);
                    break;

            case 2: traversebackward(&list);
                    break;

            case 3: bool duplicate;
                    do{
                        printf("Enter case ID: ");
                        scanf("%d", &CaseID);
                        getchar();
                        printf("Enter item ID: ");
                        scanf("%d", &ItemID);
                        getchar();
                        duplicate = isduplicate(&list, CaseID, ItemID);
                        if (duplicate){
                            printf("\nCaseID or ItemID already exists! Try a different one\n");
                            }
                        }while(duplicate);
                        printf("Enter item name: ");
                        fgets(ItemName,sizeof(ItemName),stdin);
                        ItemName[strcspn(ItemName, "\n")] = '\0';
                        printf("Enter owner name: ");
                        fgets(OwnerName,sizeof(OwnerName),stdin);
                        OwnerName[strcspn(OwnerName, "\n")] = '\0';
                        printf("Enter returned date: ");
                        fgets(ReturnedDate,sizeof(ReturnedDate),stdin);
                        ReturnedDate[strcspn(ReturnedDate, "\n")] = '\0';
                        printf("Enter verfied by: ");
                        fgets(VerifiedBy,sizeof(VerifiedBy),stdin);
                        VerifiedBy[strcspn(VerifiedBy, "\n")] = '\0';
                        printf("Enter remarks: ");
                        fgets(Remarks,sizeof(Remarks),stdin);
                        Remarks[strcspn(Remarks, "\n")] = '\0';

                        addcase(&list, CaseID, ItemID, ItemName, OwnerName, ReturnedDate, VerifiedBy, Remarks);
                        break;

            case 4: if (temp != NULL){
                            temp = temp->next;
                            printf("\nMoved to next case\n");
                        }
                    else {
                        printf("\nEnter CaseID to start navigation: ");
                        scanf("%d", &CaseID);
                        getchar();
                        temp = search(&list, CaseID);
                    }
                        break;

            case 5: if (temp != NULL){
                            temp = temp->prev;
                            printf("\nMoved to previous case\n");
                        }
                    else {
                        printf("\nEnter CaseID to start navigation: ");
                        scanf("%d", &CaseID);
                        getchar();
                        temp = search(&list, CaseID);
                    }
                    break;

            case 6: displaycase(temp);
                    break;

            case 7: printf("Enter CaseID to search: ");
                    scanf("%d", &CaseID);
                    getchar();
                    temp = search(&list, CaseID);
                    break;

            case 8: printf("Enter CaseID to update: ");
                    scanf("%d", &CaseID);
                    getchar();
                    printf("Enter new remarks: ");
                    fgets(Remarks,sizeof(Remarks),stdin);
                    update(&list, CaseID, Remarks);
                    break;

            case 9: printf("Enter CaseID to delete: ");
                    scanf("%d", &CaseID);
                    if (temp != NULL && temp->CaseID == CaseID){
                        temp = temp->next;
                    }
                    deletecase(&list, CaseID);
                    break;

            case 0: printf("\nExiting...\n");
            return 0;

            default: printf("\nInvalid choice! Please try again\n");
        }
    } while(choice != 0);
}
