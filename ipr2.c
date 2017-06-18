/**
 * Программа формирования стека с последующим
 * его преобразованием в двунаправленную очередь.
 * Разработчик - Дубинин А. В. (http://dubinin.net)
 * 27.11.2016
 */

// Подключение файлов из стандартной библиотеки
#include <locale.h>
#include <stdio.h>

// Объявление символических констант
#define DATA_PATTERN     "%-3d"
#define MSG_RESULT_SRC   "Данные из внешнего источника: "
#define MSG_RESULT_STACK "Данные из стека: "
#define MSG_RESULT_QUEUE "Данные из очереди: "
#define MSG_MEMORY_ERR   "Ошибка выделения памяти элементу %s"
#define MSG_APP_EXIT     "Для выхода из программы нажмите любую клавишу"

// Объявление новой структуры и имени типа - stack
typedef struct {
    int data;
    struct stack *next;
} stack;

// Объявление нового имени типа - stackPtr
typedef stack *stackPtr;

// Объявление новой структуры и имени типа - queue
typedef struct {
    int data;
    struct queue *next, *prev;
} queue;

// Объявление нового имени типа - queuePtr
typedef queue *queuePtr;

/*
 * Прототипы функций hr, pushIntoStack, popTop, pushIntoQueue, popFront
 */
void hr();
void pushIntoStack(stackPtr *, int);
int popTop(stackPtr *);
void pushIntoQueue(queuePtr *, queuePtr *, int);
int popFront(queuePtr *);

void main()
{
    setlocale(LC_ALL, ""); // установка локализации
    int i, data;           // объявление переменных типа int

    /*
     * Объявление и инициализация массива данных,
     * а также определение кол-ва элементов.
     */
    int externalSrcData[] = {0,1,1,2,3,5,8,13,21,34,55,89};
    int dataCount = sizeof externalSrcData/sizeof(int);

    // Объявление и инициализация пустого стека
    stackPtr top = NULL;

    /*
     * Вывод на экран элементов массива-источника.
     * Элементы помещаются в стек.
     */
    printf(MSG_RESULT_SRC);
    for (i = 0; i < dataCount; i++) {
        printf(DATA_PATTERN, externalSrcData[i]);
        pushIntoStack(&top, externalSrcData[i]);
    }
    hr();

    // Объявление и инициализация пустой очереди
    queuePtr front = NULL;
    queuePtr rear = front;

    /*
     * Вывод на экран элементов из стека и помещение их
     * в двунаправленную очередь.
     */
    printf(MSG_RESULT_STACK);
    while (top) {
        data = popTop(&top);
        printf(DATA_PATTERN, data);
        pushIntoQueue(&front, &rear, data);
    }
    hr();

    /*
     * Вывод на экран элементов из полученной двунаправленной очереди.
     */
    printf(MSG_RESULT_QUEUE);
    while (front) {
        printf(DATA_PATTERN, popFront(&front));
    }
    hr();

    // Вывод на экран диалога выхода из программы
    printf(MSG_APP_EXIT);
    getchar();
    return;
}

/*
 * Функция вывода на всю ширину окна
 * горизонтальной полосы.
 */
void hr()
{
    int i;
    putchar('\n');
    for (i = 0; i <= 79; i++) {
        putchar('-');
    }
    return;
}

/*
 * Функция помещения данных в стек.
 *
 * top - параметр указатель типа stackPtr,
 * data - параметр типа int.
 */
void pushIntoStack(stackPtr *top, int data)
{
    // Выделение памяти элементу стека
    stackPtr newPtr = (stack *) malloc(sizeof(stack));

    if (newPtr == NULL) {
        printf(MSG_MEMORY_ERR, "стека");
        return;
    }

    newPtr->data = data;
    newPtr->next = *top; // помещение элемента
    *top = newPtr;       // в стек
    return;
}

/*
 * Функция выборки данных из стека.
 *
 * top - параметр указатель типа stackPtr.
 */
int popTop(stackPtr *top)
{
    // рабочему указателю присваивается адрес вершины стека
    stackPtr tmpPtr = *top;
    int topData = (*top)->data; // значение возвращаемого эл-та
    *top = (*top)->next;        // переопределение указателя на вершину стека
    free(tmpPtr);               // освобождение памяти
    return topData;
}

/*
 * Функция помещения данных в очередь.
 *
 * front, rear - параметры указатели типа queuePtr,
 * data - параметр типа int.
 */
void pushIntoQueue(queuePtr *front, queuePtr *rear, int data)
{
    // Выделение памяти элементу очереди
    queuePtr newPtr = (queue *) malloc(sizeof(queue));

    if (newPtr == NULL) {
        printf(MSG_MEMORY_ERR, "очереди");
        return;
    }

    newPtr->data = data;
    newPtr->next = NULL;
    newPtr->prev = NULL;

    /*
     * Если очередь пуста, указателям на начало и конец очереди
     * присваивается значение указателя на новый элемент.
     * Иначе элемент присоединяется к концу очереди и переопределяются
     * указатели на конец очереди и предыдущий элемент.
     */
    if ((*rear) == NULL) {
        *front = newPtr;
        *rear = newPtr;
    } else {
        queuePtr prevPtr = *rear;
        (*rear)->next = newPtr;
        (*rear) = newPtr;
        (*rear)->prev = prevPtr;
    }
    return;
}

/*
 * Функция выборки данных из очереди.
 *
 * front - параметр указатель типа queuePtr.
 */
int popFront(queuePtr *front)
{
    // рабочему указателю присваивается адрес начала очереди
    queuePtr tmpPtr = *front;
    int frontData = (*front)->data; // значение возвращаемого эл-та
    *front = (*front)->next;        // переопределение указателя на начало очереди
    free(tmpPtr);                   // освобождение памяти
    return frontData;
}
