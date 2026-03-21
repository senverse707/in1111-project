#ifndef CATEGORIES_H
#define CATEGORIES_H

#define MAX_CATEGORIES 20
#define MAX_LENGTH 50

extern char categories[MAX_CATEGORIES][MAX_LENGTH];
extern int categoryCount;

void addCategory(void);
void updateCategory(void);
void searchCategory(void);
void displayCategories(void);

#endif
