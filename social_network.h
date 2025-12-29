/* Лукьянова Алина, бТИИ-251 */
/* Содержит определения структур данных и прототипы функций
для работы с базой данных пользователей социальной сети. */

#ifndef SOCIALNETWORK_H
#define SOCIALNETWORK_H

/* Перечисление возможных интересов пользователей */
typedef enum {
    SPORT,
    ANIMALS,
    FILMS,
    ART,
    CELEBRITIES,
    COOKING
} Interests;

/* Структура для хранения даты регистрации пользователя */
typedef struct {
    int day;
    int month;
    int year;
} Date_of_Regist;

/* Перечисление статусов активности пользователя */
typedef enum {
    ONLINE,
    OFFLINE
} Activity_Status;

/* Структура для хранения данных пользователя социальной сети */
typedef struct {
    char name[50];
    float age;
    Interests interests[3];
    Date_of_Regist date;
    int friends;
    char city[30];
    Activity_Status status;
} Social_Network;

/**
 * Отображение главного меню программы и получение выбора пользователя
 * @return выбранный пункт меню (0-9)
 */
int Menu();

/**
 * Отображение информации о конкретной записи пользователя
 * @param NOTES указатель на массив записей
 * @param i индекс отображаемой записи
 */
void show_Note(Social_Network* NOTES, int i);

/**
 * Добавление новой записи пользователя через диалог с пользователем
 * @param NOTES указатель на массив записей
 * @param n_count индекс для новой записи
 * @param mistake строка для сообщений об ошибках
 * @return указатель на строку с ошибками (или пустую строку при успехе)
 */
char* add_NewNote(Social_Network* NOTES, int n_count, char* mistake);

/**
 * Поиск пользователей по городу проживания
 * @param NOTES указатель на массив всех записей
 * @param n_count общее количество записей
 * @param city город для поиска
 * @param found_count указатель на переменную для хранения количества найденных записей
 * @return указатель на динамически выделенный массив найденных записей
 */
Social_Network* single_search(Social_Network* NOTES, int n_count, char* city, int* found_count);

/**
 * Комбинированный поиск пользователей по возрасту и интересу
 * @param NOTES указатель на массив всех записей
 * @param n_count общее количество записей
 * @param age возраст для поиска
 * @param interest интерес для поиска
 * @param found_count указатель на переменную для хранения количества найденных записей
 * @return указатель на динамически выделенный массив найденных записей
 */
Social_Network* comb_search(Social_Network* NOTES, int n_count, int age, int interest, int* found_count);

/**
 * Сохранение всех записей в текстовый файл
 * @param NOTES указатель на массив записей
 * @param n_count количество записей для сохранения
 * @param fname имя файла для сохранения
 * @return 0 при успешном сохранении, -1 при ошибке
 */
int saveToFile(Social_Network* NOTES, int n_count, char* fname);

/**
 * Загрузка записей из текстового файла
 * @param NOTES указатель на массив для загрузки записей
 * @param current_count текущее количество записей в массиве
 * @param max_size максимальный размер массива
 * @param fname имя файла для загрузки
 * @return количество загруженных записей или код ошибки (-1, -2, -3)
 */
int loadFromFileCompactSimple(Social_Network* NOTES, int* current_count, int max_size, char* fname);

/**
 * Функция сравнения для сортировки записей qsort()
 * Приоритет сортировки: дата регистрации (по убыванию) -> количество друзей -> статус активности
 * @param a указатель на первую запись
 * @param b указатель на вторую запись
 * @return отрицательное число если a < b, положительное если a > b, 0 если равны
 */
int compare(const void* a, const void* b);

/**
 * Заполнение массива тестовыми данными
 * @param NOTES указатель на массив для заполнения
 * @param test_count количество тестовых записей для создания
 */
void test_fill(Social_Network* NOTES, int test_count);


#endif