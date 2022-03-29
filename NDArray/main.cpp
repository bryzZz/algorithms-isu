#include <iostream>
#include <ctime>

using namespace std;

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
            return NDArray<T>(this->shape, this->dimension, this->size, arr);
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

    int getDimension(){
        return this->dimension;
    }
    int* getShape(){
        return this->shape;
    }


    NDArray<T> flatten(){
        int _shape[1] = {this->size};
        return NDArray<T>(_shape, 1, this->size, this->_array);
    }
    
    NDArray<T> transposition(){
        int *newShape = new int[2]{this->shape[1], this->shape[0]};
        NDArray<T> current = NDArray<T>(this->shape, this->dimension, this->size, this->_array);
        T *newArr = new T[this->size];
        for(int i = 0; i < this->shape[1]; i++){
            for(int j = 0; j < this->shape[0]; j++){
                // result(i, j) = current(j, i);
                int index = i * newShape[1] + j;
                newArr[index] = current(j, i);
            }
        }

        return NDArray<T>(newShape, this->dimension, this->size, newArr);
    }
    NDArray<T> matMul(NDArray<T> other){
        if(
            this->dimension == 2
            && other.getDimension() == 2
            && this->shape[1] == other.getShape()[0]
        ){
            NDArray<T> otherT = other.transposition();
            int *newShape = new int[2]{this->shape[0], other.getShape()[1]};
            int newSize = newShape[0];
            for(int i = 1; i < this->dimension; i++){
                newSize *= newShape[i];
            }
            T *newArr = new T[newSize];
            NDArray<T> current = NDArray<T>(this->shape, this->dimension, this->size, this->_array);

            for(int i = 0; i < this->shape[0]; i++){
                for(int j = 0; j < this->shape[1]; j++){
                    NDArray<T> item = current(i) * otherT(j);
                    T sum = 0;
                    for(int k = 0; k < this->shape[1]; k++){
                        sum += item[k];
                    }
                    int index = i * newShape[1] + j;
                    newArr[index] = sum;
                }
            }

            return NDArray<T>(newShape, this->dimension, newSize, newArr);
        }

        throw runtime_error("Not supported");
    }

    T& operator[](unsigned index){
        if(this->dimension == 1){
            return this->_array[index];
        }

        throw runtime_error("Not supported");
    }
    NDArray<T> operator()(unsigned row){
        if(this->dimension == 2){
            int rowShape[1] = {this->shape[1]};
            // const T *rowArray = this->_array + index;
            return NDArray<T>(rowShape, 1, this->shape[1], this->_array + row * this->shape[1]);
        }

        throw runtime_error("Not supported");
    }
    T& operator()(unsigned row, unsigned col){
        if(this->dimension == 2){
            return this->_array[row * this->shape[1] + col];
        }

        throw runtime_error("Not supported");
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
        srand((unsigned) time(0));
        cout << "start " << start << " stop " << stop << endl;
        int *arr = new int[size];
        for(int i = 0; i < size; i++){
            arr[i] = start + (rand() % stop);
        }

        return NDArray<int>(shape, dimension, size, arr);
    }
};

int main(){
    int shape[1] = {6};
    int shape2[2] = {3, 3};
    int shape3[2] = {3, 3};
    int *arr = new int[6]{0, 1, 2, 3, 4, 5};
    NDArray<int> empty = NDArray<int>(shape, 1);
    NDArray<int> filled = NDArray<int>(shape, 1, 6, arr);
    NDArray<int> ones = NDArray<int>::ones(shape2, 2);
    NDArray<int> random = NDArray<int>::random(shape3, 2, 0, 10);
    NDArray<int> random2 = NDArray<int>::random(shape3, 2, 10, 20);

    // cout << "Empty array: " << empty << endl;
    // cout << "Filled: " << filled << endl;
    // cout << "Ones: " << ones << endl;
    // cout << "Random: " << random << endl;
    // cout << "Random2: " << random2 << endl;

    // cout << "Empty + Filled = " << empty + filled << endl;
    // cout << "Ones * Random = " << ones * random << endl;
    // cout << "Random1 - Random2 = " << random - random2 << endl;

    // cout << "Random1 transposition: " << random.transposition() << endl;
    // cout << "Random1 @ Random2 = " << random.matMul(random2) << endl;

    // cout << "filled third element: " << filled[2] << endl;
    // cout << "Random1 first row: " << random(0) << endl;
    // cout << "Random1 second row second element: " << random(1, 1) << endl;
    // cout << "Random1 second row second element(different method): " << random(1)[1] << endl;

    return 0;
}
