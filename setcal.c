#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>

/**
 * -----------------------------------------------------------------------------
 * SYSTEM MODULE
 * -----------------------------------------------------------------------------
 */

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

void print_string(char *s) {
    printf("%s\n", s);
}

void print_string_size(char *s) {
    printf("%lu\n", strlen(s));
}

/**
 * Prints the error message and exits the program.
 * @param filename The name of the file where the error occurred.
 * @param line The line number where the error occurred.
 * @param function The function where the error occurred.
 * @param msg The error message.
 */
void print_error(const char *filename, int line, const char *function,
                 const char *msg) {
    fprintf(stderr, "%s:%d - [%s] %s\n", filename, line, function, msg);
    exit(EXIT_FAILURE);
}

/**
 * -----------------------------------------------------------------------------
 * STRING MODULE
 * -----------------------------------------------------------------------------
 */

char *pad_string(char *str, unsigned int max);

char *replace_char(char *str, char s, char r);

char *remove_char(char *str, char r);

void remove_spaces(char *str);

void remove_newlines(char *str);

/**
 * Pads the string with spaces at the end.
 * @param str The string.
 * @param max The max length of the string.
 * @return The padded string.
 */
char *pad_string(char *str, unsigned int max) {
    char *new_str = (char *) malloc(sizeof(char) * (max + 1));

    if (new_str == NULL) {
        print_error(__FILENAME__, __LINE__, __func__, "Malloc failed");
    }

    strcpy(new_str, str);

    if (strcmp(str, new_str) != 0) {
        print_error(__FILENAME__, __LINE__, __func__, "strcpy failed");
    }

    for (unsigned int i = strlen(str); i < max; i++) {
        new_str[i] = ' ';
    }
    new_str[max] = '\0';
    return new_str;
}

// create a function to check is string contains only characters
bool is_string_only_characters(char *str) {
    for (unsigned int i = 0; i < strlen(str); i++) {
//        printf("%c\n", str[i]);
//        printf("%d - %d\n", isalpha(str[i]), isspace(str[i]));
        if (isalpha(str[i]) == 0 && isspace(str[i]) == 0) {
            return false;
        }
    }
    return true;
}

/**
 * Replaces all occurrences of a character in a string with another character.
 * @param str The string.
 * @param s The character to be replaced.
 * @param r The character to replace with.
 * @return The new string.
 */
char *replace_char(char *str, char s, char r) {
    char *new_str = (char *) malloc(sizeof(char) * (strlen(str) + 1));

    if (new_str == NULL) {
        print_error(__FILENAME__, __LINE__, __func__, "Malloc failed");
    }

    strcpy(new_str, str);

    if (strcmp(str, new_str) != 0) {
        print_error(__FILENAME__, __LINE__, __func__, "strcpy failed");
    }

    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == s) {
            new_str[i] = r;
        }
    }
    new_str[strlen(str)] = '\0';
    return new_str;
}

/**
 * Removes spaces everywhere in the string.
 * @param str The string.
 * @return The string without spaces.
 */
char *remove_char(char *str, char r) {
    char *new_str = (char *) malloc(sizeof(char) * (strlen(str) + 1));

    if (new_str == NULL) {
        print_error(__FILENAME__, __LINE__, __func__, "Malloc failed");
        exit(EXIT_FAILURE);
    }

    int j = 0;
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] != r) {
            new_str[j] = str[i];
            j++;
        }
    }
    new_str[j] = '\0';
    return new_str;
}

/**
 * Removes spaces from the string.
 * @param str The string.
 */
void remove_spaces(char *str) {
    char *new_str = remove_char(str, ' ');
    strcpy(str, new_str);

    if (strcmp(str, new_str) != 0)
        print_error(__FILENAME__, __LINE__, __func__, "strcpy failed");

    free(new_str);
}

/**
 * Removes new lines from the string.
 * @param str The string.
 */
void remove_newlines(char *str) {
    char *new_str = remove_char(str, '\n');
    new_str = remove_char(new_str, '\r');
    strcpy(str, new_str);

    if (strcmp(str, new_str) != 0)
        print_error(__FILENAME__, __LINE__, __func__, "strcpy failed");

    free(new_str);
}

/**
 * -----------------------------------------------------------------------------
 * VECTOR MODULE
 * -----------------------------------------------------------------------------
 */

/**
 * Vector data structure type
 */
typedef struct {
    int size;
    int capacity;
    char **elements;
} vector_t;

vector_t *vector_init(int capacity);

unsigned int find_max_vector_element_size(vector_t *v);

void resize_all(vector_t *v, unsigned int max);

void vector_add(vector_t *v, char *s);

bool vector_contains(vector_t *v, char *s);

void vector_remove(vector_t *v, int index);

void vector_foreach(vector_t *v, void (*f)(char *));

void vector_free(vector_t *v);

/**
 * Initializes the vector
 * @param capacity The capacity of the vector.
 * @return The initialized vector.
 */
vector_t *vector_init(int capacity) {
    if (capacity < 1) {
        print_error(__FILENAME__, __LINE__, __func__,
                    "Capacity must be greater than 0");
    }

    vector_t *v = (vector_t *) malloc(sizeof(vector_t));

    if (v == NULL) {
        print_error(__FILENAME__, __LINE__, __func__, "Malloc failed");
    }

    v->size = 0;
    v->capacity = capacity;
    v->elements = (char **) malloc(capacity * sizeof(char *));

    if (v->elements == NULL) {
        print_error(__FILENAME__, __LINE__, __func__, "Malloc failed");
    }

    return v;
}

/**
 * Finds the longest element in the vector.
 * @param v The vector.
 * @return Length of the longest element.
 */
unsigned int find_max_vector_element_size(vector_t *v) {
    unsigned int max = 0;
    for (int i = 0; i < v->size; i++) {
        if (strlen(v->elements[i]) > max) {
            max = strlen(v->elements[i]);
        }
    }
    return max;
}

/**
 * Resizes all elements to the max length.
 * @param v The vector.
 * @param max The max length of the elements.
 */
void resize_all(vector_t *v, unsigned int max) {
    for (int i = 0; i < v->size; i++) {
        v->elements[i] = pad_string(v->elements[i], max);
    }
}

/**
 * Adds a string to the vector.
 * @param v The vector.
 * @param s The string.
 */
