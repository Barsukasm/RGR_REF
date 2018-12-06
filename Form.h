#include <vector>
#include <list>


using namespace std;
//форма представления
template <class EdgeT> class GraphForm {
public:
//Вставка и удаление вершин и рёбер
    virtual bool InsertV(int index) = 0;
    virtual bool DeleteV(int index) = 0;
    virtual bool InsertE(int v1, int v2, EdgeT *t) = 0;
    virtual bool DeleteE(int v1, int v2);
//Удалить входящие и исходящие из вершины рёбра
    virtual int DeleteEsFromVertex(int index, bool directed) = 0;
//Проверка и получение
    virtual bool hasEdge(int v1, int v2) = 0;
    virtual EdgeT* getEdge(int v1, int v2) = 0;
};

//форма представления матричная
template <class EdgeT> class GraphMatrixForm : public GraphForm < EdgeT >{
    friend class EdgeIterator;
    bool directed;
public:
    vector<vector<EdgeT*>> matrix; //Матрица смежности
    vector<vector<EdgeT*>> matrix_tmp1; //temp Матрица смежности
    vector<vector<EdgeT*>> matrix_tmp2; //temp Матрица смежности

    GraphMatrixForm(bool directed) : directed(directed) {}
    //Вставка и удаление вершин и рёбер
    bool InsertV(int index) {
        int size = matrix.size(); //Число вершин
        //Неверный номер вершины
        if (index < 0 || index > size) return false;
        //Создаём новую пустую строку
        vector<EdgeT*> newLine;
        newLine.assign(size, NULL);
        //Вставляем новую строку:
        matrix.insert(matrix.begin() + index, newLine);
        ++size;
        //Вставляем новый столбец:
        for (int i = 0; i < size; ++i)
            matrix[i].insert(matrix[i].begin() + index, (EdgeT*)NULL);
        return true;
    }

    bool DeleteV(int index)
    {
        int size = matrix.size(); //Число вершин
        //Неверный номер вершины
        if (index < 0 || index >= size)
            return false;
        //Удаляем строку:
        matrix.erase(matrix.begin() + index);
        --size;
        //Удаляем столбец:
        for (int i = 0; i < size; i++)
            matrix[i].erase(matrix[i].begin() + index);
        return true;
    }

    bool InsertE(int v1, int v2, EdgeT *t){
        int size = matrix.size(); //Число вершин
        //Неверный номер вершины
        if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size) return false;
        //Петля или ребро уже есть
        if (v1 == v2 || matrix[v1][v2] != NULL) return false;
        //Вставляем ребро
        matrix[v1][v2] = t;
        return true;
    }

    bool DeleteE(int v1, int v2){
        int size = matrix.size(); //Число вершин
        //Неверный номер вершины
        if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size) return false;
        //Ребра нет
        if (v1 == v2 || matrix[v1][v2] == NULL) return false;
        matrix[v1][v2] = NULL;
        return true;
    }

    //Удалить входящие и исходящие из вершины рёбра
    int DeleteEsFromVertex(int index, bool directed){
        int size = matrix.size(); //Число вершин
        int deleted = 0;
        //Неверный номер вершины
        if (index < 0 || index >= size) return 0;
        //Удаляем связанные с вершиной рёбра
        for (int i = 0; i < size; i++) {
            if (matrix[i][index] != NULL) {
                delete matrix[i][index];
                matrix[i][index] = NULL;
                ++deleted;
                //Стираем симметричное ребро
                if (directed == false)
                    matrix[index][i] = NULL;
            }
            if (matrix[index][i] != NULL) {
                delete matrix[index][i];
                matrix[index][i] = NULL;
                ++deleted;
            }
        }
        return deleted;
    }

    //Проверка и получение
    bool hasEdge(int v1, int v2){
        int size = matrix.size(); //Число вершин
        //Неверный номер вершины
        if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size)
            return false;
        if (v1 == v2) //Петля
            return false;
        if (matrix[v1][v2] != NULL)
            return true;
        return false;

    }

    EdgeT* getEdge(int v1, int v2){
        int size = matrix.size(); //Число вершин
        //Неверный номер вершины
        if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size)
            throw 1;
        if (v1 == v2 || matrix[v1][v2] == NULL)//Петля
            throw 1;
        return matrix[v1][v2];

    }

};

