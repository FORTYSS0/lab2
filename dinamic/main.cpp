#include <iostream>

using std::cout;
using std::cin;
using std::endl;

void sort_case2(int a1, int a2, int* a3, int a4){
    int v4; // edi@1
    int v5; // esi@1
    int *v6; // eax@1
    int v7; // edx@1
    int v8; // ecx@1
    int *v9; // edi@2
    int *v10; // edi@5
    int *v11; // ecx@5
    int v12; // ecx@7
    int *v13; // edi@8
    int *v14; // eax@8
    int v15; // [sp+8h] [bp-8h]@1
    int v16; // [sp+8h] [bp-8h]@5
    int *v17; // [sp+Ch] [bp-4h]@1
    int v18; // [sp+18h] [bp+8h]@7

    v4 = a1;
    v5 = a2;
    v15 = a1 + a4;
    v6 = new int[v15];
    v7 = v5 + v4;
    v17 = v6;
    v8 = v5;
    if ( v5 < v5 + v4 )
    {
        v9 = v6;
        do
        {
            *v9 = a3[v8++];
            ++v9;
        }
        while ( v8 < v7 );
    }
    if ( a4 > 0 )
    {
        v10 = &v6[v15 - 1];
        v11 = &a3[v7];
        v16 = a4;
        do
        {
            *v10 = *v11;
            ++v11;
            --v10;
            --v16;
        }
        while ( v16 );
    }
    v18 = v7 + a4;
    v12 = v5;
    if ( v5 < v18 )
    {
        v13 = v6;
        v14 = &v6[v18 - 1 - v5];
        do
        {
            if ( *v14 >= *v13 )
            {
                a3[v12] = *v13;
                ++v13;
            }
            else
            {
                a3[v12] = *v14;
                --v14;
            }
            ++v12;
        }
        while ( v12 < v18 );
        v6 = v17;
    }
    delete(v6);
}

void sort_case1(int* array, int begin, int end){
    int even = 0;
    if(end % 2)
        even = 1;
    if(end != 1){
        if(end != 2){
            sort_case1(array, begin, end/2 + even);
            sort_case1(array, begin + end/2 + even, end/2);
        }
        sort_case2(even + end/2, begin, array, end/2);
    }
}

int main() {
    srand(time(nullptr));
    int array_size;
    cout << "Input size of array:";
    cin >> array_size;
    int* array = new int [array_size];
    cout << "Choose the method of filling:\n"
            "1.Random filling\n"
            "2.Hand filling" << endl;
    int choice_filling;
    cin >> choice_filling;
    int random_module;
    int filling_counter = 0;
    int current_element;
    switch (choice_filling) {
        case 1:
            cout << "Choose the module:";
            cin >> random_module;
            do{
                array[filling_counter] = rand() % random_module;
                ++filling_counter;
            } while (filling_counter < array_size);
            break;
        case 2:
            filling_counter = array_size;
            do{
                cin >> current_element;
                array[array_size - filling_counter] = current_element;
                -- filling_counter;
            } while (filling_counter);
            break;
        case 3:
            return 0;
    }
    int choice_action;
    int ticks_begin, ticks_end;
    do{
        while (true){
            while(true){
                cout << "Choose action:\n"
                        "1.Sort array\n"
                        "2.Print array\n"
                        "3.Exit\n";
                cin >> choice_action;
                if(choice_action != 1)
                    break;
                ticks_begin = clock();
                int is_array_even = 0;
                if(array_size % 2)
                    is_array_even = 1;
                if(array_size != 1){
                    if(array_size != 2){
                        sort_case1(array, 0, is_array_even + array_size / 2);
                        sort_case1(array, is_array_even + array_size / 2, array_size / 2);
                    }
                    sort_case2(is_array_even + array_size / 2, 0, array, array_size / 2);
                }
                ticks_end = clock();
                cout << ticks_end - ticks_begin;
            }
            if(choice_action != 2)
                break;
            for(int i = 0; i < array_size; ++i)
                cout << array[i] << ",";
        }
    } while (choice_action != 3);
    return 0;
}