void vector_add(vector_t *v, char *s) {
    if (v->size == v->capacity) {
        v->capacity *= 2;
        v->elements = (char **) realloc(v->elements,
                                        v->capacity * sizeof(char *));

        if (v->elements == NULL) {
            print_error(__FILENAME__, __LINE__, __func__, "Realloc failed");
        }
    }
    v->elements[v->size] = remove_char(s, ' ');
    v->size++;

    resize_all(v, find_max_vector_element_size(v));
}

bool vector_contains(vector_t *v, char *s) {
    for (int i = 0; i < v->size; i++) {
        if (strcmp(v->elements[i], s) == 0) {
            return true;
        }
    }
    return false;
}

/**
 * Remove element from the vector.
 * @param v The vector.
 * @param index The index of the element.
 */
void vector_remove(vector_t *v, int index) {
    if (index < 0 || index >= v->size) {
        print_error(__FILENAME__, __LINE__, __func__, "Index out of bounds");
    }

    for (int i = index; i < v->size - 1; i++) {
        v->elements[i] = v->elements[i + 1];
    }
    v->size--;
}

/**
 * Applies the function to each element of vector.
 * @param v The vector.
 * @param f The function.
 */
void vector_foreach(vector_t *v, void (*f)(char *)) {
    if (v == NULL) {
        print_error(__FILENAME__, __LINE__, __func__, "Vector is NULL");
    }

    if (f == NULL) {
        print_error(__FILENAME__, __LINE__, __func__, "Function is NULL");
    }

    for (int i = 0; i < v->size; i++) {
        f(v->elements[i]);
    }
}

// create a function to convert vector args to string with delimeter
char *vector_to_string(vector_t *v, char *delim) {
    char *str = (char *) malloc(sizeof(char) * (v->size + 1));

    if (str == NULL)
        print_error(__FILENAME__, __LINE__, __func__, "Malloc failed");

    str[0] = '\0';
    for (int i = 0; i < v->size; i++) {
        strcat(str, v->elements[i]);
        if (i != v->size - 1) {
            strcat(str, delim);
        }
    }
    return str;
}

/**
 * Frees the vector.
 * @param v The vector.
 */
void vector_free(vector_t *v) {
    if (v == NULL) {
        print_error(__FILENAME__, __LINE__, __func__, "Vector is NULL");
    }

    if (v->elements == NULL) {
        print_error(__FILENAME__, __LINE__, __func__,
                    "Vector elements are NULL");
    }

    for (int i = 0; i < v->size; i++) {
        if (v->elements[i] == NULL) {
            print_error(__FILENAME__, __LINE__, __func__,
                        "Vector element is NULL");
        }
    }

    for (int i = 0; i < v->size; i++) {
        free(v->elements[i]);
    }
    free(v->elements);
    free(v);
}

/**
 * -----------------------------------------------------------------------------
 * SET MODULE [SET]
 * -----------------------------------------------------------------------------
 */

/**
 * Set type.
 */
typedef struct set {
    unsigned int index;
    int size;
    int capacity;
    char **elements;
} set_t;

set_t *set_init(int capacity);

set_t *set_init_indexed(int index, int capacity);

void set_add(set_t *s, char *e);

void set_add_row(set_t *s, int row);

void set_print(set_t *s);

/**
 * Creates a new set.
 * @param capacity The initial capacity of the set.
 * @return The new set.
 */
set_t *set_init(int capacity) {
    set_t *s = malloc(sizeof(set_t));

    if (s == NULL)
        print_error(__FILENAME__, __LINE__, __func__, "Malloc failed");

    s->index = 0;
    s->size = 0;
    s->capacity = capacity;
    s->elements = malloc(sizeof(char *) * capacity);

    if (s->elements == NULL)
        print_error(__FILENAME__, __LINE__, __func__, "Malloc failed");

    return s;
}

/**
 * Creates a new set.
 * @param index The index of the set.
 * @param capacity The initial capacity of the set.
 * @return The new set.
 */
set_t *set_init_indexed(int index, int capacity) {
    if (index < 1)
        print_error(__FILENAME__, __LINE__, __func__,
                    "Index is negative or zero");

    set_t *s = malloc(sizeof(set_t));

    if (s == NULL)
        print_error(__FILENAME__, __LINE__, __func__, "Malloc failed");

    s->index = index;
    s->size = 0;
    s->capacity = capacity;
    s->elements = malloc(sizeof(char *) * capacity);

    if (s->elements == NULL)
        print_error(__FILENAME__, __LINE__, __func__, "Malloc failed");

    return s;
}

/**
 * Adds an element to the set.
 * @param s The set.
 * @param e The element to add.
 */
void set_add(set_t *s, char *e) {
    if (s->size == s->capacity) {
        s->capacity *= 2;
        s->elements = realloc(s->elements, sizeof(char *) * s->capacity);

        if (s->elements == NULL)
            print_error(__FILENAME__, __LINE__, __func__, "Realloc failed");
    }
    s->elements[s->size] = e;
    s->size++;
}

///**
// * Adds a row number to the set.
// * @param s The set.
// * @param e The element to add.
// */
//void set_add_row(set_t *s, int row) {
//    s->row = row;
//}

/**
 * Prints the set.
 * @param s The set.
 */
void set_print(set_t *s) {
    printf("Set %d: ", s->index);
    for (int i = 0; i < s->size; i++) {
        printf("%s ", s->elements[i]);
    }
    printf("\n");
}

/**
 * -----------------------------------------------------------------------------
 * SET MODULE [SET VECTOR]
 * -----------------------------------------------------------------------------
 */

/**
 * Set vector type.
 */
typedef struct set_vector_t {
    int size;
    int capacity;
    set_t **sets;
} set_vector_t;

set_vector_t *set_vector_init(int capacity) {
    if (capacity < 1)
        print_error(__FILENAME__, __LINE__, __func__, "Invalid capacity");

    set_vector_t *sv = malloc(sizeof(set_vector_t));

    if (sv == NULL)
        print_error(__FILENAME__, __LINE__, __func__, "Malloc failed");

    sv->size = 0;
    sv->capacity = capacity;
    sv->sets = malloc(sizeof(set_t *) * capacity);

    if (sv->sets == NULL)
        print_error(__FILENAME__, __LINE__, __func__, "Malloc failed");

    return sv;
}

