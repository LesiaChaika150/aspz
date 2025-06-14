## ЗАВДАННЯ 1

> **Умова:**
>Напишіть програму для визначення моменту, коли time_t закінчиться. Дослідіть, які зміни >відбуваються в залежності від 32- та 64-бітної архітектури. Дослідіть сегменти виконуваного файлу.

## **Пояснення програми**
Ця програма визначає максимальне значення типу time_t шляхом зсуву найстаршого біта типу на основі його розміру у байтах. Тип time_t використовується для представлення часу у вигляді кількості секунд, що минули з 1 січня 1970 року. Залежно від розрядності системи (sizeof(time_t) дорівнює 4 або 8 байт), програма показує різні результати:
- на 32-бітній архітектурі — дата обмежується 19 січня 2038 року;
- на 64-бітній — значення сягає десятків мільярдів років у майбутнє.

Функція ctime() перетворює числове значення time_t у зрозумілий текстовий формат дати й часу. Якщо значення занадто велике, функція повертає NULL, що свідчить про вихід за межі оброблюваних значень.

Програма також дозволяє візуалізувати наслідки переповнення — коли time_t досягає межі і переходить у від’ємне значення.

### Результат роботи програми (Завдання 1):

![Результат програми](task1/Результат1.png)

## ЗАВДАННЯ 2

> **Умова:**  
> Розгляньте сегменти у виконуваному файлі.  
> 1. Скомпілюйте програму "hello world", запустіть ls -l для виконуваного файлу, щоб отримати його загальний розмір, і запустіть size, щоб отримати розміри сегментів всередині нього.
> 2. Додайте оголошення глобального масиву із 1000 int, перекомпілюйте й повторіть вимірювання. Зверніть увагу на відмінності.
> 3. Тепер додайте початкове значення в оголошення масиву (пам’ятайте, що C не змушує вас вказувати значення для кожного елемента масиву в ініціалізаторі). Це перемістить масив із сегмента BSS у сегмент даних. Повторіть вимірювання. Зверніть увагу на різницю.
> 4. Тепер додайте оголошення великого масиву в локальну функцію. Оголосіть другий великий локальний масив з ініціалізатором. Повторіть вимірювання. Дані розташовуються всередині функцій, залишаючись у виконуваному файлі? Яка різниця, якщо масив ініціалізований чи ні?
> 5. Які зміни відбуваються з розмірами файлів і сегментів, якщо ви компілюєте для налагодження? Для максимальної оптимізації?
> Проаналізуйте результати, щоб переконатися, що:
> ● сегмент даних зберігається у виконуваному файлі;
> ● сегмент BSS не зберігається у виконуваному файлі (за винятком примітки щодо його вимог до розміру часу виконання);
> ● текстовий сегмент більшою мірою піддається перевіркам оптимізації;
> ● на розмір файлу a.out впливає компіляція для налагодження, але не сегменти.
## **Пояснення програми:**

- task2_1.c:  
  Базова програма без глобальних або локальних змінних. У виконуваному файлі міститься тільки текстовий сегмент.
  
**Результат роботи програми:**

![Результат програми](task2/Результат2_1.png)

- task2_2.c:  
  Масив потрапляє у сегмент BSS, який не зберігається у виконуваному файлі, але резервується в пам'яті під час виконання. Розмір ELF-файлу при цьому змінюється незначно або зовсім не змінюється.

**Результат роботи програми:**

![Результат програми](task2/Результат2_2.png)

- task2_3.c:  
  Переміщається в сегмент DATA, який зберігається у виконуваному файлі. Це призводить до збільшення розміру виконуваного файлу.

**Результат роботи програми:**

![Результат програми](task2/Результат2_3.png)

- task2_4.c:  
  Розміщуються у стеку, тому не змінюють структуру або розміри сегментів ELF-файлу. Ініціалізований локальний масив може незначно вплинути на розмір text-сегменту, але незначно.

**Результат роботи програми:**

![Результат програми](task2/Результат2_4.png)

- 5_1, 5_2:  
  Компіляція з параметром -g значно збільшує розмір виконуваного файлу через включення debug-інформації. Компіляція з -O3 зменшує text-сегмент завдяки оптимізації коду, але не впливає на розміри сегментів BSS і DATA.

**Результат роботи програми:**

![Результат програми](task2/Результат2_5_1.png)

![Результат програми](task2/Результат2_5_2.png)

## ЗАВДАННЯ 3

