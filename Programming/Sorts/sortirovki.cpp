#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <cmath>
using namespace std;

struct Data {
    int day;
    int month;
    int year;
};

struct Worker {
    string surname;     
    string position;     
    Data date_of_birth;  
    int expirience;            
    int salary;         
};

Data preobr_data(string &data_str) {
    Data d;
    int pos1 = data_str.find('.');
    int pos2 = data_str.find('.', pos1 + 1);
    d.day = stoi(data_str.substr(0, pos1));
    d.month = stoi(data_str.substr(pos1 + 1, pos2 - pos1 - 1));
    d.year = stoi(data_str.substr(pos2 + 1));
    return d;
}

vector<Worker> get_info_from_file(string &filename) {
    vector<Worker> workers;
    ifstream in(filename);
    if (!in.is_open()) {
        cerr << "Error: file " << filename << " is not openable" << endl;
        return workers;
    }
    string surname, position, data_str;
    int expirience, salary;

    // in - объект ifstream (файловый поток ввода); оператор >> читает из файла
    // данные, разделенные пробелами, а всё выр-е в скобках возвращает in (сам поток)
    while (in >> surname >> position >> data_str >> expirience >> salary) {
        Worker curr_worker;
        curr_worker.surname = surname;
        curr_worker.position = position;
        curr_worker.date_of_birth = preobr_data(data_str);
        curr_worker.expirience = expirience;
        curr_worker.salary = salary;
        workers.push_back(curr_worker);
    }
    in.close();
    return workers;
}

void give_info_in_file(ofstream &out, Worker &curr_worker) {
    out << setw(20) << left << curr_worker.surname;
    out << setw(25) << left << curr_worker.position;
    if (curr_worker.date_of_birth.day < 10) {
        out << '0';
    }
    out << curr_worker.date_of_birth.day << '.';
    if (curr_worker.date_of_birth.month < 10) {
        out << '0';
    }
    out << curr_worker.date_of_birth.month << '.';
    out << curr_worker.date_of_birth.year;
    out << setw(6) << " "; 
    
    out << setw(10) << left << curr_worker.expirience;
    out << setw(10) << left << curr_worker.salary << endl;
}

void give_info_all_workers(string &filename, vector<Worker> &workers, string headline) {
    ofstream out(filename);
    if (!out.is_open()) {
        cerr << "Error: can't create file " << filename << endl;
        return;
    }
    out << "----------------------- " << headline << " -----------------------" << endl;
    out << setw(20) << left << "Surname";
    out << setw(25) << left << "Position";
    out << setw(15) << left << "Date of birth";
    out << setw(12) << left << "Experience";
    out << setw(10) << left << "Salary" << endl;
    out << string(82, '-') << endl;
    
    for (int i = 0; i < workers.size(); ++i) {
        give_info_in_file(out, workers[i]);
    }
    out.close();
}

// 1. Поразрядная сортировка LSD по зарплате      | сортировка от младшего разрядка к старшему |

int get_max_salary(vector<Worker> &arr) {
    if (arr.empty()) {
        return 0;
    }
    int max = arr[0].salary;
    for (int i = 0; i < arr.size(); ++i) {
        if (arr[i].salary > max) {
            max = arr[i].salary;
        }
    }
    return max;
}

void porazryadnaya_sortirovka_LSD(vector<Worker> &arr) {
    if (arr.empty()) {
        return;
    }
    int max_salary = get_max_salary(arr);
    int osn = 10;
    
    // проходим по каждому разряду
    for (int exp = 1; (max_salary / exp) > 0; exp *= osn) {
        // делаем 10 "коробок"
        vector<vector<Worker>> box(osn);
        
        // распределяем элементы по коробкам в зависимости от текущего разряда
        for (int i = 0; i < arr.size(); ++i) {
            int digit = (arr[i].salary / exp) % osn;
            box[digit].push_back(arr[i]);   
        }
        
        // собираем элементы обратно в массив, обходим коробки по порядку
        int index = 0;
        for (int i = 0; i < osn; ++i) {
            for (int j = 0; j < box[i].size(); ++j) {
                arr[index] = box[i][j];
                index++;
            }
        }
    }
}

// 2. Гномья сортировка                  | сначала по должности, потом по зарплате |
bool sravnit_position_salary(Worker &a, Worker &b) {
    if (a.position != b.position) {
        return a.position < b.position;
    }
    return a.salary <= b.salary;
}

void gnomya_sortirovka(vector<Worker> &arr) {
    if (arr.empty()) return;
    int i = 1;
    while (i < arr.size()) {
        if (i == 0 || sravnit_position_salary(arr[i-1], arr[i])) {
            i++;
        } else {
            swap(arr[i-1], arr[i]);
            i--;
        }
    }
}

// 3. Сортировка пузырьком              | сначала по должности, потом по статусу, потом по зарплате |
bool sravnit_position_expirience_salary(Worker &a, Worker &b) {
    if (a.position != b.position) {
        return a.position < b.position;
    }
    if (a.expirience != b.expirience) {
        return a.expirience < b.expirience;
    }
    return a.salary < b.salary;
}

void puzyrkovaya_sortirovka(vector<Worker> &arr) {
    if (arr.empty()) return;
    
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        bool was_swap = false;
        // Идем справа налево, как в методичке
        for (int j = n - 1; j > i; --j) {
            if (!sravnit_position_expirience_salary(arr[j-1], arr[j])) {
                swap(arr[j-1], arr[j]); 
                was_swap = true;
            }
        }
        if (!was_swap) {
            break;
        }
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    
    string input_file = "sotrudniki_predpriyatiya.txt";
    string output_file_1 = "sorted_by_razr.txt";
    string output_file_2 = "sorted_by_gnome.txt";
    string output_file_3 = "sorted_by_bubble.txt";
    
    vector<Worker> workers = get_info_from_file(input_file);
    
    if (workers.empty()) {
        cerr << "File hasn`t data" << endl;
        return 0;
    }
    
    vector<Worker> workers1 = workers;
    porazryadnaya_sortirovka_LSD(workers1);
    give_info_all_workers(output_file_1, workers1, "Sort by salary (porazryadnaya LSD)");
    cout << "Sort by salary (porazryadnaya LSD) complete. Result in file: " << output_file_1 << endl;
    
    vector<Worker> workers2 = workers;
    gnomya_sortirovka(workers2);
    give_info_all_workers(output_file_2, workers2, "Sort by position, then by salary (gnomya)");
    cout << "Sort by position, then by salary (gnomya) complete. Result in file: " << output_file_2 << endl;

    vector<Worker> workers3 = workers;
    puzyrkovaya_sortirovka(workers3);
    give_info_all_workers(output_file_3, workers3, "Sort by position, expirience, salary (puzyrkovaya)");
    cout << "Sort by position, expirience, salary (puzyrkovaya) complete. Result in file: " << output_file_3 << endl;
   
    cout << "\nVse sortirovki zaversheny!" << endl;
    
    return 0;
}