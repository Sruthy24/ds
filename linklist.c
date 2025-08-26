#include <stdio.h>
#include <stdlib.h>
typedef struct PolyNode {
    int coeff;
    int expo;
    struct PolyNode* next;
} PolyNode;
PolyNode* createNode(int coeff, int expo) {
    PolyNode* newNode = (PolyNode*)malloc(sizeof(PolyNode));
    newNode->coeff = coeff;
    newNode->expo = expo;
    newNode->next = NULL;
    return newNode;
}
void insertTerm(PolyNode** poly, int coeff, int expo) {
    PolyNode* newNode = createNode(coeff, expo);
    if (*poly == NULL || (*poly)->expo < expo) {
        newNode->next = *poly;
        *poly = newNode;
    } else {
        PolyNode* temp = *poly;
        while (temp->next != NULL && temp->next->expo >= expo)
            temp = temp->next;
        if (temp->expo == expo) {
            temp->coeff += coeff;
            free(newNode);
        } else if (temp->next != NULL && temp->next->expo == expo) {
            temp->next->coeff += coeff;
            free(newNode);
        } else {
            newNode->next = temp->next;
            temp->next = newNode;
        }
    }
}
void displayPoly(PolyNode* poly) {
    if (poly == NULL) {
        printf("0\n");
        return;
    }

    while (poly != NULL) {
        printf("%dx^%d", poly->coeff, poly->expo);
        if (poly->next != NULL && poly->next->coeff >= 0)
            printf(" + ");
        poly = poly->next;
    }
    printf("\n");
}
PolyNode* addPolynomials(PolyNode* poly1, PolyNode* poly2) {
    PolyNode* result = NULL;

    while (poly1 != NULL && poly2 != NULL) {
        if (poly1->expo > poly2->expo) {
            insertTerm(&result, poly1->coeff, poly1->expo);
            poly1 = poly1->next;
        } else if (poly1->expo < poly2->expo) {
            insertTerm(&result, poly2->coeff, poly2->expo);
            poly2 = poly2->next;
        } else {
            int sum = poly1->coeff + poly2->coeff;
            if (sum != 0)
                insertTerm(&result, sum, poly1->expo);
            poly1 = poly1->next;
            poly2 = poly2->next;
        }
    }

    while (poly1 != NULL) {
        insertTerm(&result, poly1->coeff, poly1->expo);
        poly1 = poly1->next;
    }

    while (poly2 != NULL) {
        insertTerm(&result, poly2->coeff, poly2->expo);
        poly2 = poly2->next;
    }

    return result;
}
void inputPolynomial(PolyNode** poly, int polyNum) {
    int n, coeff, expo;
    printf("Enter number of terms for Polynomial %d: ", polyNum);
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter coefficient and exponent for term %d: ", i + 1);
        scanf("%d %d", &coeff, &expo);
        insertTerm(poly, coeff, expo);
    }
}
int main() {
    PolyNode* poly1 = NULL;
    PolyNode* poly2 = NULL;
    PolyNode* sum = NULL;
    inputPolynomial(&poly1, 1);
    inputPolynomial(&poly2, 2);
    printf("\nPolynomial 1: ");
    displayPoly(poly1);
    printf("Polynomial 2: ");
    displayPoly(poly2);
    sum = addPolynomials(poly1, poly2);
    printf("Sum: ");
    displayPoly(sum);

    return 0;
}