> **Умова: **
> Скомпілюйте й запустіть тестову програму, щоб визначити приблизне розташування стека у вашій системі:
> 
> #include <stdio.h>
> 
> int main() {
 >    int i;
    printf("The stack top is near %p\n", &i);
    return 0;
> }
> 
> Знайдіть розташування сегментів даних і тексту, а також купи всередині сегмента даних, оголосіть змінні, які будуть поміщені в ці сегменти, і виведіть їхні адреси.
Збільшіть розмір стека, викликавши функцію й оголосивши кілька великих локальних масивів. Яка зараз адреса вершини стека?
> 
> Примітка: стек може розташовуватися за різними адресами на різних архітектурах та різних ОС. Хоча ми говоримо про вершину стека, на більшості процесорів стек зростає вниз, до пам’яті з меншими значеннями адрес.

**Результат роботи тестової програми:**

![Результат програми](task3/Результат3_1.png) 

# Пояснення програми task3_2.c:
Код досліджує розташування різних сегментів пам’яті:
Адреса функції func — показує розташування текстового сегмента.
global_var — ініціалізована глобальна змінна - сегмент DATA.
global_bss — неініціалізована глобальна змінна - сегмент BSS.
static_var — статична змінна - сегмент DATA.
local_var, arr1, arr2 — локальні змінні - стек.
malloc() пам’ять на купі (heap).

**Результат роботи програми task3_2.c:**

![Результат програми](task3/Результат3_2.png) 

# Пояснення програми task3_3.c:
У коді досліджується, як змінюється розташування вершини стека при виділенні великих локальних масивів. На початку виводиться адреса змінної i у main, що вказує на початкове розташування стека. Після виклику функції func, де оголошені масиви arr1 і arr2, адреса вершини стека зсувається вниз (у більшість архітектур стек зростає до нижчих адрес). Це ілюструє динамічний характер використання стека під час виконання програми.

**Результат роботи програми task3_3.c:**

![Результат програми](task3/Результат3_3.png) 

**Отже:**
Сегмент тексту містить машинний код функції (адреса func).
Сегмент даних містить ініціалізовані глобальні/статичні змінні.
Сегмент BSS — для глобальних неініціалізованих змінних.
Стек змінюється в межах високих адрес і зменшується при глибших викликах.
Купа зростає в напрямку більших адрес (malloc-виділена пам’ять).

## ЗАВДАННЯ 4

