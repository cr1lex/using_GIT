#include <iostream>
#include <string>
using namespace std;

struct queue {
    int inf;       // номер клетки от 0 до 63
    queue *next;
};

void push(queue *(&h), queue *(&t), int x) {
    queue *r = new queue;
    r->inf = x;
    r->next = NULL;
    if (!h && !t) {h = t = r;} 
    else {
        t->next = r;
        t = r;
    }
}

int pop(queue *&h, queue *&t) {
    queue *r = h;
    int i = h->inf;
    h = h->next;
    if (!h) {t = NULL;}
    delete r;
    return i;
}

// ходы коня: 8 вариантов (move_row;move_col)
int move_row[] = {-2, -2, -1, -1, +1, +1, +2, +2};
int move_col[] = {-1, +1, -2, +2, -2, +2, -1, +1};

// из клетки (row;col) получаем номер от 0 до 63
int cell_to_number(int row, int col) {
    return row * 8 + col;
}

int get_row(int cell) {return cell / 8;}
int get_col(int cell) {return cell % 8;}

// перевод строки вида "LetterDigit" -> (row;col)
// буква = столбец (A=0 ... H=7), цифра = строка (1=0 ... 8=7)
void parse_cell(const string &s, int &row, int &col) {
    char letter = toupper(s[0]);
    char digit = s[1];
    col = letter - 'A';      // 'A' = 65 ... 'H' = 72        | A=0, B=1, ...
    row = digit  - '1';      // '1' = 49 ... '9' = 57        | 1=0, 2=1, ...
    return;
}

// перевод (row;col) в строку вида "A2"
string cell_to_str(int row, int col) {
    string s = "ab";
    s[0] = 'A' + col;
    s[1] = '1' + row;
    return s;
}


// восстанавливаем путь: идём от finish к start по массиву prev, используем стек для разворота
struct stack {
    int inf;
    stack *next;
};

void push_stack(stack *&h, int x) {
    stack *r = new stack;
    r->inf  = x;
    r->next = h;
    h = r;
}

int pop_stack(stack *&h) {
    int i = h->inf;
    stack *r = h;
    h = h->next;
    delete r;
    return i;
}


int main() {
    string start_str, end_str;
    cout << "Введите начальную клетку (например, A2): "; cin >> start_str;
    cout << "Введите конечную клетку (например, E6): "; cin >> end_str;
    int start_row, start_col, end_row, end_col;
    parse_cell(start_str, start_row, start_col);    
    parse_cell(end_str,   end_row,   end_col);     
    int start  = cell_to_number(start_row, start_col); 
    int finish = cell_to_number(end_row,   end_col);  
    if (start == finish) {
        cout << "Путь: " << cell_to_str(start_row, start_col) << endl;
        return 0;
    }

    // обход в ширину с помощью очереди
    int prev[64];          // prev[i] = откуда пришли в клетку i
    bool visited[64];      // посещена ли клетка
    for (int i = 0; i < 64; i++) {
        prev[i] = -1;
        visited[i] = false;
    }
    queue *head = NULL;
    queue *tail = NULL;
    visited[start] = true;
    push(head, tail, start);

    bool found = false;
    while (head) {                          // пока очередь не пуста
        int cur = pop(head, tail);
        int r = get_row(cur);
        int c = get_col(cur);
        for (int k = 0; k < 8; k++) {      // все 8 ходов коня
            int new_row = r + move_row[k];
            int new_col = c + move_col[k];
            if (new_row < 0 || new_row > 7 || new_col < 0 || new_col > 7) {continue;}  // вне доски
            int next = cell_to_number(new_row, new_col);
            if (!visited[next]) {
                visited[next] = true;
                prev[next] = cur;        // запоминаем, откуда пришли
                push(head, tail, next);
                if (next == finish) {       // нашли конечную клетку
                    found = true;
                    break;
                }
            }
        }
        if (found) {break;}
    }

    // освобождаем очередь если вышли раньше
    while (head) {
        pop(head, tail);
    }
    if (!found) {
        cout << "Путь не найден." << endl;
        return 0;
    }

    stack *path = NULL;
    int cur = finish;
    while (cur != -1) {
        push_stack(path, cur);
        cur = prev[cur];
    }

    cout << "\nКратчайший путь коня:" << endl;
    int step = 0;
    while (path) {
        int cell = pop_stack(path);
        cout << cell_to_str(get_row(cell), get_col(cell));
        if (path) cout << " -> ";
        ++step;
    }
    cout << endl;
    cout << "Количество ходов: " << step - 1 << endl;
    return 0;
}