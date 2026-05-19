#include <iostream>
#include <vector>
using namespace std;

struct stack {
    int inf;
    stack *next;
};

void push_s(stack *(&h), int x) {
    stack *r = new stack;
    r->inf = x;
    r->next = h;
    h = r;
}

int pop_s(stack *(&h)) {
    int i = h->inf;
    stack *r = h;
    h = h->next;
    delete r;
    return i;
}

struct queue {
    int inf;
    queue *next;
};

void push_q(queue *(&h), queue *(&t), int x) {
    queue *r = new queue;
    r->inf = x;
    r->next = NULL;
    if (!h && !t) {
        h = t = r;
    }
    else {
        t->next = r;
        t = r;
    }
}

int pop_q(queue *(&h), queue *(&t)) {
    queue *r = h;
    int i = h->inf;
    h = h->next;
    if (!h) {
        t = NULL;
    }
    delete r;
    return i;
}

// DFS (нерекурсивный, алгоритм 5)
// граф Gr - список смежности (вектор векторов)
// N - число вершин, start - начальная вершина
void dfs(const vector<vector<int>> &Gr, int N, int start) {
    cout << "\nОбход в глубину (DFS, нерекурсивный), начало с вершины " << start << endl;
    vector<int> A(N, 0);   // массив посещенных вершин (0 - не посещена)
    stack *h = NULL;      
    A[start] = 1;
    push_s(h, start);
    cout << start;

    while (h) {
        int x = h->inf;   // смотрим вершину на вершине стека (не извлекаем)
        bool fl = false;
        int y = -1;
        for (int i = 0; i < (int)Gr[x].size(); i++) {   // ищем смежную непосещенную вершину
            if (A[Gr[x][i]] == 0) {
                y = Gr[x][i];
                fl = true;
                break;
            }
        }
        if (fl) {   // нашли непосещенную, тогда помечаем и кладем в стек
            A[y] = 1;
            push_s(h, y);
            cout << ", " << y;
        } 
        else {   // нет смежных непосещенных, тогда извлекаем из стека
            pop_s(h);
        }
    }
    for (int v = 0; v < N; v++) {   // проверяем, остались ли непосещенные вершины (несвязный граф)
        if (A[v] == 0) {
            cout << endl;
            cout << "(Граф несвязный, продолжаем с вершины " << v << ")" << endl;
            cout << v;
            A[v] = 1;
            push_s(h, v);
            while (h) {
                int x = h->inf;
                bool fl = false;
                int y = -1;
                for (int i = 0; i < (int)Gr[x].size(); i++) {
                    if (A[Gr[x][i]] == 0) {
                        y = Gr[x][i];
                        fl = true;
                        break;
                    }
                }
                if (fl) {
                    A[y] = 1;
                    push_s(h, y);
                    cout << ", " << y;
                } 
                else {
                    pop_s(h);
                }
            }
        }
    }
    cout << endl;
}


// BFS (алгоритм 6)
void bfs(const vector<vector<int>> &Gr, int N, int start) {
    cout << "\nОбход в ширину (BFS), начало с вершины " << start << endl;
    vector<int> A(N, 0);
    queue *qh = NULL;
    queue *qt = NULL;
    A[start] = 1;
    push_q(qh, qt, start);
    cout << start;

    while (qh) {
        int x = pop_q(qh, qt);   // извлекаем голову очереди
        for (int i = 0; i < (int)Gr[x].size(); i++) {
            int neighbor = Gr[x][i];
            if (A[neighbor] == 0) {
                A[neighbor] = 1;
                push_q(qh, qt, neighbor);
                cout << ", " << neighbor;
            }
        }
    }

    // несвязный граф
    for (int v = 0; v < N; v++) {
        if (A[v] == 0) {
            cout << endl;
            cout << "(Граф несвязный, продолжаем с вершины " << v << ")" << endl;
            cout << v;
            A[v] = 1;
            push_q(qh, qt, v);
            while (qh) {
                int x = pop_q(qh, qt);
                for (int i = 0; i < (int)Gr[x].size(); i++) {
                    int neighbor = Gr[x][i];
                    if (A[neighbor] == 0) {
                        A[neighbor] = 1;
                        push_q(qh, qt, neighbor);
                        cout << ", " << neighbor;
                    }
                }
            }
        }
    }
    cout << endl;
}

int main() {
    cout << "Введите число вершин и ребер: ";
    int N, M; cin >> N >> M;
    vector<vector<int>> Gr(N);
    cout << "Введите ребра (пары вершин u v, нумерация с 0):" << endl;
    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        Gr[u].push_back(v);
        Gr[v].push_back(u);   // граф неориентированный
    }
    cout << "Введите начальную вершину обхода: ";
    int start; cin >> start;

    cout << "\nСписок смежности:" << endl;
    for (int i = 0; i < N; i++) {
        cout << i << " -> ";
        for (int j = 0; j < (int)Gr[i].size(); j++) {
            cout << Gr[i][j] << " -> ";
        }
        cout << "NULL" << endl;
    }
    dfs(Gr, N, start);
    bfs(Gr, N, start);

    return 0;
}