//форма представления список
template <class EdgeT> class GraphListForm : public GraphForm < EdgeT > {
    //Элемент списка
    class Node{
    public:
        EdgeT *edge; //Само ребро
        int v2; //Вторая вершина, которую ребро соединяет
    };

    bool directed;
    vector<list<Node>> edgeList; //Списки смежности

public:

    GraphListForm(bool directed) : directed(directed) {}

    //Вставка и удаление вершин и рёбер
    bool InsertV(int index){
        int size = edgeList.size(); //Число вершин
        if (index < 0 || index > size) //Неверный номер вершины
            return false;
        //Создаём новый список смежности
        list<Node> newList;
        //Вставляем
        edgeList.insert(edgeList.begin() + index, newList);
        ++size;
        //Обновляем дескрипторы
        for (int i = 0; i < size; ++i)
            for (typename list<Node>::iterator j = edgeList[i].begin(); j != edgeList[i].end(); ++j)
                if ((*j).v2 >= index)//если текущая вершина имеет больший номер, чем вставляемая,
                    ++((*j).v2);//то увеличиваем этот номер
        return true;
    }

    bool DeleteV(int index){
        int size = edgeList.size(); //Число вершин
        if (index < 0 || index >= size) //Неверный номер вершины
            return false;
        //Удаляем из списков записи о рёбрах
        for (int i = 0; i < size; ++i)
            for (typename list<Node>::iterator j = edgeList[i].begin(); j != edgeList[i].end(); ++j)
                if ((*j).v2 == index){
                    edgeList[i].erase(j);
                    break;
                }
        //Удаляем список смежности
        edgeList.erase(edgeList.begin() + index);//
        --size;//
        //Обновляем дескрипторы
        for (int i = 0; i < size; ++i)//
            for (typename list<Node>::iterator j = edgeList[i].begin(); j != edgeList[i].end(); ++j)//
                if ((*j).v2 > index)//если текущая вершина имеет больший номер, чем удаляемая,//
                    --((*j).v2);//то уменьшить этот номер//
        return true;
    }

    bool InsertE(int v1, int v2, EdgeT *t){
        int size = edgeList.size(); //Число вершин
        if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size)//Неверный номер вершины
            return false;
        if (v1 == v2 || hasEdge(v1, v2)) //Петля или ребро уже есть
            return false;
        //Вставляем ребро
        Node node;
        node.edge = t;
        node.v2 = v2;
        edgeList[v1].push_front(node);
        return true;
    }

    bool DeleteE(int v1, int v2){
        int size = edgeList.size(); //Число вершин
        //Неверный номер вершины
        if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size)
            return false;
        //Ребра нет
        if (v1 == v2 || hasEdge(v1, v2) == false)
            return false;
        //Удаляем ребро
        for (typename list<Node>::iterator j = edgeList[v1].begin(); j != edgeList[v1].end(); ++j)
            if ((*j).v2 == v2) {
                edgeList[v1].erase(j);
                break;
            }
        return true;
    }

    //Удалить входящие и исходящие из вершины рёбра
    int DeleteEsFromVertex(int index, bool directed){
        int size = edgeList.size(); //Число вершин
        int deleted = 0;
        //Неверный номер вершины
        if (index < 0 || index >= size)
            return 0;
        //Удаляем связанные с вершиной рёбра
        for (int i = 0; i < size; ++i)
            for (typename list<Node>::iterator j = edgeList[i].begin(); j != edgeList[i].end(); ++j)
                if ((*j).v2 == index){
                //Стираем симметричное ребро
                    if (!directed)
                        for (typename list<Node>::iterator k = edgeList[index].begin(); k != edgeList[index].end(); ++k)
                            if ((*k).v2 == i){
                                edgeList[index].erase(k);
                                break;
                            }
                    delete (*j).edge;
                    edgeList[i].erase(j);
                    ++deleted;
                    break;
                }
        return deleted;
    }

    //Проверка и получение
    bool hasEdge(int v1, int v2){
        int size = edgeList.size(); //Число вершин
        //Неверный номер вершины
        if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size)
            return false;

        //Петля
        if (v1 == v2)
            return false;
        for (typename list<Node>::iterator j = edgeList[v1].begin(); j != edgeList[v1].end(); ++j)
            if ((*j).v2 == v2)
                return true;
        return false;
    }

    EdgeT* getEdge(int v1, int v2){
        int size = edgeList.size(); //Число вершин
        //Неверный номер вершины
        if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size)
            throw 1;
        //Петля
        if (v1 == v2)
            throw 1;
        for (typename list<Node>::iterator j = edgeList[v1].begin(); j != edgeList[v1].end(); ++j)
            if ((*j).v2 == v2)
                return (*j).edge;
        throw 1;
    }
};