> Умова:  
> Ваше завдання – дослідити стек процесу або пригадати, як це робиться. Ви можете:
> ● Автоматично за допомогою утиліти gstack або procstat (у FreeBSD).  
> ● Вручну за допомогою налагоджувача GDB.
>
> Користувачі Ubuntu можуть зіткнутися з проблемою: на момент написання (Ubuntu 18.04) gstack, схоже, не був доступний (альтернативою може бути pstack). Якщо gstack не працює, використовуйте другий метод – через GDB, як показано нижче. Спочатку подивіться на стек за допомогою gstack(1). Нижче наведений приклад стека bash (аргументом команди є PID процесу):
> $ gstack 14654
> #0 0x00007f359ec7ee7a in waitpid () from /lib64/libc.so.6
> #1 0x000056474b4b41d9 in waitchild.isra ()
> #2 0x000056474b4b595d in wait_for ()
> #3 0x000056474b4a5033 in execute_command_internal ()
> #4 0x000056474b4a5c22 in execute_command ()
> #5 0x000056474b48f252 in reader_loop ()
> #6 0x000056474b48dd32 in main ()
> $
> Розбір стека:
> ● Номер кадру стека відображається ліворуч перед символом #.
> ● Кадр #0 – це найнижчий кадр. Читайте стек знизу вверх (тобто від main() – кадр #6 – до waitpid() – кадр #0).
> ● Якщо процес багатопотоковий, gstack покаже стек кожного потоку окремо.
> 
>   Аналіз стека в режимі користувача через GDB
> Щоб переглянути стек процесу вручну, використовуйте GDB, приєднавшись до процесу. Нижче наведена невелика тестова програма на C, що виконує кілька вкладених викликів функцій. Граф викликів виглядає так:
>     main() --&gt; foo() --&gt; bar() --&gt; bar_is_now_closed() --&gt; pause()
> Системний виклик pause() – це приклад блокуючого виклику. Він переводить викликаючий процес у сплячий режим, очікуючи (або блокуючи) сигнал. У цьому випадку процес блокується, поки не отримає будь-який сигнал.
>
> #include <stdio.h>
> #include <stdlib.h>
> #include <unistd.h>
> #include <sys/types.h>
> 
> #define MSG &quot;In function %20s; &amp;localvar = %p\n&quot;
> 
> static void bar_is_now_closed(void) {
   > int localvar = 5;
   > printf(MSG, FUNCTION, &localvar);
   > printf("\n Now blocking on pause()...\n");
   > pause();
> }
>
> static void bar(void) {
    > int localvar = 5;
    > printf(MSG, FUNCTION, &localvar);
    > bar_is_now_closed();
> }
> 
> static void foo(void) {
   > int localvar = 5;
   > printf(MSG, FUNCTION, &localvar);
   > bar();
>}
>
> int main(int argc, char **argv) {
   > int localvar = 5;
   > printf(MSG, FUNCTION, &localvar);
   > foo();
   > exit(EXIT_SUCCESS);
>}
>
> Тепер відкрийте GDB
> 
> У ньому підключіться (attach) до процесу (в наведеному прикладі PID = 24957) і дослідіть стек > за допомогою команди backtrace (bt):
> 
> $ gdb --quiet
> (gdb) attach 24957
> Attaching to process 24957
> Reading symbols from <...>/hspl/unit2/stacker...done.
> Reading symbols from /lib64/libc.so.6...Reading symbols from
> /usr/lib/debug/usr/lib64/libc-2.26.so.debug...done.
> done.
> Reading symbols from /lib64/ld-linux-x86-64.so.2...
> Reading symbols
> ...
> (gdb) bt
> ...
>
>   Примітка: В Ubuntu, через питання безпеки, GDB не дозволяє підключатися до довільного процесу. Це можна обійти, запустивши GDB від імені користувача root.
>
> Аналіз того ж процесу через gstack
>
> $ gstack 24957 ...
>
> gstack — це, по суті, оболонковий скрипт (wrapper shell script), який неінтерактивно викликає GDB і запускає команду backtrace, яку ви щойно використали.
> Завдання: Ознайомтеся з виводом gstack і порівняйте його з GDB.

Програма демонструє вкладені виклики функцій із передачею керування через main(), foo(), bar(), bar_is_now_closed() і подальше блокування на системному виклику pause().
Кожна функція виводить адресу своєї локальної змінної, що дозволяє відстежувати зміни в стеку.
Для дослідження стека процесу було використано інструмент GDB.

| Інструмент | Особливості                                                                                          | Результати аналізу                                                                                       |
| ---------- | ---------------------------------------------------------------------------------------------------- | -------------------------------------------------------------------------------------------------------- |
| GDB        | Інтерактивний налагоджувач, який дозволяє підключитися до процесу і виконувати діагностичні команди. | Дозволяє детально переглядати стек, локальні змінні та здійснювати покадровий аналіз виконання програми. |

| Критерій                    | GDB                          |
| --------------------------- | ---------------------------- |
| Режим роботи                | Інтерактивний                |
| Інформація про стек         | Повна (із символами)         |
| Підтримка багатопотоковості | Аналіз кожного потоку вручну |
| Складність використання     | Середня                      |
| Призначення                 | Глибокий аналіз              |


# Результат роботи:

**Запуск програми:**

![Результат програми](task4/Результат4.png) 

**GDB:**

![Результат програми](task4/Результат4_2.png) 

## ЗАВДАННЯ 5

Умова:  
Відомо, що при виклику процедур і поверненні з них процесор використовує стек.  
Чи можна в такій схемі обійтися без лічильника команд (Instruction Pointer, IP), використовуючи замість нього вершину стека?  
Обґрунтуйте свою відповідь та наведіть приклади.

---

### Код до завдання  
#### 1. Базовий приклад — коректна робота з IP і стеком

#include <stdio.h>

void demo() {
    printf("Це функція demo()\n");
}

int main() {
    printf("Викликаємо demo()\n");
    demo();
    printf("Повернулись у main()\n");
    return 0;
}

# Результат роботи:

![Результат програми](task5/Результат5_1.png) 

#### 2. Приклад з ручним пошкодженням стека

#include <stdio.h>

void broken() {
    printf("Перед маніпуляцією зі стеком\n");

    // Ручне видалення адреси повернення з вершини стека
    asm("addq $8, %rsp");

    printf("Цей рядок не буде виведений\n");
}

