/* Лукьянова Алина, бТИИ-251 */
/* Этот файл содержит функции для обработки данных,
а именно поиск, сортировка, работа с файлами и другие алгоритмы. */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <time.h> 
#include "social_network.h"


int compare(const void* a, const void* b) {

    const Social_Network* note_a = (const Social_Network*)a;
    const Social_Network* note_b = (const Social_Network*)b;

    if (note_a->date.year > note_b->date.year) return -1;
    else if (note_a->date.year < note_b->date.year) return 1;
    else {

        if (note_a->date.month > note_b->date.month) return -1;
        else if (note_a->date.month < note_b->date.month) return 1;
        else {

            if (note_a->date.day > note_b->date.day) return -1;
            else if (note_a->date.day < note_b->date.day) return 1;
            else {

                if (note_a->friends < note_b->friends) return -1;
                else if (note_a->friends > note_b->friends) return 1;
                else {
                    if (note_a->status < note_b->status) return -1;
                    else if (note_a->status > note_b->status) return 1;
                }
            }
        }
    }

    return 0;
}



int saveToFile(Social_Network* NOTES, int n_count, char* fname) {

    FILE* out;

    if ((out = fopen(fname, "wt")) == NULL) {
        return -1;
    }

    fprintf(out, "%d\n", n_count);

    for (int i = 0; i < n_count; i++) {
        char interests_str[6] = "";
        for (int j = 0; j < 3; j++) {
            if (NOTES[i].interests[j] >= 0 && NOTES[i].interests[j] <= 5) {
                if (strlen(interests_str) > 0) strcat(interests_str, ",");
                switch (NOTES[i].interests[j]) {
                case SPORT: strcat(interests_str, "0"); break;
                case ANIMALS: strcat(interests_str, "1"); break;
                case FILMS: strcat(interests_str, "2"); break;
                case ART: strcat(interests_str, "3"); break;
                case CELEBRITIES: strcat(interests_str, "4"); break;
                case COOKING: strcat(interests_str, "5"); break;
                }
            }
        }
        if (strlen(interests_str) == 0) strcpy(interests_str, "NONE");

        fprintf(out, "%s;%.1f;%s;%d.%d.%d;%d;%s;%d\n",
            NOTES[i].name, NOTES[i].age, interests_str,
            NOTES[i].date.day, NOTES[i].date.month, NOTES[i].date.year,
            NOTES[i].friends, NOTES[i].city,
            NOTES[i].status == ONLINE ? "ONLINE" : "OFFLINE");
    }

    fclose(out);

    return 0;
}



int loadFromFileCompactSimple(Social_Network* NOTES, int* n_count, int max_size, const char* fname) {

    FILE* in;

    if ((in = fopen(fname, "rt")) == NULL) {
        return -1;
    }

    int total_records;
    if (fscanf(in, "%d\n", &total_records) != 1) {
        fclose(in);
        return -2;
    }

    if (*n_count + total_records > max_size) {
        fclose(in);
        return -3;
    }

    int loaded_count = 0;

    for (int i = 0; i < total_records; i++) {
        int idx = *n_count + loaded_count;
        char name[50], interests_str[6], city[30], status_str[10];
        float age;
        int day, month, year, friends;

        if (fscanf(in, "%49[^;];%f;%5[^;];%d.%d.%d;%d;%29[^;];%9s\n\n",
            name, &age, interests_str, &day, &month, &year, &friends, city, status_str) == 9) {

            strcpy(NOTES[idx].name, name);
            NOTES[idx].age = age;

            int interests[3] = { -1, -1, -1 };
            int count = 0;
            char* ptr = interests_str;

            while (sscanf(ptr, "%d", &interests[count]) == 1 && count < 3) {
                count++;
                ptr = strchr(ptr, ',');
                if (ptr == NULL) break;
                ptr++;
            }

            for (int j = 0; j < 3; j++) NOTES[idx].interests[j] = (Interests)interests[j];

            NOTES[idx].date.day = day;
            NOTES[idx].date.month = month;
            NOTES[idx].date.year = year;
            NOTES[idx].friends = friends;
            strcpy(NOTES[idx].city, city);

            if (strcmp(status_str, "ONLINE") == 0 || strcmp(status_str, "0") == 0) {
                NOTES[idx].status = ONLINE;
            }
            else NOTES[idx].status = OFFLINE;

            loaded_count++;
        }
        else {
            printf("Ошибка чтения записи %d\n", i + 1);;
            break;
        }
    }

    fclose(in);

    return loaded_count;
}



