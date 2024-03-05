#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Student {
    string imie;
    string nazwisko;
    string pesel;
    string numer_indeksu;
    string plec;
};


struct BazaStudentow {
    string nazwa_uczelni;
    vector<Student> student;
};


void display_student(Student s){
    cout << s.imie << " " << s.nazwisko << endl << "Pesel: " << s.pesel << endl;
    cout << "Nr albumu: " << s.numer_indeksu << endl << "Plec: " << s.plec << endl << endl;
}


void display_all_students(Student* s, int student_number){
    for(int i=0; i<student_number; i++)
    {
        display_student(s[i]);
    }
}


void display_all_students_vec(vector<Student> s, int student_number){
    for(int i=0; i<student_number; i++)
    {
        display_student(s[i]);
    }
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


void add_student(BazaStudentow* baza) {

    baza->student.push_back(read_student());
}


int find_student(BazaStudentow* baza, string poszukiwany_indeks){

    int pozycja = baza->student.size();

    while(baza->student[pozycja].numer_indeksu != poszukiwany_indeks){
        pozycja--;
    }
    return pozycja;
}


void remove_student(BazaStudentow* baza, string poszukiwany_indeks){

    int pozycja = find_student(baza, poszukiwany_indeks);

    if(pozycja >= 0){
        baza->student.erase(baza->student.begin() + pozycja);
    }
}


void load_students(BazaStudentow* baza){

    string file_name;
    string line;

    cout << "Wpisz nazwę pliku do wczytania: ";
    cin >> file_name;

    ifstream input_file(file_name);

    if (!input_file.is_open()) {
        std::cerr << "Nie można otworzyć pliku do odczytu.\n";
        return;
    }

    while (getline(input_file, line)) {

        Student s;
        stringstream stream(line);

        stream >> s.imie >> s.nazwisko >> s.pesel >> s.numer_indeksu >> s.plec;
        
        baza->student.push_back(s);
    }

    input_file.close();
}


void save_students(BazaStudentow* baza){

    string file_name;
    cout << "Wpisz nazwę pliku do zapisania: ";
    cin >> file_name;

    ofstream output_file(file_name);

    if (!output_file.is_open()) {
        std::cerr << "Nie można otworzyć pliku do zapisu.\n";
        return;
    }

    int pozycja = baza->student.size() - 1;

    while(pozycja >= 0){

        output_file << baza->student[pozycja].imie << " ";
        output_file << baza->student[pozycja].nazwisko << " ";
        output_file << baza->student[pozycja].pesel << " ";
        output_file << baza->student[pozycja].numer_indeksu << " ";
        output_file << baza->student[pozycja].plec << "\n";

        pozycja--;
    }

    output_file.close();
}

int main() {

    //Dekalracje
    int number_of_s1 = 5, number_of_s2 = 3;
    string szukany_indeks;
    Student s1[number_of_s1];
    Student s2[number_of_s2];

    BazaStudentow uczelnia1;
    BazaStudentow uczelnia2;

    s1[0] = {"Tomek",  "Anonimski", "19749195", "983457", "mężczyzna"};
    s1[1] = {"Joanna", "Mazur",     "12159015", "278316", "kobieta"};
    s1[2] = {"Antoni", "Kraczewski","14390987", "093812", "mężczyzna"};
    s1[3] = {"Milena", "Kosman",    "18875210", "823579", "kobieta"};
    s1[4] = {"Bartek", "Olejnik",   "10361540", "981756", "mężczyzna"};

    s2[0] = {"Ania",   "Bąk",       "19749195", "983427", "kobieta"};
    s2[1] = {"Katasia","Jackowska", "12159015", "223316", "kobieta"};
    s2[2] = {"Karol",  "Mak",       "14390987", "093232", "mężczyzna"};

    // Testy funkcji
    cout << "Wczytaj studenta" << endl;
    Student s_read = read_student();

    cout << "\n\nWyświetl wczytanego studenta oraz studentów dwóch innych grup" << endl;
    display_student(s_read);
    cout << "\nGrupa 1" << endl;
    display_all_students(s1, number_of_s1);
    cout << "\nGrupa 2" << endl;
    display_all_students(s2, number_of_s2);

    cout << "\nDodaj studenta do uczelni 1" << endl;
    add_student(&uczelnia1);

    cout << "\nSzukaj studenta uczelni 1 \nWypisz indeks szukanego studenta:";
    cin >> szukany_indeks;
    cout << find_student(&uczelnia1, szukany_indeks) << endl;

    cout << "\nUsuń studenta uczelni 1\nWypisz indeks szukanego studenta:";
    cin >> szukany_indeks;
    remove_student(&uczelnia1, szukany_indeks);

    cout << "\nWczytaj studentów uczelni 2 z pliku" << endl;
    load_students(&uczelnia2);

    cout << "\nZapisz studentów uczelni 1 do pliku" << endl;
    save_students(&uczelnia1);

    cout << "\nPomyślnie wczytano \nWyświetl studentów uczelni 1" << endl;
    display_all_students_vec(uczelnia1.student, uczelnia1.student.size());
    cout << "\nWyświetl studentów uczelni 2" << endl;
    display_all_students_vec(uczelnia2.student, uczelnia2.student.size());

    return 0;
}
