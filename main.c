#include <stdio.h>
#include <string.h>
#include <malloc.h>
/** !muj main je uplne dolu!
 * struktura relace a mnoziny
 */
typedef struct {
    char ***pairs;
    int pocet;
} relace_t;

typedef struct{
    char **prvky;
    int pocet;
} mnozina_t;

/**
 * tabulka s 0 1 podle relace
 */
void rel_tabulka(int tabulka[N][N], relace_t *p_relace, mnozina_t *univerzum){
    for (int i = 0; i < p_relace->pocet; i++){
        for (int j = 0; j < univerzum->pocet; j++){
            if (strcmp(p_relace->pairs[i][0], univerzum->prvky[j]) == 0){
                for (int k = 0; k < univerzum->pocet; k++){
                    if (strcmp(p_relace->pairs[i][1], univerzum->prvky[k]) == 0){
                        tabulka[j][k] = 1;
                    }
                }
            }
        }
    }
    for (int i = 0; i < univerzum->pocet; i++){
        for (int j = 0; j < univerzum->pocet; j++){
            printf("%d ",tabulka[i][j]);
        }
        printf("\n");
    }
}
/**
 * funkce podle zadani
 */
int reflexive(relace_t *p_relace, mnozina_t *univerzum){
    int tabulka[N][N];
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            tabulka[i][j] = 0;
        }
    }
    rel_tabulka(tabulka, p_relace, univerzum);
    for (int i = 0; i < univerzum->pocet; i++){
        if (tabulka[i][i] == 0){
            printf("false\n");
            return 0;
        }
    }
    printf("true\n");
    return 0;
}

int symmetric(relace_t *p_relace, mnozina_t *univerzum){
    int tabulka[N][N];
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            tabulka[i][j] = 0;
        }
    }
    rel_tabulka(tabulka, p_relace, univerzum);
    for (int i = 0; i < univerzum->pocet; i++){
        for (int j = 0; j < univerzum->pocet; j++){
            if (tabulka[i][j] == 1 && tabulka[j][i] == 0){
                printf("false\n");
                return 0;
            }
        }
    }
    printf("true\n");
    return 0;
}

int antisymmetric(relace_t *p_relace, mnozina_t *univerzum){
    int tabulka[N][N];
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            tabulka[i][j] = 0;
        }
    }
    rel_tabulka(tabulka, p_relace, univerzum);
    for (int i = 0; i < univerzum->pocet; i++){
        for (int j = 0; j < univerzum->pocet; j++){
            if (tabulka[i][j] == 1 && tabulka[j][i] == 1 && i!=j){
                printf("false\n");
                return 0;
            }
        }
    }
    printf("true\n");
    return 0;
}

int transitive(relace_t *p_relace, mnozina_t *univerzum){
    int tabulka[N][N];
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            tabulka[i][j] = 0;
        }
    }
    rel_tabulka(tabulka, p_relace, univerzum);
    for (int i = 0; i < univerzum->pocet; i++){
        for (int j = 0; j < univerzum->pocet; j++){
            for (int k = 0; k < univerzum->pocet; k++){
                if (tabulka[i][j] == 1 && tabulka[j][k] == 1 && tabulka[i][k] == 0){
                    printf("false\n");
                    return 0;
                }
            }
        }
    }
    printf("true\n");
    return 0;
}

int function(relace_t *p_relace, mnozina_t *univerzum){
    int tabulka[N][N];
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            tabulka[i][j] = 0;
        }
    }
    rel_tabulka(tabulka, p_relace, univerzum);
    for (int i = 0; i < univerzum->pocet; i++){
        int pocet_relaci = 0;
        for (int j = 0; j < univerzum->pocet; j++){
            if (tabulka[i][j] == 1){
                pocet_relaci++;
            }
            if (pocet_relaci == 2){
                printf("false\n");
                return 0;
            }
        }
    }
    printf("true\n");
    return 0;
}
/**
 * funkce pro dodani prvku do mnoziny
 */