Social_Network* single_search(Social_Network* NOTES, int n_count, char* city, int* found_count) {

    for (int i = 0; i < n_count; i++) {
        if (strcmp(NOTES[i].city, city) == 0) *found_count += 1;
    }

    if (*found_count == 0) {
        return NULL;
    }
    else {
        Social_Network* singlfound_n = (Social_Network*)(malloc(*found_count * sizeof(Social_Network)));
        if (singlfound_n == NULL) {
            printf("Ошибка выделения памяти для массива найденых записей!");
            return -1;
        }

        int found_index = 0;
        for (int j = 0; j < n_count; j++) {
            if (strcmp(NOTES[j].city, city) == 0) {
                singlfound_n[found_index] = NOTES[j];
                found_index++;
            }
        }


        return singlfound_n;
    }
}



Social_Network* comb_search(Social_Network* NOTES, int n_count, int age, int interest, int* found_count) {

    for (int i = 0; i < n_count; i++) {
        if ((int)NOTES[i].age == (int)age) {
            for (int k = 0; k < 3; k++) {
                if (NOTES[i].interests[k] == interest) {
                    *found_count += 1;
                    break;
                }
            }
        }
    }

    if (*found_count == 0) {
        return NULL;
    }
    else {
        Social_Network* combfound_n = (Social_Network*)malloc(*found_count * sizeof(Social_Network));
        if (combfound_n == NULL) {
            printf("Ошибка выделения памяти для массива найденых записей!");
            return -1;
        }

        int found_index = 0;
        for (int i = 0; i < n_count; i++) {
            if ((int)NOTES[i].age == age) {
                int interest_found = 0;
                for (int k = 0; k < 3; k++) {
                    if (NOTES[i].interests[k] == interest) {
                        interest_found = 1;
                        break;
                    }
                }
                if (interest_found == 1) {
                    combfound_n[found_index] = NOTES[i];
                    found_index++;
                }
            }
        }

        return combfound_n;
    }
}



int getRandomNumber(int a, int b) {
    return rand() % (a - b + 1) + a;
}

void test_fill(Social_Network* NOTES, int size) {

    srand(time(NULL));

    for (int i = 0; i < size; i++) {

        char* names[6] = { "Алина ", "Галина ", "Максим ", "Тамара ", "Данил ", "Мария " };
        char* sernames[6] = { "Московская", "Кузнецова", "Петров", "Иванова", "Семенова", "Степашкин", };
        char* cities[6] = { "Москва", "Санкт-Петербург", "Воронеж", "Екатеринбург", "Казань", "Ростов-на-Дону", };
        int ind1 = rand() % 6, ind2 = rand() % 6, ind = rand() % 6;

        strcpy(NOTES[i].name, names[ind1]);
        strcat(NOTES[i].name, sernames[ind2]);
        strcpy(NOTES[i].city, cities[ind]);
        NOTES[i].age = getRandomNumber(14, 60);
        NOTES[i].interests[0] = getRandomNumber(0, 5);
        NOTES[i].interests[1] = getRandomNumber(0, 5);
        NOTES[i].interests[2] = getRandomNumber(0, 5);
        NOTES[i].date.day = getRandomNumber(1, 31);
        NOTES[i].date.month = getRandomNumber(1, 12);
        NOTES[i].date.year = getRandomNumber(2000, 2025);
        NOTES[i].friends = getRandomNumber(1, 1000);
    }
}