int main() {
    broken();
    return 0;
}

# Результат роботи:

![Результат програми](task5/Результат5_2.png) 

# Пояснення програми:
У цьому завданні ми дослідили, чи можна замінити лічильник команд (IP) вершиною стека при виклику функцій і поверненні з них.

У першому коді (task5a) — показано стандартний механізм:
при виклику demo() процесор зберігає адресу повернення в стеку, а при завершенні — автоматично зчитує її та оновлює IP. Після цього виконання продовжується у main().

У другому коді (task5b) — ми вручну зсунули стек, видаливши адресу повернення з вершини. Коли процесор намагається повернутись (ret), він читає зіпсовану адресу, що викликає аварійне завершення програми (Segmentation fault).

Отже відповідь:
Ні, замінити IP вершиною стека неможливо.
IP — це окремий регістр, який вказує на поточну інструкцію, що виконується.
Стек — лише тимчасове сховище для адрес повернення, але не визначає напрям виконання.
Процесор довіряє стеку лише при ret, але сам IP завжди контролює поточний стан виконання.

Порівняння прикладів:
| Приклад                | Особливості                                                                 | Результат роботи                                        |
| ---------------------- | --------------------------------------------------------------------------- | ------------------------------------------------------- |
| Базовий виклик функції | Стандартний механізм — IP зберігається у стеку та автоматично відновлюється | Програма виконується правильно                          |
| Маніпуляція зі стеком  | Ручне знищення адреси повернення зі стеку (`addq $8, %rsp`)                 | Segmentation fault — процесор не знає, куди повертатися |

## ЗАВДАННЯ ЗА ВЛАСНИМ ВАРІАНТОМ (варіант 23)

Умова:  
Дослідіть поведінку програми при сегментації пам’яті.

---

### Загальна мета:  
З’ясувати, у яких випадках відбувається помилка Segmentation fault, як вона виникає і що спричиняє порушення доступу до пам’яті в різних ситуаціях.

---

### Код до завдання

#### Приклад 1: Звернення до NULL-вказівника

#include <stdio.h>

int main() {
    int *p = NULL;
    *p = 42;  // спроба запису в нульову адресу
    return 0;
}

# Результат роботи:

![Результат програми](task6/Результат6_1.png) 

Приклад 2: Вихід за межі масиву

#include <stdio.h>

int main() {
    int arr[5];
    arr[100] = 123;  // вихід за межі масиву
    return 0;
}

# Результат роботи:

![Результат програми](task6/Результат6_2.png) 

Приклад 3: Запис у рядковий літерал (read-only пам’ять)

#include <stdio.h>

int main() {
    char *str = "hello";
    str[0] = 'H';  // спроба змінити read-only дані
    return 0;
}

# Результат роботи:

![Результат програми](task6/Результат6_3.png) 

Приклад 4: Ручне порушення стека

#include <stdio.h>

void damage_stack() {
    printf("Перед зміщенням стека\n");
    asm("addq $8, %rsp");  // зсув стеку — руйнування адреси повернення
}

int main() {
    damage_stack();
    printf("Цей рядок не буде виведено\n");
    return 0;
}

# Результат роботи:

![Результат програми](task6/Результат6_4.png) 

**Пояснення:**
Усі приклади викликають сегментаційну помилку (SIGSEGV) через порушення меж дозволеної пам’яті, а саме:
Звернення до NULL-вказівника — звернення до неініціалізованої області пам’яті.
Вихід за межі масиву — доступ до невиділеної області пам’яті.
Запис у read-only область — порушення захисту сегменту даних.
Пошкодження стека — некоректне повернення після функції.

**Аналіз результатів:**
Приклад  Причина порушення пам’яті  Результат
NULL-вказівник  Доступ до адреси 0  Segmentation fault
Вихід за межі масиву  Порушення меж виділеного буфера  Segmentation fault
Зміна рядка (літерала)  Спроба запису в read-only пам’ять  Segmentation fault
Зміщення стека вручну  Пошкодження адреси повернення  Segmentation fault

**Отже з'ясували:**
Сегментаційна помилка (Segmentation fault) — це механізм захисту пам’яті, який запобігає небезпечним операціям над критичними ділянками.
Це гарантує стабільність ОС та безпеку інших процесів.
Будь-які спроби звернення до заборонених або некоректно керованих областей пам’яті завершуються аварійно — сигналом SIGSEGV.
