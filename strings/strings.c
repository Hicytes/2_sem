#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DEFINITIONS 100

// strcmp
int my_strcmp(const char *s1, const char *s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

// Структура для хранения определений макросов с указателями
typedef struct {
    char *name;
    char *value;
    int defined;
} MacroDefinition;

MacroDefinition macros[MAX_DEFINITIONS];
int macro_count = 0;

//является ли символ разделителем
int is_delimiter(char c, const char* delimiters) {
    while (*delimiters) {
        if (c == *delimiters) {
            return 1;
        }
        delimiters++;
    }
    return 0;
}

// поиск макроса по имени
MacroDefinition* find_macro(const char* name) {
    for (int i = macro_count - 1; i >= 0; i--) {
        if (macros[i].defined && my_strcmp(macros[i].name, name) == 0) {
            return &macros[i];
        }
    }
    return NULL;
}

// Функция для выделения памяти и копирования строки
char* my_strdup(const char *s) {
    size_t len = strlen(s) + 1;
    char *new = malloc(len);
    if (new == NULL) return NULL;
    memcpy(new, s, len);
    return new;
}

// Функция для обработки директив #define и #undef
int process_directive(char* line) {
    if (strncmp(line, "#define ", 8) == 0) {
        char *name_start = line + 8;
        while (*name_start == ' ' || *name_start == '\t') name_start++;
        
        char *value_start = name_start;
        while (*value_start && *value_start != ' ' && *value_start != '\t' && *value_start != '\n') 
            value_start++;
        
        if (*value_start) {
            *value_start = '\0';
            value_start++;
            while (*value_start == ' ' || *value_start == '\t' || *value_start == '\n') 
                value_start++;
            
            if (macro_count < MAX_DEFINITIONS) {
                macros[macro_count].name = my_strdup(name_start);
                macros[macro_count].value = my_strdup(value_start);
                macros[macro_count].defined = 1;
                macro_count++;
                return 1;
            }
        }
    } 
    else if (strncmp(line, "#undef ", 7) == 0) {
        char *name_start = line + 7;
        while (*name_start == ' ' || *name_start == '\t') name_start++;
        
        char *name_end = name_start;
        while (*name_end && *name_end != ' ' && *name_end != '\t' && *name_end != '\n') 
            name_end++;
        *name_end = '\0';
        
        for (int i = 0; i < macro_count; i++) {
            if (my_strcmp(macros[i].name, name_start) == 0) {
                macros[i].defined = 0;
                return 1;
            }
        }
    }
    return 0;
}

// Функция для обработки строки с макросами
void process_line(char* line, const char* delimiters, FILE* output) {
    char *word_start = line;
    char *current = line;
    
    while (*current) {
        if (is_delimiter(*current, delimiters)) {
            if (current > word_start) {
                char saved_char = *current;
                *current = '\0';
                
                MacroDefinition* macro = find_macro(word_start);
                if (macro) {
                    fputs(macro->value, output);
                } else {
                    fputs(word_start, output);
                }
                
                *current = saved_char;
                word_start = current + 1;
            }
            fputc(*current, output);
        }
        current++;
    }
    
    if (current > word_start) {
        MacroDefinition* macro = find_macro(word_start);
        if (macro) {
            fputs(macro->value, output);
        } else {
            fputs(word_start, output);
        }
    }
}

void free_macros() {
    for (int i = 0; i < macro_count; i++) {
        free(macros[i].name);
        free(macros[i].value);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: %s input_file output_file\n", argv[0]);
        return 1;
    }
    
    const char* delimiters = " .,;:!?()[]{}<>\"'\\/|@#$%^&*-+=~`\t\n";
    
    FILE* input = fopen(argv[1], "r");
    if (!input) {
        perror("Error opening input file");
        return 1;
    }
    
    FILE* output = fopen(argv[2], "w");
    if (!output) {
        perror("Error opening output file");
        fclose(input);
        return 1;
    }
    
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    
    while ((read = getline(&line, &len, input)) != -1) {
        if (line[0] == '#') {
            if (process_directive(line)) {
                continue;
            }
        }
        
        process_line(line, delimiters, output);
    }
    
    free(line);
    free_macros();
    fclose(input);
    fclose(output);
    
    printf("File processed successfully. Result saved to %s\n", argv[2]);
    return 0;
}
