/* Лукьянова Алина, бТИИ-251 */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <search.h> 
#include "social_network.h"


main() {
    system("chcp 1251");
    printf("\n----------------------------------------------------\n");
    printf("    ПРОГРАММА 'БАЗА ДАННЫХ СОЦИАЛЬНОЙ СЕТИ' \n");
    printf("    Разработала студентка группы бТИИ-251 \n");
    printf("    Лукьянова Алина");
    printf("\n----------------------------------------------------\n\n");

    char fname[20] = "Social_Network.txt";
    int size, loaded_count, notes_count = 0, found_count = 0;
    int* found_count_ptr = &found_count;
    int* notes_count_ptr;
    notes_count_ptr = &notes_count;
    printf("Введите размер базы данных: ");
    scanf("%d", &size);

    Social_Network* notes = (Social_Network*)(malloc(size * sizeof(Social_Network)));
    if (notes == NULL) {
        printf("Ошибка выделения памяти!");
        return -1;
    }

    while (1) {

        int end = 1;

        switch (Menu()) {
        case 1:
            if (notes_count == 0) {
                printf("\nНет записей для просмотра!\n");
            }
            else {
                printf("\n                             === ВСЕ ЗАПИСИ ===\n");
                for (int i = 0; i < notes_count; i++) {
                    show_Note(notes, i);
                }
            }
            break;
        case 2:
            if (notes_count < size) {
                char mistake[300] = "";
                char* result = add_NewNote(notes, notes_count, mistake);
                if (strlen(mistake) > 0) {
                    printf("%s", mistake);
                    printf("\nЗапись добавлена с ошибками! Настоятельно рекомендуется отредактировать!\n");
                }
                else printf("\nЗапись успешно добавлена!\n");
                notes_count++;
                printf("Всего записей: %d\n", notes_count);
            }
            else printf("\n Достигнут максимальный лимит записей (%d)!\n", size);
            break;
        case 3:
            printf("Введите номер записи, которую хотите перезаписать (1-%d): ", notes_count);
            int ind;
            if (scanf("%d", &ind) != 1 || ind > size) {
                printf("\n Такой записи не сущесвтует!\n");
                while (getchar() != '\n');
            }
            else {
                while (getchar() != '\n');
                char mistake[300] = "\nЗапись успешно перезаписана!\n";
                char* result = add_NewNote(notes, ind - 1, mistake);
                printf("%s", result);
            }
            break;
        case 4:
            if (notes_count == 0) {
                printf("\nНет записей для поиска!\n");
            }
            else {
                char city[30];
                printf("\nВведите город для поиска: ");
                fgets(city, 30, stdin);
                int len = strlen(city);
                if (len > 0 && city[len - 1] == '\n') {
                    city[len - 1] = '\0';
                }
                if (single_search(notes, notes_count, city, found_count_ptr) == -1)
                    printf("Ошибка выделения памяти для массива найденых записей!");
                else {
                    printf("\n=== РЕЗУЛЬТАТЫ ПОИСКА ПО ГОРОДУ '%s' ===\n", city);
                    printf("Всего записей в базе: %d\n\n", notes_count);
                    Social_Network* found_notes = single_search(notes, notes_count, city, found_count_ptr);
                    if (found_notes == NULL) printf("Записей из города '%s' не найдено.\n", city);

                    if (found_notes != NULL) {
                        show_search_results(found_notes, found_count_ptr);
                        free(found_notes);
                    }
                }
                *found_count_ptr = 0;
            }
            break;
        case 5:
            if (notes_count == 0) printf("\nНет записей для поиска!\n");
            else {
                float age;
                int interest;

                while (1) {
                    printf("\nВведите возраст: ");
                    if (scanf("%f", &age) == 1 && age >= 0) {
                        while (getchar() != '\n');
                        break;
                    }
                    else {
                        printf("Ошибка ввода! Пожалуйста, введите число.\n");
                        while (getchar() != '\n');
                    }
                }

                printf("\n~~ Список интересов:\n");
                printf("0 - СПОРТ\n1 - ЖИВОТНЫЕ\n2 - ФИЛЬМЫ\n3 - ИСКУССТВО\n");
                printf("4 - ЗНАМЕНИТОСТИ\n5 - КУЛИНАРИЯ\n\n");

                while (1) {
                    printf("\nВведите номер интереса: ");
                    if (scanf("%d", &interest) == 1 && interest >= 0 && interest <= 5) {
                        while (getchar() != '\n');
                        break;
                    }
                    else {
                        printf("Ошибка ввода! Пожалуйста, введите число от 0 до 5.\n");
                        while (getchar() != '\n');
                    }
                }

                printf("\n=== РЕЗУЛЬТАТЫ ПОИСКА ПО ВОЗРАСТУ %d И ИНТЕРЕСУ ===\n", age);
                printf("Всего записей в базе: %d\n\n", notes_count);
                if (comb_search(notes, notes_count, age, interest, found_count_ptr) == -1)
                    printf("Ошибка выделения памяти для массива найденных записей!");
                Social_Network* found_notes = comb_search(notes, notes_count, age, interest, found_count_ptr);
                if (found_count == NULL) printf("Пользователей с возрастом %d и указанным интересом не найдено.\n", age);


                if (found_notes != NULL) {
                    show_search_results(found_notes, found_count_ptr);
                    free(found_notes);
                }
                *found_count_ptr = 0;
            }
            break;
        case 6:
            if (notes_count == 0) printf("\nНет записей для сортировки!\n");
            else {
                qsort(notes, notes_count, sizeof(Social_Network), compare);
                printf("Записи успешно отосртированы!");
            }
            break;
        case 7:
            if (notes_count == 0) printf("\nНет записей для сохранения в файл!\n");
            else if (saveToFile(notes, notes_count, fname) == -1)
                printf("Ошибка открытия файла для записи\n");
            else printf("Данные успешно сохранены в файл '%s'\n", fname);
            break;
        case 8:
            loaded_count = loadFromFileCompactSimple(notes, notes_count_ptr, size, fname);
            switch (loaded_count) {
            case -1: printf("Ошибка открытия файла '%s' для чтения!\n", fname);
            case -2: printf("Ошибка чтения количества записей!\n");
            case -3: printf("Недостаточно места в базе данных!\n");
            default:
                notes_count += loaded_count;
                printf("Загружено %d записей\n", loaded_count);
            }
            break;
        case 9:
            test_fill(notes, size);
            notes_count = size;
            printf("\nБаза данных успешна заполнена тестовыми записями!\n");
            break;
        case 0:
            printf("\nДо свидания!\n");
            end = 0;
            break;
        default:
            printf("\nНеверный ввод!\n");
            break;
        };

        if (end == 0) break;
        printf("\nПродолжить? (1 - да, 0 - нет): ");
        scanf("%d", &end);
        while (getchar() != '\n');

        if (end != 0 && end != 1) {
            do {
                printf("Получено неисзвестное значение. Пожалуйста, повторите ввод: ");
                scanf("%d", &end);
                while (getchar() != '\n');
            } while (end != 0 && end != 1);
            if (end == 0) {
                printf("До свидания!");
                free(notes);
                break;
            }
        }
        else if (end == 0) {
            printf("До свидания!");
            break;
        }
    }
}