// create a function to add to vector
void set_vector_add(set_vector_t *sv, set_t *s) {
    if (sv->size == sv->capacity) {
        sv->capacity *= 2;
        sv->sets = realloc(sv->sets, sizeof(set_t *) * sv->capacity);

        if (sv->sets == NULL)
            print_error(__FILENAME__, __LINE__, __func__, "Realloc failed");
    }

    sv->sets[sv->size] = s;
    sv->size++;
}


// create a function to find vector by index property
set_t *set_vector_find(set_vector_t *sv, int index) {
    for (int i = 0; i < sv->size; i++) {
        if (sv->sets[i]->index == index) {
            return sv->sets[i];
        }
    }
    return NULL;
}


void set_vector_print(set_vector_t *sv) {
    for (int i = 0; i < sv->size; i++) {
        set_print(sv->sets[i]);
    }
}

/**
 * -----------------------------------------------------------------------------
 * SET MODULE [SET MATH]
 * -----------------------------------------------------------------------------
 */

bool _set_is_empty(set_t *s);

bool set_is_empty(int n, ...);

set_t *_set_union(set_t *s1, set_t *s2);

set_t *set_union(int n, ...);

set_t *_set_intersection(set_t *s1, set_t *s2);

set_t *set_intersection(int n, ...);

set_t *_set_diff(set_t *s1, set_t *s2);

set_t *set_diff(int n, ...);

bool _set_is_subset(set_t *s1, set_t *s2);

bool set_is_subset(int n, ...);

bool _set_is_equal(set_t *s1, set_t *s2);

bool set_is_equal(int n, ...);

/**
 * Checks if a set is empty.
 * @param s The set.
 * @return True if the set is empty, false otherwise.
 */
bool _set_is_empty(set_t *s) {
    return s->size == 0;
}
/**
 * Checks if a set is empty.
 * @param n The number of sets.
 * @param ... The sets.
 * @return True if the set is empty, false otherwise.
 */
bool set_is_empty(int n, ...) {
    va_list args;
    va_start(args, n);

    for (int i = 0; i < n; i++) {
        set_t *s = va_arg(args, set_t *);
        if (!_set_is_empty(s)) {
            va_end(args);
            return false;
        }
    }

    va_end(args);
    return true;
}

/**
 * Returns the union of two sets.
 * @param s1 The first set.
 * @param s2 The second set.
 * @return The union of the two sets.
 */
