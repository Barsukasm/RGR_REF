template<class NameT, class DataT>
class Vertex {
    NameT name; //Имя вершины

    DataT data; //Данные вершины

    bool nameSet, dataSet;//признаки установки имени и данных

public:
    Vertex(); //Конструктор пустой вершины

    Vertex(NameT name, DataT data);//Конструктор с параметрами имени и данных

    void setName(NameT name); //Установка имени

    void setData(DataT data); //Установка данных

    NameT getName(); //Получение имени

    DataT getData(); //Получение данных

    bool isNameSet(); //Проверка установленности имени

    bool isDataSet(); //Проверка установленности данных

};

//Конструкторы

template<class NameT, class DataT>
Vertex<NameT, DataT>::Vertex(): nameSet(false), dataSet(false) {}

template<class NameT, class DataT>
Vertex<NameT, DataT>::Vertex(NameT name, DataT data):

        name(name),
        data(data),
        nameSet(true),
        dataSet(true) {}

//Установка, получение имени и данных

template<class NameT, class DataT>
void Vertex<NameT, DataT>::setName(NameT name) {
    this->name = name;
    nameSet = true;
}

template<class NameT, class DataT>
void Vertex<NameT, DataT>::setData(DataT data) {
    this->data = data;
    dataSet = true;
}

template<class NameT, class DataT>
NameT Vertex<NameT, DataT>::getName() {
    return name;
}

template<class NameT, class DataT>
DataT Vertex<NameT, DataT>::getData() {
    return data;
}

template<class NameT, class DataT>
bool Vertex<NameT, DataT>::isNameSet() {
    return nameSet;
}

template<class NameT, class DataT>
bool Vertex<NameT, DataT>::isDataSet() {
    return dataSet;
}