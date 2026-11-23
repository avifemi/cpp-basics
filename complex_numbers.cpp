#include <iostream>
#include <cmath>
#include <stdexcept>
using namespace std;

class complex_numbers
{
private:
    double Re; //Re - действительная часть
    double Im; //Im - мнимая часть

public:
    complex_numbers(); //конструктор без параметров
    complex_numbers(double Re, double Im); //конструктор
    complex_numbers(complex_numbers const& first_num); //конструктор копирования

    complex_numbers& operator =(complex_numbers const& first_num);
    complex_numbers& operator +=(complex_numbers const& first_num);

    complex_numbers operator +(complex_numbers const& first_num) const;
    complex_numbers operator -(complex_numbers const& first_num) const;
    complex_numbers operator *(complex_numbers const& first_num) const;
    complex_numbers operator /(complex_numbers const& first_num) const;

    void arg_complex_numbers();
    double mod_complex_numbers();
    void show();
};

void complex_numbers::arg_complex_numbers()
{
    if(Re == 0 && Im == 0)
    {
        cout << "Аргумент комплексного числа не определён";
    }
    else
    {
        cout << atan2(Im, Re) << "+2πn, где n ∈ Z";
    }
}

void complex_numbers::show()
{
    if(Im >= 0)
    {
        cout << "Комплексное число = " << Re << "+" << Im << "i" << endl;
    }
    else
    {
        cout << "Комплексное число = " << Re << Im << "i" << endl;
    }
}

double complex_numbers::mod_complex_numbers()
{
    return sqrt((Re*Re) + (Im*Im));
}

complex_numbers::complex_numbers(double Re1, double Im1)
{
    Re = Re1;
    Im = Im1;
}

complex_numbers::complex_numbers()
{
    Re = 0.0;
    Im = 0.0;
}

complex_numbers::complex_numbers(complex_numbers const& first_num)
{
    Re = first_num.Re;
    Im = first_num.Im;
}

complex_numbers& complex_numbers::operator=(complex_numbers const& first_num)
{
    Re = first_num.Re;
    Im = first_num.Im;

    return *this;
}

complex_numbers& complex_numbers::operator+=(complex_numbers const& first_num)
{
    Re += first_num.Re;
    Im += first_num.Im;

    return *this;
}

complex_numbers complex_numbers::operator +(complex_numbers const& first_num) const
{
    complex_numbers ob;

    ob.Re = Re + first_num.Re;
    ob.Im = Im + first_num.Im;

    return ob;
}

complex_numbers complex_numbers::operator -(complex_numbers const& first_num) const
{
    complex_numbers ob;

    ob.Re = Re - first_num.Re;
    ob.Im = Im - first_num.Im;

    return ob;
}

complex_numbers complex_numbers::operator *(complex_numbers const& first_num) const
{
    complex_numbers ob;

    ob.Re = Re * first_num.Re - Im * first_num.Im;
    ob.Im = Re * first_num.Im + Im * first_num.Re;

    return ob;
}

complex_numbers complex_numbers::operator /(complex_numbers const& first_num) const
{
    double Zn;

    Zn = first_num.Re * first_num.Re + first_num.Im * first_num.Im;

    if(Zn == 0)
    {
        throw runtime_error("Деление на ноль");
    }

    complex_numbers ob;

    ob.Re = (Re * first_num.Re + Im * first_num.Im) / Zn;
    ob.Im = (Im * first_num.Re - Re * first_num.Im) / Zn;

    return ob;
}

int main()
{
    complex_numbers ob(2.0, 3.0);
    complex_numbers ob1(-5.0, 7.0);
    complex_numbers ob2;

    cout << "Первое число: ";
    ob.show();

    cout << "Второе число: ";
    ob1.show();

    ob2 = ob + ob1;
    cout << "Сложение: ";
    ob2.show();

    ob2 = ob - ob1;
    cout << "Вычитание: ";
    ob2.show();

    ob2 = ob * ob1;
    cout << "Умножение: ";
    ob2.show();

    try
    {
        ob2 = ob / ob1;
        cout << "Деление: ";
        ob2.show();
    }
    catch(const runtime_error& error)
    {
        cout << error.what() << endl;
    }

    cout << "Модуль первого числа: " << ob.mod_complex_numbers() << endl;

    cout << "Аргумент первого числа: ";
    ob.arg_complex_numbers();
    cout << endl;

    return 0;
}