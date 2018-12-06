template <class VertexT, class WeightT, class DataT>

class Edge {
    VertexT *v1, *v2; //Вершины, которые соединяет ребро
    WeightT weight; //Вес
    DataT data; //Данные ребра
    bool weightSet, dataSet;//признаки установки веса и данных
public:
    Edge(VertexT *v1, VertexT *v2); //Ребро с неустановленным весом и данными
    Edge(VertexT *v1, VertexT *v2, WeightT weight); //Ребро с установленным весом
    Edge(VertexT *v1, VertexT *v2, WeightT weight, DataT data);//Ребро с установленными весом и данными
    void setWeight(WeightT weight); //Установка веса
    void setData(DataT data); //Установка данных
    WeightT getWeight(); //Получение веса
    DataT getData(); //Получение данных
    bool isWeightSet(); //Установленность веса
    bool isDataSet(); //Установленность данных
    VertexT* getVertex1(); //получение дескриптора исх. вершины
    VertexT* getVertex2();//получение дескриптора вх. вершины
};

//Конструкторы
template <class VertexT, class WeightT, class DataT>
Edge<VertexT, WeightT, DataT>::Edge(VertexT *v1, VertexT *v2){
    v1(v1);
    v2(v2);
    weightSet(false);
    weight(0);
    dataSet(false);
}

template <class VertexT, class WeightT, class DataT>
Edge<VertexT, WeightT, DataT>::Edge(VertexT *v1, VertexT *v2, WeightT weight){
    v1(v1);
    v2(v2);
    weight(weight);
    weightSet(true);
    dataSet(false);
}

template <class VertexT, class WeightT, class DataT>
Edge<VertexT, WeightT, DataT>::Edge(VertexT *v1, VertexT *v2, WeightT weight, DataT data){
    v1(v1);
    v2(v2);
    weight(weight);
    data(data);
    weightSet(true);
    dataSet(true);
}

//Установка и получение веса и данных
template <class VertexT, class WeightT, class DataT>
void Edge<VertexT, WeightT, DataT>::setWeight(WeightT weight){
    this->weight = weight;
    weightSet = true;
}

template <class VertexT, class WeightT, class DataT>
void Edge<VertexT, WeightT, DataT>::setData(DataT data){
    this->data = data;
    dataSet = true;
}

template <class VertexT, class WeightT, class DataT>
WeightT Edge<VertexT, WeightT, DataT>::getWeight(){
    return weight;
}

template <class VertexT, class WeightT, class DataT>
DataT Edge<VertexT, WeightT, DataT>::getData(){
    return data;
}

template <class VertexT, class WeightT, class DataT>
VertexT* Edge<VertexT, WeightT, DataT>::getVertex1(){
    return v1;
}

template <class VertexT, class WeightT, class DataT>
VertexT* Edge<VertexT, WeightT, DataT>::getVertex2(){
    return v2;
}

template <class VertexT, class WeightT, class DataT>
bool Edge<VertexT, WeightT, DataT>::isWeightSet(){
    return weightSet;
}

template <class VertexT, class WeightT, class DataT>
bool Edge<VertexT, WeightT, DataT>::isDataSet(){
    return dataSet;
}