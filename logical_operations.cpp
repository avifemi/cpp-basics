#include <iostream>
#include <cstring>

using namespace std;

class logical_values_array
{
private:
    unsigned int _value; //0 принимаем за false, а !0 за true
public:
    unsigned int get_value(); //accessor или же просто геттер(метод get)
    logical_values_array(); //конструктор без принимабщих параметров
    logical_values_array(unsigned int value); //конструктор
    logical_values_array& operator=(unsigned int value);
    logical_values_array& inversion_value(); //инверсия
    logical_values_array& conjunction_value(logical_values_array ob); //конъюкция
    logical_values_array& disjunction_value(logical_values_array ob); //дизъюнкция
    logical_values_array& implication_value(logical_values_array ob); //импликация
    logical_values_array& coimplication_value(logical_values_array ob); //коимпликация
    logical_values_array& addition_modulo_2_value(logical_values_array ob); //сложение по модулю 2
    logical_values_array& equivalence_value(logical_values_array ob); //эквивалентность
    logical_values_array& Pier_arrow_value(logical_values_array ob); //стрелка Пирса
    logical_values_array& Schaeffers_stroke_value(logical_values_array ob); //штрих Шеффера
    static bool equals(unsigned int a, unsigned int b); //я принимаю это как полную экв. типа 1!=45, 1=1, 45=45
    char* perevod2cc();
    char get_bit(unsigned int position);
};

unsigned int logical_values_array::get_value()
{
    return _value;
}

logical_values_array::logical_values_array()
{
    _value = 0;
}

logical_values_array::logical_values_array(unsigned int value)
{
    _value = value;
}

logical_values_array& logical_values_array::operator=(unsigned int value)
{
    _value = value;
    
    return *this;
}

logical_values_array& logical_values_array::inversion_value()
{
    if(_value == 0)
    {
        _value = 1;
    }
    
    else
    {
        _value = 0;
    }
    
    return *this;
}

logical_values_array& logical_values_array::conjunction_value(logical_values_array ob)
{
    if((_value >= 1) && (ob._value >= 1))
    {
        _value = 1;
    }
    
    else
    {
        _value = ob._value * _value;
    }
    
    return *this;
}

logical_values_array& logical_values_array::disjunction_value(logical_values_array ob)
{
    if(_value == 0 && ob._value == 0)
    {
        _value = 0;
    }
    
    else
    {
        _value = 1;
    }
    
    return *this;
}

logical_values_array& logical_values_array::implication_value(logical_values_array ob)
{
    logical_values_array ob1(_value);
    ob1.inversion_value();
    ob1.disjunction_value(ob);
    _value = ob1._value;
    
    return *this;
}

logical_values_array& logical_values_array::coimplication_value(logical_values_array ob)
{
    logical_values_array ob1(_value);
    ob1.implication_value(ob);
    _value = ob1._value;
    if(_value == 0)
    {
        _value = 1;
    }
    
    else
    {
        _value = 0;
    }
    
    return *this;
}

logical_values_array& logical_values_array::addition_modulo_2_value(logical_values_array ob)
{
    //формула: (X1∨ X2) ∧ (¬X1∨ ¬X2)
    logical_values_array a(_value);
    logical_values_array a1(_value);
    
    a.disjunction_value(ob); //левая скобка
    a1.inversion_value();
    ob.inversion_value();
    a1.disjunction_value(ob); //правая скобка
    a1.conjunction_value(a);
    _value = a1._value;
    
    return *this;
}

logical_values_array& logical_values_array::equivalence_value(logical_values_array ob)
{
    //формула (X1∨¬X2) ∧ (¬X1∨X2)
    logical_values_array a(_value);
    logical_values_array a1(_value);
    ob.inversion_value();
    a.disjunction_value(ob); //левая скобка
    a1.inversion_value();
    ob.inversion_value(); //вернули x2 в исходное состояние
    a1.disjunction_value(ob); //правая скобка
    a.conjunction_value(a1);
    _value = a._value;
    
    return *this;
}

logical_values_array& logical_values_array::Pier_arrow_value(logical_values_array ob)
{
    //формула ¬X1 ∧ ¬X2
    logical_values_array a(_value);
    a.inversion_value();
    ob.inversion_value();
    a.conjunction_value(ob);
    _value = a._value;
    
    return *this;
}

logical_values_array& logical_values_array::Schaeffers_stroke_value(logical_values_array ob)
{
    //формула ¬X1 ∨ ¬X2
    logical_values_array a(_value);
    a.inversion_value();
    ob.inversion_value();
    a.disjunction_value(ob);
    _value = a._value;
    
    return *this;
}

bool logical_values_array::equals(unsigned int a, unsigned int b)
{
    if(a == b)
    {
        return true;
    }
    
    else
    {
        return false;
    }
}

char* logical_values_array::perevod2cc()
{
    unsigned int a = _value;
    unsigned int count = 0;

    //считаем количество битов в числе
    do
    {
        count++;
        a = a >> 1;
    }
    while(a != 0);

    //создаем массив для хранения числа в 2сс в виде строки
    char* mas = new char[count + 1];
    mas[count] = '\0';

    a = _value;

    //записываем биты справа налево
    for(int i = (int)count - 1; i >= 0; i--)
    {
        mas[i] = '0' + (a & 0x00000001);
        a = a >> 1;
    }

    return mas;
}

char logical_values_array::get_bit(unsigned int position)
{
    char* ptr = perevod2cc();
    unsigned int length = strlen(ptr);

    if(position >= length)
    {
        position = length - 1;
    }

    char bit = ptr[position];
    delete[] ptr;

    return bit;
}

int main()
{
    logical_values_array ob(10);
    logical_values_array ob1(5);

    cout << "Первое число: " << ob.get_value() << endl;
    cout << "Второе число: " << ob1.get_value() << endl;

    logical_values_array a(ob.get_value());
    a.conjunction_value(ob1);
    cout << "Конъюнкция: " << a.get_value() << endl;

    logical_values_array b(ob.get_value());
    b.disjunction_value(ob1);
    cout << "Дизъюнкция: " << b.get_value() << endl;

    cout << "Полная эквивалентность: " << logical_values_array::equals(10, 10) << endl;

    char* mas = ob.perevod2cc();
    cout << "Число в двоичной системе: " << mas << endl;
    delete[] mas;

    cout << "Бит по позиции 1: " << ob.get_bit(1) << endl;

    return 0;
}
