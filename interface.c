/* Лукьянова Алина, бТИИ-251 */
/* Этот файл содержит все функции, отвечающие за взаимодействие с пользователем,
а именно вывод информации на экран и получение ввода от пользователя. */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h> 
#include "social_network.h"


int Menu() {
    printf("\n     ===================== УПРАВЛЕНИЕ БАЗОЙ ДАННЫХ ====================");
    printf("\n            ================== СОЦИАЛЬНЫЕ СЕТИ ==================");
    printf("\n\n1. Просмотреть все записи");
    printf("\n2. Добавить новую запись");
    printf("\n3. Перезаписать существующую запись");
    printf("\n4. Поиск записи по городу");
    printf("\n5. Поиск записи по возрасту и интересам");
    printf("\n6. Отсортировать данные по следующему приоритету:");
    printf("\n  1) Дата регистрации (по убыванию)");
    printf("\n  2) Количество друзей");
    printf("\n  3) Статус активности");
    printf("\n7. Сохранить данные в файл");
    printf("\n8. Загрузить данные из файла");
    printf("\n9. Заполнить базу тестовыми значениями");
    printf("\n0. Выход\n\n");

    int number;
    printf("Выбирите функцию (0-7): ");
    scanf("%d", &number);
    while (getchar() != '\n');

    return number;
}





void show_Note(Social_Network* NOTES, int i) {

    printf("\n--- Запись %d ---\n", i + 1);
    printf("\n   --- ИНФОРМАЦИЯ О ПОЛЬЗОВАТЕЛЕ ---\n");
    printf("Имя: %s\n", NOTES[i].name);
    printf("Возраст: %.1f\n", NOTES[i].age);
    printf("Интересы: ");
    int has_interests = 0;
    for (int j = 0; j < 3; j++) {
        if (NOTES[i].interests[j] >= 0 && NOTES[i].interests[j] <= 5) {
            if (has_interests != 0) printf(", ");
            switch (NOTES[i].interests[j]) {
            case SPORT: printf("Спорт"); break;
            case ANIMALS: printf("Животные"); break;
            case FILMS: printf("Фильмы"); break;
            case ART: printf("Искусство"); break;
            case CELEBRITIES: printf("Знаменитости"); break;
            case COOKING: printf("Кулинария"); break;
            default: printf("Было записано неизвестное значение");
            }
            has_interests = 1;
        }
    }
    if (has_interests == 0) printf("Интересы отсутствуют");
    printf("\n");

    printf("Дата регистрации: %02d.%02d.%d\n", NOTES[i].date.day, NOTES[i].date.month, NOTES[i].date.year);
    printf("Количество друзей: %d\n", NOTES[i].friends);
    printf("Город: %s\n", NOTES[i].city);
    printf("Статус: %s\n", NOTES[i].status == ONLINE ? "Онлайн" : "Оффлайн");
    printf("====================================\n");
}