int mnozina_add_prvek(mnozina_t *mnozina, char *istr){
    char **f = realloc(mnozina->prvky, (mnozina->pocet + 1) * sizeof(char*));
    if (f == NULL){
        fprintf(stderr, "realloc se neprovedl!\n");
        return 1;
    }
    mnozina->prvky = f;
    mnozina->prvky[mnozina->pocet] = malloc(sizeof(char) * (strlen(istr)+1));
    if (mnozina->prvky[mnozina->pocet] == NULL){
        fprintf(stderr, "malloc se neprovedl!\n");
        return 1;
    }
    strcpy(mnozina->prvky[mnozina->pocet], istr);
    mnozina->pocet += 1;
    return 0;
}
/**
 * funkce pro dodani mnoziny do pole mnozin (zatim nekde je chyba)
 */
int pole_add_mnozina(mnozina_t *mnoziny, mnozina_t mnozina, int *pocet_mnozin){
    mnozina_t *f = realloc(mnoziny, (*pocet_mnozin + 1) * sizeof(mnozina_t));
    if (f == NULL){
        fprintf(stderr, "realloc se neprovedl!\n");
        return 1;
    }
    mnoziny = f;
    mnoziny[*pocet_mnozin] = mnozina;
    *pocet_mnozin += 1;
    return 0;
}

/**
 * Definition for bool
 */
typedef enum {
    false,
    true
} bool;

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
} set;

/**
 * Operation data structure
 */
typedef struct {
    char *name;
    void *pointer;
} operation;

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
    char *operation;
    char *param1;
    char *param2;
} command_t;

/**
 * Parses commands array.
 * @param commands Commands array
 * @param size Commands array size
 * @return Parsed commands array
 */
command_t *parse_commands(char **commands, int size) {
    command_t *result = malloc(sizeof(command_t) * size);
    for (int i = 0; i < size; i++) {
        char *command = commands[i];
        char *type = command;
        char *operation = strchr(command, ' ');
        char *param1 = strchr(operation + 1, ' ');
        char *param2 = strchr(param1 + 1, ' ');
        result[i].type = type[0];
        result[i].operation = operation + 1;
        result[i].param1 = param1 + 1;
        result[i].param2 = param2 + 1;
    }
    return result;
}

/**
 * Prints commands array.
 * @param commands Commands array
 * @param size Commands array size
 */
void print_commands(command_t *commands, int size) {
    for (int i = 0; i < size; i++) {
        printf("%c %s %s %s\n", commands[i].type, commands[i].operation,
               commands[i].param1, commands[i].param2);
    }
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
 * Prints the set.
 * @param s The set.
 */
void set_print(set *s) {
    for (int i = 0; i < s->size; i++) {
        printf("%s\n", s->elements[i]);
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
 * Main function.
 * @param argc The number of arguments.
 * @param argv The arguments.
 * @return 0 if the program ran successfully, 1 otherwise.
 */
int main(int argc, char *argv[]) {
    char **lines = malloc(sizeof(char *) * 100);
    lines[0] = "C intersect 2 3";
    lines[1] = "C union 2 3";

//    command_t *commands = parse_commands(lines, 2);
//    print_commands(commands, 2);

//    operation operations[] = {
//            {"union", set_union},
//            {"intersection", set_intersection},
//            {"difference", set_difference},
//            {"is_subset", set_is_subset},
//            {"is_equal", set_is_equal},
//    };
//
//    int p = find_operation(operations, 5, "intersection");
//    if (p == -1) {
//        fprintf(stderr, "Operation not found.\n");
//        return 1;
//    }

//    set *s = set_init(10);
//
//    set_add(s, "Hello");
//    set_add(s, "World");
//
//    set *s2 = set_init(10);
//    set_add(s2, "Hello");
//    set_add(s2, "World");
//    set_add(s2, "!");
//
//    set *s3 = set_union(s, s2);
//    set *s4 = set_intersection(s, s2);
//    set *s5 = set_difference(s2, s);
//    bool is_subset = set_is_subset(s, s2);
//    bool is_equal = set_is_equal(s, s2);
//
//    set_print(s3);
//    printf("\n");
//    set_print(s4);
//    printf("\n");
//    set_print(s5);
//    printf("\n");
//    printf("%d\n", is_subset);
//    printf("%d\n", is_equal);

    return 0;
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
    mnozina_t univerzum;
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
                mnozina_add_prvek(&univerzum, istr);
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
