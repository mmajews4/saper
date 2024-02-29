#include <iostream>
#include <string>

using namespace std;

struct Student {
    string imie;
    string nazwisko;
    string pesel;
    string numer_indeksu;
    string plec;
};

void display_student(Student s){
    cout << s.imie << " " << s.nazwisko << endl << "Pesel: " << s.pesel << endl;
    cout << "Nr albumu: " << s.numer_indeksu << endl << "Plec: " << s.plec << endl << endl;
}

Student read_student() {
    Student s;

    cout << "Wpisz imię: ";
    getline(cin, s.imie);
    cout << "Wpisz nazwisko: ";
    getline(cin, s.nazwisko);
    cout << "Wpisz pesel: ";
    getline(cin, s.pesel);
    cout << "Wpisz numer indeksu: ";
    getline(cin, s.numer_indeksu);
    cout << "Wpisz płeć: ";
    getline(cin, s.plec);

    return s;
}

int main() {
    Student s[5];
    s[0] = {"Tomek", "Anonimski", "19749195", "983457", "mężczyzna"};
    s[1] = {"Joanna", "Mazur", "12159015", "278316", "kobieta"};
    Student s_read = read_student();

    display_student(s_read);
    display_student(s[0]);
    display_student(s[1]);

    return 0;
}
