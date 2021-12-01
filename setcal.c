#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdbool.h>
#include <stdlib.h>

#define N 3

/**
 * Definition for singly-linked list.
 */
typedef struct {
    char **words;
    int count;
} univerzum;

/**
 * Definition for singly-linked list.
 */
typedef struct set {
    int size;
    int capacity;
    char **elements;
    int row;
} set;

/**
 * Definition for items in set array.
 */
typedef struct item t_item;
struct item {
    set s;
    t_item *next;
};

/**
* Definition for set array.
*/
typedef struct {
    t_item *head;
    t_item *tail;
} t_list;

/**
 * Operation data structure
 */
typedef struct {
    char *name;
    void *pointer;
} operation;

/**
 * Definition for relations
 */
typedef struct {
    char ***pairs;
    int count_pairs;
} relations;

/**
 * Enumerates command types
 */
typedef enum {
    U = 'U',
    S = 'S',
    R = 'R',
    C = 'C',
} commands;

/**
 * Command data structure
 */
typedef struct {
    commands type;
    char **args;
} command_t;

typedef struct {
    int size;
    int capacity;
    char **elements;
} vector_t;

/**
 * Prototypes of functions
 */
void rel_table(int **table, relations *rel_arr, univerzum *univerzum);

int find_operation(operation *operations, int size, char *name);

set *set_init(int capacity);

void set_add(set *s, char *e);

void set_add_row(set *s, int row);

void set_print(set *s);

void list_init(t_list *list);

void insert_first(t_list *list, set s);

void write_list(const t_list *list);

bool set_is_empty(set *s);

set *set_union(set *s1, set *s2);

set *set_intersection(set *s1, set *s2);

set *set_difference(set *s1, set *s2);

bool set_is_subset(set *s1, set *s2);

bool set_is_equal(set *s1, set *s2);

bool reflexive(relations *rel_arr, univerzum *univerzum);

bool symmetric(relations *rel_arr, univerzum *univerzum);

bool antisymmetric(relations *rel_arr, univerzum *univerzum);

bool transitive(relations *rel_arr, univerzum *univerzum);

bool function(relations *rel_arr, univerzum *univerzum);


/**
 * Main function.
 * @param argc The number of arguments.
 * @param argv The arguments.
 * @return 0 if the program ran successfully, 1 otherwise.
 */
int main(int argc, char *argv[]) {
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        fprintf(stderr, "Error during opening the file!\n");
        return 1;
    }
    char row[101];
    char *istr;
    univerzum *univerzum;
    univerzum = set_init(1);
    set **sets = NULL;
    int set_amount = 0;
    while (fgets(row, 101, file)) {
        istr = strtok(row, " \n");
        if (strcmp(istr, "U") == 0) {
            istr = strtok(NULL, " \n");
            while (istr != NULL) {
                set_add(univerzum, istr);
                istr = strtok(NULL, " \n");
            }
        } else if (strcmp(istr, "S") == 0) {
            set *s;
            s = set_init(1);
            istr = strtok(NULL, " \n");
            while (istr != NULL) {
                set_add(s, istr);
                istr = strtok(NULL, " \n");
            }
        }
    }

    for (int i = 0; i < set_amount; i++) {
        for (int j = 0; j < sets[i]->size; j++) {
            printf("%s ", sets[i]->elements[j]);
        }
        printf("\n");
    }

    fclose(file);
    return 0;
}


/**
 * function for file opening
 */


/**
 * table of 0 and 1 for relations
 */
void rel_table(int **table, relations *rel_arr, univerzum *univerzum) {
    for (int i = 0; i < univerzum->count; i++) {
        for (int j = 0; j < univerzum->count; j++) {
            table[i][j] = 0;
        }
    }
    for (int i = 0; i < rel_arr->count_pairs; i++) {
        for (int j = 0; j < univerzum->count; j++) {
            if (strcmp(rel_arr->pairs[i][0], univerzum->words[j]) == 0) {
                for (int k = 0; k < univerzum->count; k++) {
                    if (strcmp(rel_arr->pairs[i][1], univerzum->words[k]) ==
                        0) {
                        table[j][k] = 1;
                    }
                }
            }
        }
    }
    for (int i = 0; i < univerzum->count; i++) {
        for (int j = 0; j < univerzum->count; j++) {
            printf("%d ", table[i][j]);
        }
        printf("\n");
    }
}

/**
 * Finds operation by name
 * @param operations Operations array
 * @param size Operations array size
 * @param name Operation name
 * @return Operation index or -1 if not found
 */
