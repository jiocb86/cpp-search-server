// Решите загадку: Сколько чисел от 1 до 1000 содержат как минимум одну цифру 3?
// Напишите ответ здесь:
#include <iostream>

using namespace std;

int main()
{
    int count = 0;
    for (int hundreds = 0; hundreds < 10; ++hundreds) {
        for (int tens = 0; tens < 10; ++tens) {
            for (int units = 0; units < 10; ++units)
            {
                if (hundreds == 3 || tens == 3 || units == 3) {
                    ++count;
                }
            }
        }
    }
    cout << count << endl;
    return 0;
}
// Закомитьте изменения и отправьте их в свой репозиторий.