set_t *_set_union(set_t *s1, set_t *s2) {
    set_t *s = set_init(s1->capacity + s2->capacity);

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
 * Returns the union of sets.
 * @param n The number of sets.
 * @param ... The sets.
 * @return The union of the sets.
 */
set_t *set_union(int n, ...) {
    va_list sets;
    va_start(sets, n);

    set_t *s = set_init(1);

    for (int i = 0; i < n; i++) {
        set_t *s_i = va_arg(sets, set_t *);
        set_t *s_union = _set_union(s, s_i);
        s = s_union;
    }

    va_end(sets);

    return s;
}

/**
 * Returns the intersection of sets.
 * @param s1 The first set.
 * @param s2 The second set.
 * @return The intersection of the sets.
 */
set_t *_set_intersection(set_t *s1, set_t *s2) {
    set_t *s = set_init(s1->capacity + s2->capacity);

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
 * Returns the intersection of sets.
 * @param n The number of sets.
 * @param ... The sets.
 * @return The intersection of the sets.
 */
set_t *set_intersection(int n, ...) {
    va_list sets;
    va_start(sets, n);

    set_t *s = va_arg(sets, set_t *);

    for (int i = 1; i < n; i++) {
        set_t *s_i = va_arg(sets, set_t *);
        set_t *s_intersection = _set_intersection(s, s_i);
        s = s_intersection;
    }

    va_end(sets);

    return s;
}

/**
 * Difference of two sets.
 * @param s1 The first set.
 * @param s2 The second set.
 * @return The difference of the two sets.
 */
set_t *_set_diff(set_t *s1, set_t *s2) {
    set_t *s = set_init(s1->capacity + s2->capacity);

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
 * Difference of sets.
 * @param n The number of sets.
 * @param ... The sets.
 * @return The difference of the sets.
 */
set_t *set_diff(int n, ...) {
    va_list sets;
    va_start(sets, n);

    set_t *s = va_arg(sets, set_t *);

    for (int i = 1; i < n; i++) {
        set_t *s_i = va_arg(sets, set_t *);
        set_t *s_diff = _set_diff(s, s_i);
        s = s_diff;
    }

    va_end(sets);

    return s;
}

/**
 * Checks if the first set is a subset of the second set.
 * @param s1 The first set.
 * @param s2 The second set.
 * @return true if the first set is a subset of the second set, false otherwise.
 */
bool _set_is_subset(set_t *s1, set_t *s2) {
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
 * Checks if the first set is a subset of the second set.
 * @param n The number of sets.
 * @param ... The sets.
 * @return true if the first set is a subset of the second set, false otherwise.
 */
bool set_is_subset(int n, ...) {
    va_list sets;
    va_start(sets, n);

    set_t *s1 = va_arg(sets, set_t *);
    set_t *s2 = va_arg(sets, set_t *);

    bool is_subset = _set_is_subset(s1, s2);

    va_end(sets);

    return is_subset;
}

/**
 * Checks if the first set is equal to the second set.
 * @param s1 The first set.
 * @param s2 The second set.
 * @return true if the first set is equal to the second set, false otherwise.
 */
bool _set_is_equal(set_t *s1, set_t *s2) {
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
 * Checks if the first set is equal to the second set.
 * @param n The number of sets.
 * @param ... The sets.
 * @return true if the first set is equal to the second set, false otherwise.
 */
bool set_is_equal(int n, ...) {
    va_list sets;
    va_start(sets, n);

    set_t *s1 = va_arg(sets, set_t *);
    set_t *s2 = va_arg(sets, set_t *);

    bool is_equal = _set_is_equal(s1, s2);

    va_end(sets);

    return is_equal;
}

/**
 * -----------------------------------------------------------------------------
 * COMMAND MODULE [COMMAND]
 * -----------------------------------------------------------------------------
 */

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
 * Operation type
 */
typedef struct {
    char *name;
    commands type;
} operation;

typedef struct operation_vector_t {
    int size;
    int capacity;
    operation **operations;
} operation_vector_t;

/**
 * Command type
 */
typedef struct {
    commands type;
    vector_t args;
} command_t;

typedef struct command_system_t command_system_t;
/**
 * Command vector type
 */
typedef struct {
    int size;
    int capacity;
    command_t *commands;
    command_system_t *system;
} command_vector_t;


typedef struct command_system_t {
    char *filename;
    command_vector_t *cv;
    operation_vector_t *operation_vector;
    set_t *universe;
    set_vector_t *set_vector;
};

command_t *init_command();

command_t *init_command_with_type(commands type);

void set_command_args(command_t *c, vector_t *args);

void add_command_arg(command_t *c, char *arg);

void print_command(command_t *c);

void free_command(command_t *c);

command_t *parse_command(char *s);

/**
 * Initializes a command.
 * @return The initialized command.
 */
command_t *init_command() {
    command_t *c = (command_t *) malloc(sizeof(command_t));

    if (c == NULL)
        print_error(__FILENAME__, __LINE__, __func__, "Malloc failed");

    c->type = 0;
    c->args = *vector_init(1);
    return c;
}

/**
 * Initializes a command with a type.
 * @param type The type of the command.
 * @return The initialized command.
 */
command_t *init_command_with_type(commands type) {
    command_t *c = init_command();
    c->type = type;
    return c;
}


/**
 * Sets the command arguments.
 * @param c The command.
 * @param args The arguments.
 */
void set_command_args(command_t *c, vector_t *args) {
    if (args == NULL)
        print_error(__FILENAME__, __LINE__, __func__, "Args is NULL");

    if (&(c->args) == NULL)
        print_error(__FILENAME__, __LINE__, __func__, "Command args is NULL");

    c->args = *args;
}

/**
 * Adds a command argument.
 * @param c The command.
 * @param arg The argument.
 */
void add_command_arg(command_t *c, char *arg) {
    if (&(c->args) == NULL)
        print_error(__FILENAME__, __LINE__, __func__, "Command args is NULL");

    vector_add(&c->args, arg);
}

/**
 * Prints the command.
 * @param c The command.
 */
void print_command(command_t *c) {
    switch (c->type) {
        case U:
            printf("U");
            break;
        case S:
            printf("S");
            break;
        case R:
            printf("R");
            break;
        case C:
            printf("C");
            break;
    }

    if (c->args.size > 0 && c->type != 0) {
        printf(" ");
    }

    for (int i = 0; i < c->args.size; i++) {
        printf(i < c->args.size - 1 ? "%s " : "%s",
               (char *) c->args.elements[i]);
    }
    printf("\n");
}

/**
 * Frees the command.
 * @param c The command.
 */
void free_command(command_t *c) {
    if (&(c->args) == NULL)
        print_error(__FILENAME__, __LINE__, __func__, "Command args is NULL");

    if (c->args.size == 0)
        print_error(__FILENAME__, __LINE__, __FUNCTION__, "Invalid args");


    vector_free(&c->args);
    free(c);
}

/**
 * Parses a command.
 * @param s The command string.
 * @return The command.
 */
command_t *parse_command(char *s) {
    command_t *c = init_command();
    vector_t *args = vector_init(10);

    if (s == NULL)
        print_error(__FILENAME__, __LINE__, __func__, "String is NULL");

    char *copy = strdup(s);
    char *token = strtok(copy, " ");

    while (token != NULL) {
        vector_add(args, token);
        token = strtok(NULL, " ");
    }

    if (args->size == 0)
        print_error(__FILENAME__, __LINE__, __FUNCTION__, "Invalid command");

    vector_foreach(args, remove_spaces);
    vector_foreach(args, remove_newlines);

    if (strcmp(args->elements[0], "U") == 0) {
        c->type = U;
    } else if (strcmp(args->elements[0], "S") == 0) {
        c->type = S;
    } else if (strcmp(args->elements[0], "R") == 0) {
        c->type = R;
    } else if (strcmp(args->elements[0], "C") == 0) {
        c->type = C;
    } else {
        print_error(__FILENAME__, __LINE__, __FUNCTION__, "Invalid command");
    }

    vector_remove(args, 0);

    c->args = *args;
    return c;
}

command_t bool_to_command(bool b) {
    command_t *c = init_command();

    c->args = *vector_init(1);
    vector_add(&c->args, b ? "true" : "false");

    return *c;
}

// create a function to convert set to command
command_t *set_to_command(set_t *s) {
    command_t *c = init_command();
    vector_t *args = vector_init(1);

    if (s == NULL)
        print_error(__FILENAME__, __LINE__, __func__, "Set is NULL");

    c->type = S;

    for (int i = 0; i < s->size; i++) {
        vector_add(args, s->elements[i]);
    }

    c->args = *args;

    return c;
}

/**
 * -----------------------------------------------------------------------------
 * COMMAND MODULE [COMMAND VECTOR]
 * -----------------------------------------------------------------------------
 */

command_vector_t *command_vector_init(int capacity);

void command_vector_add(command_vector_t *cv, command_t c);

void command_vector_replace(command_vector_t *cv, command_t c, int index);

bool validate_command_vector(command_vector_t *cv, operation_vector_t *ov);

void attach_command_system(command_vector_t *cv, command_system_t *cs);

vector_t *get_unique_command_types(command_vector_t *cv);

command_t *find_command_by_type(command_vector_t *cv, commands type);

command_vector_t *find_command_by_type_all(command_vector_t *cv, commands type);

command_vector_t *
command_vector_slice(command_vector_t *cv, int start, int end);

bool command_vector_contains_type(command_vector_t *cv, commands type);

void command_vector_print(command_vector_t *cv);

void command_vector_free(command_vector_t *cv);

command_vector_t *parse_file(char *filename);

/**
 * Initializes a command vector.
 * @param capacity The capacity.
 * @return The initialized command vector.
 */
command_vector_t *command_vector_init(int capacity) {
    command_vector_t *cv = (command_vector_t *) malloc(
            sizeof(command_vector_t));

    if (cv == NULL)
        print_error(__FILENAME__, __LINE__, __func__, "Malloc failed");

    cv->size = 0;
    cv->capacity = capacity;
    cv->commands = (command_t *) malloc(capacity * sizeof(command_t));

    if (cv->commands == NULL)
        print_error(__FILENAME__, __LINE__, __func__, "Malloc failed");

    return cv;
}

/**
 * Adds a command to the command vector.
 * @param cv The command vector.
 * @param c The command.
 */
void command_vector_add(command_vector_t *cv, command_t c) {
    if (cv->size == cv->capacity) {
        cv->capacity *= 2;
        cv->commands = (command_t *) realloc(cv->commands,
                                             cv->capacity * sizeof(command_t));

        if (cv->commands == NULL)
            print_error(__FILENAME__, __LINE__, __func__, "Realloc failed");
    }
    cv->commands[cv->size] = c;
    cv->size++;
}

/**
 * Replaces a command in the command vector.
 * @param cv The command vector.
 * @param c The command.
 * @param index The index.
 */
void command_vector_replace(command_vector_t *cv, command_t c, int index) {
    if (index < 0 || index >= cv->size)
        print_error(__FILENAME__, __LINE__, __FUNCTION__,
                    "Index out of bounds");

    cv->commands[index] = c;
}

/**
 * Validate command vector.
 * @param cv The command vector.
 * @return true if valid, false otherwise.
 */
bool validate_command_vector(command_vector_t *cv, operation_vector_t *ov) {
    if (cv == NULL)
        print_error(__FILENAME__, __LINE__, __func__, "Command vector is NULL");

    if (cv->size == 0)
        print_error(__FILENAME__, __LINE__, __FUNCTION__,
                    "Invalid command vector");

    command_t *u_command = find_command_by_type(cv, U);
    command_vector_t *s_commands = find_command_by_type_all(cv, S);
    command_vector_t *c_commands = find_command_by_type_all(cv, C);
    vector_t *unique_command_types = get_unique_command_types(cv);

    /**
     * Commands vector must contain only the following commands: U, S, R, C.
     */
    for (int i = 0; i < cv->size; i++) {
        if (cv->commands[i].type != U && cv->commands[i].type != S &&
            cv->commands[i].type != R && cv->commands[i].type != C) {
            print_error(__FILENAME__, __LINE__, __FUNCTION__,
                        "File has unknown command");
        }
    }

    /**
     * Commands must be in order: U, S/R, C
     */
    for (int i = 0; i < cv->size; i++) {
        if (cv->commands[i].type == U) {
            if (i != 0) {
                print_error(__FILENAME__, __LINE__, __FUNCTION__,
                            "U command must be the first command");
            }
        } else if (cv->commands[i].type == S || cv->commands[i].type == R) {
            if (i == 0) {
                print_error(__FILENAME__, __LINE__, __FUNCTION__,
                            "S command must be after U command");
            } else {
                command_vector_t *commands_before = command_vector_slice(cv, 0,
                                                                         i);
                command_vector_t *commands_after = command_vector_slice(cv, i,
                                                                        cv->size -
                                                                        1);

                if (command_vector_contains_type(commands_before, C) ||
                    command_vector_contains_type(commands_after, U)) {
                    print_error(__FILENAME__, __LINE__, __FUNCTION__,
                                "S and R commands must be after U command and before C commands");
                }
            }
        } else if (cv->commands[i].type == C) {
            if (i == 0) {
                print_error(__FILENAME__, __LINE__, __FUNCTION__,
                            "C command must be after U command");
            } else {
                command_vector_t *commands_after =
                        command_vector_slice(cv, i, cv->size - 1);
                if (command_vector_contains_type(commands_after, U) ||
                    command_vector_contains_type(commands_after, S) ||
                    command_vector_contains_type(commands_after, R)) {
                    print_error(__FILENAME__, __LINE__, __FUNCTION__,
                                "C command must be after U, S and R commands. No other commands cannot be after C");
                }
            }
        }
    }




    /**
     * Commands must contain at least two command
     */
    if (unique_command_types->size < 2) {
        print_error(__FILENAME__, __LINE__, __FUNCTION__,
                    "File must contain at least two commands");
    }


    /**
     * Commands must contains something except U command
     */
    for (int i = 0; i < unique_command_types->size; i++) {
        if (strcmp(unique_command_types->elements[i], "U") == 0 &&
            unique_command_types->size == 1) {
            print_error(__FILENAME__, __LINE__, __FUNCTION__,
                        "File must not contain only universe");
        }
    }

    /**
     * Command vector must contain only one U command.
     */
    int u_count = 0;
    for (int i = 0; i < cv->size; i++) {
        if (cv->commands[i].type == U) {
            u_count++;
        }
    }
    if (u_count != 1) {
        print_error(__FILENAME__, __LINE__, __FUNCTION__,
                    "There are multiple universes");
    }

    /**
     * Universe items length must not be greater than 30.
     */
    for (int i = 0; i < u_command->args.size; i++) {
        if (strlen(u_command->args.elements[i]) > 30) {
            print_error(__FILENAME__, __LINE__, __FUNCTION__,
                        "Universe item has length greater than 30");
        }
    }

    /**
     * Universe command can contain only strings.
     */
    if (is_string_only_characters(
            vector_to_string(&(u_command->args), " ")) == false) {
        print_error(__FILENAME__, __LINE__, __FUNCTION__,
                    "Invalid command vector");
    }

    /**
     * Check if universe does not contain false and true
     */
    for (int i = 0; i < u_command->args.size; i++)
        if (strcmp(u_command->args.elements[i], "false") == 0 ||
            strcmp(u_command->args.elements[i], "true") == 0) {
            print_error(__FILENAME__, __LINE__, __FUNCTION__,
                        "Universe contains true or false");
        }

    /**
     * Check if universe does not contain operations.
     */
    for (int i = 0; i < ov->size; i++) {
        if (vector_contains(&(u_command->args), ov->operations[i]->name) ==
            true) {
            print_error(__FILENAME__, __LINE__, __FUNCTION__,
                        "Universe contains operations");
        }
    }

    /**
     * Check if there are no repeats in the universe
     */
    for (int i = 0; i < u_command->args.size; i++) {
        for (int j = i + 1; j < u_command->args.size; j++) {
            if (strcmp(u_command->args.elements[i],
                       u_command->args.elements[j]) == 0) {
                print_error(__FILENAME__, __LINE__, __FUNCTION__,
                            "Universe contains repeating elements");
            }
        }
    }

    /**
     * Check if all sets has items only form universe.
     */
    for (int i = 0; i < s_commands->size; i++) {
        for (int j = 0; j < s_commands->commands[i].args.size; j++) {
            if (vector_contains(&(u_command->args),
                                s_commands->commands[i].args.elements[j]) ==
                false) {
                print_error(__FILENAME__, __LINE__, __FUNCTION__,
                            "Set contains elements not from universe");
            }
        }
    }

    /**
     * Check if there are not repeats in S commands
     */
    for (int i = 0; i < s_commands->size; i++) {
        command_t *s_command = &s_commands->commands[i];
        for (int j = 0; j < s_command->args.size; j++) {
            for (int k = j + 1; k < s_command->args.size; k++) {
                if (strcmp(s_command->args.elements[j],
                           s_command->args.elements[k]) == 0) {
                    print_error(__FILENAME__, __LINE__, __FUNCTION__,
                                "Set contains repeating elements");
                }
            }
        }
    }

    /**
     * Check if all operations in command vector exist
     */
    for (int i = 0; i < c_commands->size; i++) {
        command_t c_command = c_commands->commands[i];
        for (int j = 0; j < ov->size; j++) {
            if (strcmp(
                    c_command.args.elements[0],
                    ov->operations[j]->name) == 0)
                break;

            if (j == ov->size - 1) {
                print_error(__FILENAME__, __LINE__, __FUNCTION__,
                            "Operation does not exist");
            }
        }
    }


    return true;
}

/**
 * Attaches commands system to the given command vector.
 * @param cv Command vector.
 * @param cs Command system.
 */
void attach_command_system(command_vector_t *cv, command_system_t *cs) {
    cv->system = cs;
}

/**
 * Gets unique command types from the given command vector.
 * @param cv Command vector.
 * @return Unique command types.
 */
vector_t *get_unique_command_types(command_vector_t *cv) {
    vector_t *unique_command_types = vector_init(1);

    for (int i = 0; i < cv->size; i++) {
        char *command_type = " ";
        switch (cv->commands[i].type) {
            case U:
                command_type = "U";
                break;
            case S:
                command_type = "S";
                break;
            case R:
                command_type = "R";
                break;
            case C:
                command_type = "C";
                break;
        }

        if (vector_contains(unique_command_types,
                            command_type) ==
            false) {
            vector_add(unique_command_types, command_type);
        }
    }

    return unique_command_types;
}

/**
 * Finds a command in the command vector.
 * @param cv The command vector.
 * @param type The command type.
 * @return The command or NULL if not found.
 */
command_t *find_command_by_type(command_vector_t *cv, commands type) {
    for (int i = 0; i < cv->size; i++) {
        if (cv->commands[i].type == type) {
            return &cv->commands[i];
        }
    }
    return NULL;
}

// create a function to find all commands of a certain type
command_vector_t *
find_command_by_type_all(command_vector_t *cv, commands type) {
    command_vector_t *commands = command_vector_init(1);

    for (int i = 0; i < cv->size; i++) {
        if (cv->commands[i].type == type) {
            command_vector_add(commands, cv->commands[i]);
        }
    }

    return commands;
}


command_vector_t *
command_vector_slice(command_vector_t *cv, int start, int end) {
    if (start < 0 || end > cv->size || start > end) {
        print_error(__FILENAME__, __LINE__, __FUNCTION__,
                    "Invalid start or end");
    }

    command_vector_t *commands = command_vector_init(1);

    for (int i = start; i < end; i++) {
        command_vector_add(commands, cv->commands[i]);
    }

    return commands;
}

/**
 * Checks if there is a command with the given type in the command vector.
 * @param cv The command vector.
 * @param type The command type.
 * @return True if there is a command with the given type, false otherwise.
 */
bool command_vector_contains_type(command_vector_t *cv, commands type) {
    for (int i = 0; i < cv->size; i++) {
        if (cv->commands[i].type == type) {
            return true;
        }
    }
    return false;
}

/**
 * Prints the command vector.
 * @param cv The command vector.
 */
void command_vector_print(command_vector_t *cv) {
    for (int i = 0; i < cv->size; i++) {
        print_command(&cv->commands[i]);
    }
}

/**
 * Frees the command vector.
 * @param cv The command vector.
 */
void command_vector_free(command_vector_t *cv) {
    if (cv->commands == NULL)
        print_error(__FILENAME__, __LINE__, __FUNCTION__,
                    "Invalid pointer");

    free(cv->commands);
    free(cv);
}

/**
 * Parses file to command vector.
 * @param filename The file name.
 * @return The command vector.
 */
command_vector_t *parse_file(char *filename) {
    command_vector_t *cv = command_vector_init(1);
    FILE *fp = fopen(filename, "r");

    if (fp == NULL)
        print_error(__FILENAME__, __LINE__, __func__, "File not found");

    char *line = NULL;
    size_t len = 0;

    while (getline(&line, &len, fp) != -1) {
        command_t *c = parse_command(line);
        command_vector_add(cv, *c);
    }

    fclose(fp);

    return cv;
}

/**
 * -----------------------------------------------------------------------------
 * COMMAND MODULE [OPERATION]
 * -----------------------------------------------------------------------------
 */

typedef struct {
    char ***pairs;
    int count_pairs;
} relations;

/**
 * Initializes an operation.
 * @param name The name.
 * @return The initialized operation.
 */
operation *operation_init(char *name, commands type) {
    operation *o = (operation *) malloc(sizeof(operation));

    if (o == NULL)
        print_error(__FILENAME__, __LINE__, __func__, "Malloc failed");

    o->name = name;
    o->type = type;

    return o;
}


/**
 * Frees an operation.
 * @param o The operation.
 */
void operation_free(operation *o) {
    if (o == NULL)
        print_error(__FILENAME__, __LINE__, __func__, "Invalid pointer");

    free(o);
}

/**
 * -----------------------------------------------------------------------------
 * COMMAND MODULE [OPERATION VECTOR]
 * -----------------------------------------------------------------------------
 */

operation_vector_t *operation_vector_init(int capacity);

void operation_vector_add(operation_vector_t *ov, operation *o);

operation *operation_vector_find(operation_vector_t *ov, char *name);

bool operation_vector_contains(operation_vector_t *ov, char *name);

void operation_vector_free(operation_vector_t *ov);

/**
 * Initializes an operation vector.
 * @param capacity The capacity.
 * @return The initialized operation vector.
 */
operation_vector_t *operation_vector_init(int capacity) {
    if (capacity < 1)
        print_error(__FILENAME__, __LINE__, __func__, "Invalid capacity");

    operation_vector_t *ov = (operation_vector_t *) malloc(
            sizeof(operation_vector_t));

    if (ov == NULL)
        print_error(__FILENAME__, __LINE__, __func__, "Malloc failed");

    ov->size = 0;
    ov->capacity = capacity;
    ov->operations = (operation **) malloc(sizeof(operation *) * capacity);

    if (ov->operations == NULL)
        print_error(__FILENAME__, __LINE__, __func__, "Malloc failed");

    return ov;
}

/**
 * Adds an operation to the operation vector.
 * @param ov The operation vector.
 * @param o The operation.
 */
void operation_vector_add(operation_vector_t *ov, operation *o) {
    if (ov->size == ov->capacity) {
        ov->capacity *= 2;
        ov->operations = (operation **) realloc(ov->operations,
                                                sizeof(operation *) *
                                                ov->capacity);

        if (ov->operations == NULL)
            print_error(__FILENAME__, __LINE__, __func__, "Malloc failed");
    }

    ov->operations[ov->size] = o;
    ov->size++;
}

/**
 * Gets an operation from the operation vector.
 * @param ov The operation vector.
 * @param name The name.
 * @return The operation.
 */
operation *operation_vector_find(operation_vector_t *ov, char *name) {
    for (int i = 0; i < ov->size; i++) {
        if (strcmp(ov->operations[i]->name, name) == 0)
            return ov->operations[i];
    }
    return NULL;
}

bool operation_vector_contains(operation_vector_t *ov, char *name) {
    for (int i = 0; i < ov->size; i++) {
        if (strcmp(ov->operations[i]->name, name) == 0)
            return true;
    }

    return false;
}

void print_operation_vector(operation_vector_t *ov) {
    for (int i = 0; i < ov->size; i++) {
        printf("%s ", ov->operations[i]->name);
    }

    printf("\n");
}

/**
 * Frees an operation vector.
 * @param ov The operation vector.
 */
void operation_vector_free(operation_vector_t *ov) {
    if (ov->operations == NULL)
        print_error(__FILENAME__, __LINE__, __func__, "Invalid pointer");

    free(ov->operations);
    free(ov);
}


/**
 * -----------------------------------------------------------------------------
 * COMMAND MODULE [COMMAND SYSTEM]
 * -----------------------------------------------------------------------------
 */

/**
 * Command system type.
 */

command_system_t *command_system_init(char *filename);

void command_system_init_base(command_system_t *cs);

void command_system_validate(command_system_t *cs);

void command_system_init_vectors(command_system_t *cs);

void command_system_exec(command_system_t *cs);

void command_system_free(command_system_t *cs);

/**
 * Initializes a command system.
 * @param filename The file name.
 * @return The initialized command system.
 */
command_system_t *command_system_init(char *filename) {
    command_system_t *cs = (command_system_t *) malloc(
            sizeof(command_system_t));

    /**
     * Initialize the command vector from file.
     */

    if (cs == NULL)
        print_error(__FILENAME__, __LINE__, __func__, "Malloc failed");

    cs->filename = filename;
    cs->cv = parse_file(filename);

    command_system_init_base(cs);
    command_system_validate(cs);
    command_system_init_vectors(cs);

    /**
     * Initialize the operation map.
     * @todo Implement this.
     */



    return cs;
}

void command_system_init_base(command_system_t *cs) {
    /**
     * Initialize the operation vector.
     */

    cs->operation_vector = operation_vector_init(1);

    operation_vector_add(cs->operation_vector, operation_init("empty", S));
    operation_vector_add(cs->operation_vector, operation_init("card", S));
    operation_vector_add(cs->operation_vector,
                         operation_init("complement", S));
    operation_vector_add(cs->operation_vector, operation_init("union", S));
    operation_vector_add(cs->operation_vector, operation_init("intersect", S));
    operation_vector_add(cs->operation_vector, operation_init("minus", S));
    operation_vector_add(cs->operation_vector, operation_init("subseteq", S));
    operation_vector_add(cs->operation_vector, operation_init("subset", S));
    operation_vector_add(cs->operation_vector, operation_init("equals", S));
    operation_vector_add(cs->operation_vector, operation_init("reflexive", R));
    operation_vector_add(cs->operation_vector, operation_init("symmetric", R));
    operation_vector_add(cs->operation_vector,
                         operation_init("antisymmetric", R));
    operation_vector_add(cs->operation_vector,
                         operation_init("transitive", R));
    operation_vector_add(cs->operation_vector, operation_init("function", R));
    operation_vector_add(cs->operation_vector, operation_init("domain", R));
    operation_vector_add(cs->operation_vector, operation_init("codomain", R));
    operation_vector_add(cs->operation_vector, operation_init("injective", R));
    operation_vector_add(cs->operation_vector,
                         operation_init("surjective", R));
    operation_vector_add(cs->operation_vector, operation_init("bijective", R));
}

void command_system_validate(command_system_t *cs) {
    if (validate_command_vector(cs->cv, cs->operation_vector) == false)
        print_error(__FILENAME__, __LINE__, __func__, "Invalid input");
}

void command_system_init_vectors(command_system_t *cs) {
    /**
     * Initialize the universe set.
     */
    cs->universe = set_init(1);

    command_t *universe_command = find_command_by_type(cs->cv, U);

    for (int i = 0; i < universe_command->args.size; i++) {
        set_add(cs->universe, universe_command->args.elements[i]);
    }

    /**
     * Initialize the set vector.
     */
    cs->set_vector = set_vector_init(1);

    for (int i = 0; i < cs->cv->size; i++) {
        if (cs->cv->commands[i].type == S) {
            set_t *set = set_init_indexed(i + 1,
                                          cs->cv->commands[i].args.size);

            for (int j = 0; j < cs->cv->commands[i].args.size; j++) {
                set_add(set, cs->cv->commands[i].args.elements[j]);
            }

            set_vector_add(cs->set_vector, set);
        }
    }
}

/**
 * Starts the command system.
 * @param cs The command system.
 */
void command_system_exec(command_system_t *cs) {
    for (int i = 0; i < cs->cv->size; i++) {
        command_t *command = &cs->cv->commands[i];
        if (command->type != C) continue;

        char *operation_name = command->args.elements[0];

        if (strcmp(operation_name, "union") == 0) {
            int first_index = atoi(command->args.elements[1]);
            int second_index = atoi(command->args.elements[2]);

            set_t *s = set_union(
                    2,
                    set_vector_find(cs->set_vector, first_index),
                    set_vector_find(cs->set_vector, second_index));
            command_vector_replace(cs->cv, *set_to_command(s), i);
        } else if (strcmp(operation_name, "intersect") == 0) {
            int first_index = atoi(command->args.elements[1]);
            int second_index = atoi(command->args.elements[2]);

            set_t *s = set_intersection(
                    2,
                    set_vector_find(cs->set_vector, first_index),
                    set_vector_find(cs->set_vector, second_index));
            command_vector_replace(cs->cv, *set_to_command(s), i);
        } else if (strcmp(operation_name, "empty") == 0) {
            int index = atoi(command->args.elements[1]);

            bool is_empty = set_is_empty(1, set_vector_find(cs->set_vector,
                                                            index));

            command_vector_replace(cs->cv, bool_to_command(is_empty), i);
        } else if (strcmp(operation_name, "minus") == 0) {
            int first_index = atoi(command->args.elements[1]);
            int second_index = atoi(command->args.elements[2]);

            set_t *s = set_diff(
                    2,
                    set_vector_find(cs->set_vector, first_index),
                    set_vector_find(cs->set_vector, second_index));

            command_vector_replace(cs->cv, *set_to_command(s), i);
        }
    }
}

void command_system_free(command_system_t *cs) {
    if (cs == NULL)
        print_error(__FILENAME__, __LINE__, __func__, "Invalid pointer");

    command_vector_free(cs->cv);
    free(cs);
}

/**
 * Definition for relations
 */

/**
 * Prototypes of functions
 */
void rel_table(int **table, relations *rel_arr, set_t *univerzum);

bool reflexive(relations *rel_arr, set_t *univerzum);

bool symmetric(relations *rel_arr, set_t *univerzum);

bool antisymmetric(relations *rel_arr, set_t *univerzum);

bool transitive(relations *rel_arr, set_t *univerzum);

bool function(relations *rel_arr, set_t *univerzum);


/**
 * Main function.
 * @param argc The number of arguments.
 * @param argv The arguments.
 * @return 0 if the program ran successfully, 1 otherwise.
 */
int main(int argc, char *argv[]) {
    if (argc != 2)
        print_error(__FILENAME__, __LINE__, __func__,
                    "Invalid number of arguments");

    command_system_t *cs = command_system_init(argv[1]);

    command_system_exec(cs);

    command_vector_print(cs->cv);

    command_system_free(cs);

//    FILE *file = fopen(argv[1], "r");
//    if (file == NULL) {
//        fprintf(stderr, "Error during opening the file!\n");
//        return 1;
//    }
//    char row[101];
//    char *istr;
//    univerzum *univerzum;
//    univerzum = set_init(1);
//    set_t **sets = NULL;
//    int set_amount = 0;
//    while (fgets(row, 101, file)) {
//        istr = strtok(row, " \n");
//        if (strcmp(istr, "U") == 0) {
//            istr = strtok(NULL, " \n");
//            while (istr != NULL) {
//                set_add(univerzum, istr);
//                istr = strtok(NULL, " \n");
//            }
//        } else if (strcmp(istr, "S") == 0) {
//            set_t *s;
//            s = set_init(1);
//            istr = strtok(NULL, " \n");
//            while (istr != NULL) {
//                set_add(s, istr);
//                istr = strtok(NULL, " \n");
//            }
//        }
//    }
//
//    for (int i = 0; i < set_amount; i++) {
//        for (int j = 0; j < sets[i]->size; j++) {
//            printf("%s ", sets[i]->elements[j]);
//        }
//        printf("\n");
//    }
//
//    fclose(file);
    return 0;
}


/**
 * function for file opening
 */


/**
 * table of 0 and 1 for relations
 */
void rel_table(int **table, relations *rel_arr, set_t *univerzum) {
    for (int i = 0; i < univerzum->size; i++) {
        for (int j = 0; j < univerzum->size; j++) {
            table[i][j] = 0;
        }
    }
    for (int i = 0; i < rel_arr->count_pairs; i++) {
        for (int j = 0; j < univerzum->size; j++) {
            if (strcmp(rel_arr->pairs[i][0], univerzum->elements[j]) == 0) {
                for (int k = 0; k < univerzum->size; k++) {
                    if (strcmp(rel_arr->pairs[i][1],
                               univerzum->elements[k]) ==
                        0) {
                        table[j][k] = 1;
                    }
                }
            }
        }
    }
    for (int i = 0; i < univerzum->size; i++) {
        for (int j = 0; j < univerzum->size; j++) {
            printf("%d ", table[i][j]);
        }
        printf("\n");
    }
}

/**
 * Checks if the relation is reflexive.
 * @param rel_arr The array of relation pairs.
 * @param univerzum The univerzum.
 * @return true if the relation is reflexive, false otherwise.
 */
bool reflexive(relations *rel_arr, set_t *univerzum) {
    int table[univerzum->size][univerzum->size];
    rel_table(table, rel_arr, univerzum);
    for (int i = 0; i < univerzum->size; i++) {
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
bool symmetric(relations *rel_arr, set_t *univerzum) {
    int table[univerzum->size][univerzum->size];
    rel_table(table, rel_arr, univerzum);
    for (int i = 0; i < univerzum->size; i++) {
        for (int j = 0; j < univerzum->size; j++) {
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
bool antisymmetric(relations *rel_arr, set_t *univerzum) {
    int table[univerzum->size][univerzum->size];
    rel_table(table, rel_arr, univerzum);
    for (int i = 0; i < univerzum->size; i++) {
        for (int j = 0; j < univerzum->size; j++) {
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
bool transitive(relations *rel_arr, set_t *univerzum) {
    int table[univerzum->size][univerzum->size];
    rel_table(table, rel_arr, univerzum);
    for (int i = 0; i < univerzum->size; i++) {
        for (int j = 0; j < univerzum->size; j++) {
            for (int k = 0; k < univerzum->size; k++) {
                if (table[i][j] == 1 && table[j][k] == 1 &&
                    table[i][k] == 0) {
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
bool function(relations *rel_arr, set_t *univerzum) {
    int table[univerzum->size][univerzum->size];
    rel_table(table, rel_arr, univerzum);
    for (int i = 0; i < univerzum->size; i++) {
        int pocet_relaci = 0;
        for (int j = 0; j < univerzum->size; j++) {
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
    set_t univerzum;
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