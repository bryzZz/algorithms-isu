#include <iostream>
#include <ctime>

using namespace std;

struct NDArrayIndexes{
    int start;
    int end;
    int step;

    NDArrayIndexes(int start, int end, int step){
        this->start = start;
        this->end = end;
        this->step = step;
    }
};

template<class T> class NDArray{
    T *_array;
    int size;
    int *shape;
    int dimension;

    bool isShapeEqualToThis(NDArray<T> other){
        if(this->dimension != other.getDimension()){
            return false;
        }

        int* otherShape = other.getShape();
        for(int i = 0; i < this->dimension; i++){
            if(this->shape[i] != otherShape[i]){
                return false;
            }
        }

        return true;
    }
    
    NDArray<T> element_wise_operator(NDArray<T> other, string operation){
        if(this->isShapeEqualToThis(other)){
            T *arr = new T[this->size];
            for(int i = 0; i < this->size; i++){
                NDArray<T> otherFlatten = other.flatten();
                if(operation == "add"){
                    arr[i] = this->_array[i] + otherFlatten[i];
                }else if(operation == "sub"){
                    arr[i] = this->_array[i] - otherFlatten[i];
                }else if(operation == "mul"){
                    arr[i] = this->_array[i] * otherFlatten[i];
                }else if(operation == "div"){
                    arr[i] = this->_array[i] / otherFlatten[i];
                }
            }
            return NDArray<int>(this->shape, this->dimension, this->size, arr);
        }else {
            throw runtime_error("Arrays shapes are not equal");
        }
    }
public:
    NDArray(int shape[], int dimension, T fill = 0){
        this->shape = shape;
        this->dimension = dimension;
        // calculate inner array size
        this->size = shape[0];
        for(int i = 1; i < dimension; i++){
            this->size *= shape[i];
        }
        this->_array = (T *)malloc(this->size * sizeof(T));
        for(int i = 0; i < this->size; i++){
            this->_array[i] = fill;
        }
    }
    NDArray(int shape[], int dimension, int size, T *_array){
        this->shape = shape;
        this->dimension = dimension;
        this->size = size;
        this->_array = (T *)malloc(this->size * sizeof(T));
        this->_array = _array;
    }

    NDArray<T> flatten(){
        int _shape[1] = {this->size};
        return NDArray<T>(_shape, 1, this->size, this->_array);
    }
    
    NDArray<T> matMul(NDArray<T> other){
        if(
            this->dimension == 2
            && other.getDimension() == 2
            && this->shape[0] == other.getShape()[1]
            && this->shape[1] == other.getShape()[0]
        ){
            int minSide = (this->shape[0] > this->shape[1]) ? this->shape[1] : this->shape[0];
            int newShape[2] = {minSide, minSide};
            
            for(int i = 0; i < this->size; i++){

            }
        }
    }

    NDArray<T> slice(NDArrayIndexes indexes){
        // if(this->dimension == 1){
            cout << indexes.start << indexes.step << indexes.end;
        // }
    }

    int getDimension(){
        return this->dimension;
    }
    int* getShape(){
        return this->shape;
    }

    T& operator[](int index){
        if(this->dimension == 1){
            return this->_array[index];
        }else if(this->dimension == 2) {
            // return NDArray<T>(this->size, this->_array);
        }
        return this->_array[index];
    }

    NDArray<T> operator+(NDArray<T> other) {
        return this->element_wise_operator(other, "add");
    }
    NDArray<T> operator-(NDArray<T> other) {
        return this->element_wise_operator(other, "sub");
    }
    NDArray<T> operator*(NDArray<T> other) {
        return this->element_wise_operator(other, "mul");
    }
    NDArray<T> operator/(NDArray<T> other) {
        return this->element_wise_operator(other, "div");
    }

    friend ostream& operator<<(ostream &out, const NDArray& arr){
        if(arr.dimension == 1){
            out << "[";
            for (int i = 0; i < arr.size; i++){
                if(i == arr.size - 1){
                    out << arr._array[i];
                }else{
                    out << arr._array[i] << ", ";
                }
            }
            out << "]";
        }else if (arr.dimension == 2){
            out << "[\n";
            // rows iteration
            for(int i = 0; i < arr.shape[0]; i++){
                out << "    [";
                // columns iterations
                for(int j = i*arr.shape[1]; j < i*arr.shape[1]+arr.shape[1]; j++){
                    out << arr._array[j];
                    // just pretty end of line
                    if(j != i*arr.shape[1]+arr.shape[1]-1){
                        out << ", ";
                    }
                }
                // just pretty end of line
                string innerEnd = (i != arr.shape[0]-1) ? "],\n" : "]\n";
                out << innerEnd;
            }
            out << "]";
        }else {
            throw runtime_error("Not supported");
        }
        
        return out;
    }

    static NDArray<T> ones(int shape[], int dimension){
        return NDArray<T>(shape, dimension, 1);
    }
    static NDArray<T> zeros(int shape[], int dimension){
        return NDArray<T>(shape, dimension, 0);
    }
    static NDArray<int> random(int shape[], int dimension, int start = 0, int stop = 1000){
        // calculate array size
        int size = shape[0];
        for(int i = 1; i < dimension; i++){
            size *= shape[i];
        }
        // initialize random array
        srand((unsigned)time(0)); 
        int *arr = new int[size];
        for(int i = 0; i < size; i++){
            arr[i] = (rand() % stop)+start;
        }

        return NDArray<int>(shape, dimension, size, arr);
    }
};

int main(){
    int dimension = 2;
    int shape[dimension] = {3, 3};
    int shape2[dimension] = {3, 3};
    // NDArray<int> ones = NDArray<int>::ones(shape, dimension);
    NDArray<int> zeros = NDArray<int>::zeros(shape2, dimension);
    NDArray<int> random = NDArray<int>::random(shape, dimension);

    random.slice(NDArrayIndexes(1, 2, 3));

    // ones.matMul(zeros);

    // cout << "ones: " << ones << endl;

    // NDArray<int> flat = zeros.flatten();
    // flat[3] = 666;

    // cout << "zeros: " << zeros << endl;
    // cout << "random: " << random << endl;

    // NDArray<int> sum = random + zeros;
    // cout << "sum: " << sum << endl;

    return 0;
}
