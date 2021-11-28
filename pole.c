#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

typedef struct{
    int size;
    int *array;
} vector_t;

vector_t *vector_ctor(){
    vector_t *v;
    v = malloc (sizeof(vector_t));
    if (v == NULL){
        fprintf(stderr, "Failed to malloc vector_t\n");
    }
    v->size = 0;
    v->array = NULL;
    return v;
}

void vector_dtor(vector_t *vector){
    if (vector->array != NULL){
        free(vector->array);
    }
    free (vector);
}

int *resize(int *arr, unsigned int new_size){
    int *tmp;
    tmp = realloc(arr, sizeof(int) * new_size);
    if (tmp == NULL){
        return arr;
    } else {
        //free(arr);
    }
    return tmp;
}

int vector_add(vector_t *vec, int value){
    vec->array = resize(vec->array, vec->size + 1);
    vec->array[vec->size++] = value;
    return 0;
}

/*int find_substr(char *str, char *substr){
    int substr_len = strlen(substr);
    int str_len = strlen(str);
    for (int i = 0; i < str_len - substr_len; i++){
        int eq = 1;
        for (int j = 0; substr[j] != '\0'; j++){
            if (str[i+j] != substr[j]){
                eq = 0;
                break;
            }
        }
        if (eq == 1)
            return i;
    }
    return -1;
}

void replace_same_length(char *str, char *substr, char *new_substr){
    int index = find_substr(str, substr);
    if (index == -1){
        return;
    }
    int substr_len = strlen(substr);
    //strcpy(&str[index], new_substr);
    for (int i = index; i < index + substr_len; i++){
        str[i] = new_substr[i];
    }
}

char *replace(char *str, char *substr, char *new_substr){
    int index = find_substr(str, substr);
    if (index == -1){
        return;
    }
    int new_substr_len = strlen(new_substr);
    int str_len = strlen(str);
    int substr_len = strlen(substr);
    char *new_str;
    if (new_substr_len > substr_len){
        new_str = realloc(str, str_len + new_substr_len - substr_len);
        strncat(new_str, str, index - 1);
        strncat(new_str, new_substr, new_substr_len);
        strncat(new_str, str +index + str_len, str_len - index );
        return new_str;
    }
}*/

int main(){
    vector_t *v;
    v = vector_ctor();
    vector_add(v, 10);
    vector_add(v, 11);
    vector_add(v, 12);

    printf("3rd: %d\n", v->array[2]);
    vector_dtor(v);
    //if (find_substr("ahoj","ho")){
    //    printf("good\n");
    //}
    return 0;
}