int find_operation(operation *operations, int size, char *name) {
    for (int i = 0; i < size; i++) {
        if (strcmp(operations[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

/**
 * Creates a new set.
 * @param capacity The initial capacity of the set.
 * @return The new set.
 */
set *set_init(int capacity) {
    set *s = malloc(sizeof(set));
    s->size = 0;
    s->capacity = capacity;
    s->elements = malloc(sizeof(char *) * capacity);
    return s;
}

/**
 * Adds an element to the set.
 * @param s The set.
 * @param e The element to add.
 */
void set_add(set *s, char *e) {
    if (s->size == s->capacity) {
        s->capacity *= 2;
        s->elements = realloc(s->elements, sizeof(char *) * s->capacity);
    }
    s->elements[s->size] = e;
    s->size++;
}

/**
 * Adds a row number to the set.
 * @param s The set.
 * @param e The element to add.
 */
void set_add_row(set *s, int row) {
    s->row = row;
}

/**
 * Prints the set.
 * @param s The set.
 */
void set_print(set *s) {
    for (int i = 0; i < s->size; i++) {
        printf("%s\n", s->elements[i]);
    }
}

/**
 * Creates list of sets
 * @param list The list of sets.
 */
void list_init(t_list *list) {
    list->head = NULL;
    list->tail = NULL;
}

/**
 * Adds set to a first position of list of sets
 * @param list The list of sets.
 * @param s The set to add.
 */
void insert_first(t_list *list, set s) {
    t_item *new_item;
    if ((new_item = malloc(sizeof(t_item))) == NULL) {
        fprintf(stderr, "Error during malloc!\n");
        return;
    }
    new_item->s = s;
    new_item->next = list->head;
    list->head = new_item;
}

/**
 * Writes elements of list
 * @param list The list of sets.
 * @param s The set to add.
 */
void write_list(const t_list *list) {
    for (t_item *tmp = list->head; tmp != NULL; tmp = tmp->next) {
        printf("%d %d", tmp->s.size, tmp->s.capacity);
    }
}

/**
 * Checks if the set is empty.
 * @param s The set.
 * @return true if the set is empty, false otherwise.
 */
bool set_is_empty(set *s) {
    if (s->size == 0) {
        return true;
    }
    return false;
}

/**
 * Union of two sets.
 * @param s1 The first set.
 * @param s2 The second set.
 * @return The union of the two sets.
 */
set *set_union(set *s1, set *s2) {
    set *s = set_init(s1->capacity + s2->capacity);
    for (int i = 0; i < s1->size; i++) {
        set_add(s, s1->elements[i]);
    }
    for (int i = 0; i < s2->size; i++) {
        bool is_in_set = false;
        for (int j = 0; j < s->size; j++) {
            if (strcmp(s2->elements[i], s->elements[j]) == 0) {
                is_in_set = true;
            }
        }
        if (!is_in_set) {
            set_add(s, s2->elements[i]);
        }
    }
    return s;
}

/**
 * Intersection of two sets.
 * @param s1 The first set.
 * @param s2 The second set.
 * @return The intersection of the two sets.
 */
set *set_intersection(set *s1, set *s2) {
    set *s = set_init(s1->capacity + s2->capacity);
    for (int i = 0; i < s1->size; i++) {
        for (int j = 0; j < s2->size; j++) {
            if (strcmp(s1->elements[i], s2->elements[j]) == 0) {
                set_add(s, s1->elements[i]);
            }
        }
    }
    return s;
}

/**
 * Difference of two sets.
 * @param s1 The first set.
 * @param s2 The second set.
 * @return The difference of the two sets.
 */
set *set_difference(set *s1, set *s2) {
    set *s = set_init(s1->capacity + s2->capacity);
    for (int i = 0; i < s1->size; i++) {
        bool is_in_set = false;
        for (int j = 0; j < s2->size; j++) {
            if (strcmp(s1->elements[i], s2->elements[j]) == 0) {
                is_in_set = true;
            }
        }
        if (!is_in_set) {
            set_add(s, s1->elements[i]);
        }
    }
    return s;
}

/**
 * Checks if the first set is a subset of the second set.
 * @param s1 The first set.
 * @param s2 The second set.
 * @return true if the first set is a subset of the second set, false otherwise.
 */
bool set_is_subset(set *s1, set *s2) {
    for (int i = 0; i < s1->size; i++) {
        bool is_in_set = false;
        for (int j = 0; j < s2->size; j++) {
            if (strcmp(s1->elements[i], s2->elements[j]) == 0) {
                is_in_set = true;
            }
        }
        if (!is_in_set) {
            return false;
        }
    }
    return true;
}

/**
 * Checks if the first set is equal to the second set.
 * @param s1 The first set.
 * @param s2 The second set.
 * @return true if the first set is equal to the second set, false otherwise.
 */
bool set_is_equal(set *s1, set *s2) {
    if (s1->size != s2->size) {
        return false;
    }
    for (int i = 0; i < s1->size; i++) {
        bool is_in_set = false;
        for (int j = 0; j < s2->size; j++) {
            if (strcmp(s1->elements[i], s2->elements[j]) == 0) {
                is_in_set = true;
            }
        }
        if (!is_in_set) {
            return false;
        }
    }
    return true;
}

/**
 * Checks if the relation is reflexive.
 * @param rel_arr The array of relation pairs.
 * @param univerzum The univerzum.
 * @return true if the relation is reflexive, false otherwise.
 */
bool reflexive(relations *rel_arr, univerzum *univerzum) {
    int table[univerzum->count][univerzum->count];
    rel_table(table, rel_arr, univerzum);
    for (int i = 0; i < univerzum->count; i++) {
        if (table[i][i] == 0) {
            return false;
        }
    }
    return true;
}

/**
 * Checks if the relation is symmetric.
 * @param rel_arr The array of relation pairs.
 * @param univerzum The univerzum.
 * @return true if the relation is symmetric, false otherwise.
 */
bool symmetric(relations *rel_arr, univerzum *univerzum) {
    int table[univerzum->count][univerzum->count];
    rel_table(table, rel_arr, univerzum);
    for (int i = 0; i < univerzum->count; i++) {
        for (int j = 0; j < univerzum->count; j++) {
            if (table[i][j] == 1 && table[j][i] == 0) {
                return false;
            }
        }
    }
    return true;
}

/**
 * Checks if the relation is antisymmetric.
 * @param rel_arr The array of relation pairs.
 * @param univerzum The univerzum.
 * @return true if the relation is antisymmetric, false otherwise.
 */
bool antisymmetric(relations *rel_arr, univerzum *univerzum) {
    int table[univerzum->count][univerzum->count];
    rel_table(table, rel_arr, univerzum);
    for (int i = 0; i < univerzum->count; i++) {
        for (int j = 0; j < univerzum->count; j++) {
            if (table[i][j] == 1 && table[j][i] == 1 && i != j) {
                return false;
            }
        }
    }
    return true;
}

/**
 * Checks if the relation is transitive.
 * @param rel_arr The array of relation pairs.
 * @param univerzum The univerzum.
 * @return true if the relation is transitive, false otherwise.
 */
bool transitive(relations *rel_arr, univerzum *univerzum) {
    int table[univerzum->count][univerzum->count];
    rel_table(table, rel_arr, univerzum);
    for (int i = 0; i < univerzum->count; i++) {
        for (int j = 0; j < univerzum->count; j++) {
            for (int k = 0; k < univerzum->count; k++) {
                if (table[i][j] == 1 && table[j][k] == 1 && table[i][k] == 0) {
                    return false;
                }
            }
        }
    }
    return true;
}

/**
 * Checks if the relation is function.
 * @param rel_arr The array of relation pairs.
 * @param univerzum The univerzum.
 * @return true if the relation is function, false otherwise.
 */
bool function(relations *rel_arr, univerzum *univerzum) {
    int table[univerzum->count][univerzum->count];
    rel_table(table, rel_arr, univerzum);
    for (int i = 0; i < univerzum->count; i++) {
        int pocet_relaci = 0;
        for (int j = 0; j < univerzum->count; j++) {
            if (table[i][j] == 1) {
                pocet_relaci++;
            }
            if (pocet_relaci == 2) {
                return false;
            }
        }
    }
    return true;
}

/** muj main, zatim je blby, ale umi spocitat univerzu
 *
 int main (int argc, char *argv[]){
    FILE *fp;
    if ((fp = fopen(argv[1], "r")) == NULL){
        printf("Nepodarilo se otevrit soubor!\n");
        return 0;
    }
    char radek[101];
    char *istr;
    set univerzum;
    univerzum.pocet = 0;
    univerzum.prvky = NULL;
    mnozina_t *mnoziny;
    mnoziny = NULL;
    int pocet_mnozin = 0;
    while (fgets(radek, 101, fp)){
        istr = strtok(radek, " \n");
        if (strcmp(istr,"U") == 0){
            istr = strtok(NULL, " \n");
            while (istr != NULL){
                set_add(&univerzum, istr);
                istr = strtok(NULL, " \n");
            }
        }
        else if (strcmp(istr,"S") == 0){
            mnozina_t mnozina;
            mnozina.prvky = NULL;
            mnozina.pocet = 0;
            istr = strtok(NULL, " \n");
            while(istr != NULL){
                mnozina_add_prvek(&mnozina, istr);
                istr = strtok(NULL, " \n");
            }
            pole_add_mnozina(mnoziny, mnozina, &pocet_mnozin);
        }
    }
    for (int i = 0; i < univerzum.pocet; i++){
        printf("%s\n",univerzum.prvky[i]);
    }
    //printf("\n%s\n", mnoziny[0].prvky[1]);
    //for (int i = 0; i < pocet_mnozin; i++){
    //    for (int j = 0; j < mnoziny[i].pocet; j++){
    //        printf("%s ", mnoziny[i].prvky[j]);
    //    }
    //    printf("\n");
    //}
    printf("dazhe syuda doshel\n");
    for (int i = 0; i < univerzum.pocet; i++){
        free(univerzum.prvky[i]);
    }
    //for (int i = 0; i < pocet_mnozin;  i++){
    //    for (int j = 0; j < mnoziny[i].pocet; j++){
    //        free(mnoziny[i].prvky[j]);
    //    }
    //}
    free(univerzum.prvky);
    //free(mnoziny);
    fclose(fp);
    return 0;
}
*/