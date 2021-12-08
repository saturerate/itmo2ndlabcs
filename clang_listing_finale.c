/*Назовем триплетом группу из трех битов. В каждом
третьем триплете, начиная с младшего, изменить
порядок следования битов на обратный (2,5,8,...).

0xDEADBEEF ->
0xDBAF3FAF */

#include <stdio.h>

// Прототипы функций
void the_action_itself(unsigned int);
void base_2(int number);
int number = 0xd5ad6abf;
int main() {

    printf("%x\n", number);
    base_2(number);


    // В каждом третьем триплете меняем местами первый и последний бит;
    for (int i = 6; i < 32; i += 9) {
       the_action_itself(i);
    }

    printf("%x\n", number);
    base_2(number);

    return 0;
}

// Вся магия происходит здесь...
void the_action_itself (unsigned int i) {
    //unsigned int i, i + 2; // Позиции битов, которые мы обмениваем
    
    unsigned int x = ((number >> i) ^ (number >> i + 2)) & 1; // Временный XOR
    number = number ^ ((x << i) | (x << i + 2));
}

/*
    1.1) Побитового сдвигаем вправо так, чтобы на месте младшего бита оказались биты, которые мы хотим поменять местами
    1.2) XOR'им числа, сдвинутые согласно 1му пункту
    1.3) Побитого умножаем результат с 1 => у нас остается число, где младший бит есть результат XOR'а, сделанного в пункте 1.2
    и нулями во всех остальных битах => это есть число x
    2.1) Побитого сдвигаем влево, чтобы число x находилось в позициях битов, которые мы хотим обменять
    2.2) "Объединяем" 2 числа при помощи побитового или.
    Результат выглядит так - 0...0[1ый бит, который участвует в обмене]0...0[2ой бит, который участвует в обмене]0...0,
    где на месте ... некоторое количество нулей.
    2.3) XOR'им исходное число c результатом из пункта 2.2 - обмен произошёл
    Алгоритм работает по аналогии с обычным обменом значений переменных при помощи XOR'а за исключением того, что
    мы обмениваем отдельные биты. Корректность работы алгоритма обусловлена тем, что алгебра с носителем {0,1}
    и сигнатурой, состоящей из одной бинарной операции исключающего или, есть абелева группа.
*/

//Функция вывода числа в двоичной системе счисления
void base_2(int n) {
    int k = 0;
    for (int c = 31; c >= 0; c--) {
        k = n >> c;
        if (k & 1)
            printf("1");
        else
            printf("0");
    }
    printf("\n");
}