char* add_NewNote(Social_Network* NOTES, int n_count, char* mistake) {

    int mis = 0;

    printf("\n                     --- ДОБАВЛЕНИЕ НОВОЙ ЗАПИСИ ---\n\n");

    printf("~~ Введите имя пользователя: ");
    fgets(NOTES[n_count].name, sizeof(NOTES[n_count].name), stdin);
    int len = strlen(NOTES[n_count].name);
    if (len > 0 && NOTES[n_count].name[len - 1] == '\n') {
        NOTES[n_count].name[len - 1] = '\0';
    }

    printf("\n~~ Введите возраст: ");
    if (scanf("%f", &NOTES[n_count].age) != 1 || NOTES[n_count].age < 0) {
        strcpy(mistake, "\nВНИМАЕНИЕ: Допущена ошибка в поле 'Возраст'!\n");
        mis = 1;
    }
    while (getchar() != '\n');


    printf("\n~~ Выберите до трёх интересов:\n");
    printf("0 - СПОРТ\n1 - ЖИВОТНЫЕ\n2 - ФИЛЬМЫ\n3 - ИСКУССТВО\n");
    printf("4 - ЗНАМЕНИТОСТИ\n5 - КУЛИНАРИЯ\n6 - ЗАВЕРШИТЬ ВВОД\n\n");

    for (int i = 0; i < 3; i++) NOTES[n_count].interests[i] = -1;
    int interest_count = 0;
    for (int i = 0; i < 3; i++) {
        printf("\nВведите номер %d-го интереса (или 6 для завершения): ", i + 1);
        int interest;
        scanf("%d", &interest);
        if (interest == 6) break;

        int already_selected = 0;
        for (int j = 0; j < interest_count; j++) {
            if (NOTES[n_count].interests[j] == interest) {
                already_selected = 1;
                break;
            }
        }
        if (already_selected != 1) {
            NOTES[n_count].interests[interest_count] = (Interests)interest;
            interest_count++;
            printf("Добавлен интерес: ");
            switch (interest) {
            case SPORT: printf("СПОРТ\n"); break;
            case ANIMALS: printf("ЖИВОТНЫЕ\n"); break;
            case FILMS: printf("ФИЛЬМЫ\n"); break;
            case ART: printf("ИСКУССТВО\n"); break;
            case CELEBRITIES: printf("ЗНАМЕНИТОСТИ\n"); break;
            case COOKING: printf("КУЛИНАРИЯ\n"); break;
            default: printf("Неизвестный выбор\n");
            }
        }
        else {
            printf("Этот интерес уже выбран!\n");
            i--;
        }
    }
    while (getchar() != '\n');


    printf("\n~~ Дата регистрации ~~\n");
    printf("\nВведите день: ");
    if (scanf("%d", &NOTES[n_count].date.day) != 1 || 1 > NOTES[n_count].date.day || NOTES[n_count].date.day > 31)
        if (mis == 1) strcat(mistake, "ВНИМАНИЕ: Введен неккоректный день регистрации!\n");
        else {
            strcpy(mistake, "\nВНИМАНИЕ: Введен неккоректный день регистрации!\n");
            mis = 1;
        }
    while (getchar() != '\n');

    printf("\nВведите месяц: ");
    if (scanf("%d", &NOTES[n_count].date.month) != 1 || 1 > NOTES[n_count].date.month || NOTES[n_count].date.month > 12)
        if (mis == 1) strcat(mistake, "ВНИМАНИЕ: Введен неккоректный месяц регистрации!\n");
        else {
            strcpy(mistake, "\nВНИМАНИЕ: Введен неккоректный месяц регистрации!\n");
            mis = 1;
        }
    while (getchar() != '\n');

    printf("\nВведите год: ");
    if (scanf("%d", &NOTES[n_count].date.year) != 1)
        if (mis == 1) strcat(mistake, "ВНИМАНИЕ: Введен неккоректный год регистрации!\n");
        else {
            strcpy(mistake, "\nВНИМАНИЕ: Введен неккоректный год регистрации\n");
            mis = 1;
        }
    while (getchar() != '\n');


    printf("\n~~ Введите количество друзей: ");
    if (scanf("%d", &NOTES[n_count].friends) != 1 || NOTES[n_count].friends < 0)
        if (mis == 1) strcat(mistake, "ВНИМАНИЕ: Допущена ошибка в поле 'Количество друзей'!\n");
        else {
            strcpy(mistake, "\nВНИМАНИЕ: Допущена ошибка в поле 'Количество друзей'!\n");
            mis = 1;
        }
    while (getchar() != '\n');


    printf("\n~~ Введите город: ");
    fgets(NOTES[n_count].city, sizeof(NOTES[n_count].city), stdin);
    len = strlen(NOTES[n_count].city);
    if (len > 0 && NOTES[n_count].city[len - 1] == '\n') {
        NOTES[n_count].city[len - 1] = '\0';
    }

    printf("\n~~ Введите статус активности: ~~\n");
    printf("0 - ОНЛАЙН\n");
    printf("1 - ОФФЛАЙН\n");
    printf("Введите номер статуса: ");

    if (scanf("%d", &NOTES[n_count].status) != 1 || NOTES[n_count].status != ONLINE && NOTES[n_count].status != OFFLINE)
        if (mis == 1) strcat(mistake, "ВНИМАНИЕ: Допущена ошибка в поле 'Статус активности'!\n");
        else {
            strcpy(mistake, "\nВНИМАНИЕ: Допущена ошибка в поле 'Статус активности'!\n");
            mis = 1;
        }
    while (getchar() != '\n');

    return mistake;
}


void show_search_results(Social_Network* NOTES, int* found_count) {

    printf("Всего найдено записей: %d\n", *found_count);
    for (int number = 0; number < *found_count; number++) {
        printf("\n--- Найдена запись %d ---\n", number + 1);
        printf("Имя: %s\n", NOTES[number].name);
        printf("Возраст: %.1f\n", NOTES[number].age);
        printf("Количество друзей: %d\n", NOTES[number].friends);
        printf("Город: %s\n", NOTES[number].city);
        printf("Статус: %s\n", NOTES[number].status == ONLINE ? "Онлайн" : "Оффлайн");
        printf("Дата регистрации: %02d.%02d.%d\n",
            NOTES[number].date.day, NOTES[number].date.month, NOTES[number].date.year);

        printf("Интересы: ");
        int has_interests = 0;
        for (int j = 0; j < 3; j++) {
            if (NOTES[number].interests[j] >= 0) {
                if (has_interests != 0) printf(", ");
                switch (NOTES[number].interests[j]) {
                case SPORT: printf("Спорт"); break;
                case ANIMALS: printf("Животные"); break;
                case FILMS: printf("Фильмы"); break;
                case ART: printf("Искусство"); break;
                case CELEBRITIES: printf("Знаменитости"); break;
                case COOKING: printf("Кулинария"); break;
                }
                has_interests = 1;
            }
        }
        if (has_interests == 0) printf("Интересы отсутствуют");
        printf("\n");
    }
}
