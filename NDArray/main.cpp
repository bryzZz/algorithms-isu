#include <iostream>
#include <ctime>
#include <math.h>

using namespace std;

template<class T> class NDArray{
    T *_array;
    int size;
    int *shape;
    int dimension;
    int step = 1;

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

    NDArray<T> reduction(int axis, string operation){
        if(this->dimension == 1){
            if(axis == 0){
                int *newShape = new int[1]{1};
                T *newArr = new T[1]{this->_array[0]};
                for (int i = 1; i < this->size; i++){
                    T currentElement = this->_array[i * this->step];
                    if(operation == "min"){
                        if(currentElement < newArr[0]){
                            newArr[0] = currentElement;
                        }
                    }else if(operation == "max"){
                        if(currentElement > newArr[0]){
                            newArr[0] = currentElement;
                        }
                    }else if(operation == "average"){
                        newArr[0] += currentElement;
                    }
                }
                if(operation == "average"){
                    newArr[0] = newArr[0] / this->size;
                }
                return NDArray<T>(newShape, this->dimension, 1, newArr);
            }else {
                throw runtime_error("This array has only one axis");
            }
        }else if(this->dimension == 2){
            if(axis == 0){
                int *newShape = new int[1]{this->shape[1]};
                T *newArr = new T[this->shape[1]];
                NDArray<T> currentT = this->transposition();

                for(int i = 0; i < currentT.getShape()[0]; i++){
                    NDArray<T> item = currentT(i);
                    T currentElement = item[0];
                    for(int j = 1; j < currentT.getShape()[1]; j++){
                        if(operation == "min"){
                            if(currentElement > item[j]){
                                currentElement = item[j];
                            }
                        }else if(operation == "max"){
                            if(currentElement < item[j]){
                                currentElement = item[j];
                            }
                        }else if(operation == "average"){
                            currentElement += item[j];
                        }
                    }
                    if(operation == "average"){
                        newArr[i] = currentElement / currentT.getShape()[1];
                    }else {
                        newArr[i] = currentElement;
                    }
                }

                return NDArray<T>(newShape, 1, this->shape[1], newArr);
            }else if(axis == 1){
                int *newShape = new int[1]{this->shape[0]};
                T *newArr = new T[this->shape[0]];
                NDArray<T> current = NDArray<T>(this->shape, this->dimension, this->size, this->_array, this->step);

                for(int i = 0; i < current.getShape()[0]; i++){
                    NDArray<T> item = current(i);
                    T currentElement = item[0];
                    for(int j = 1; j < current.getShape()[1]; j++){
                        if(operation == "min"){
                            if(currentElement > item[j]){
                                currentElement = item[j];
                            }
                        }else if(operation == "max"){
                            if(currentElement < item[j]){
                                currentElement = item[j];
                            }
                        }else if(operation == "average"){
                            currentElement += item[j];
                        }
                    }
                    if(operation == "average"){
                        newArr[i] = currentElement / current.getShape()[1];
                    }else {
                        newArr[i] = currentElement;
                    }
                }

                return NDArray<T>(newShape, 1, this->shape[0], newArr);
            }else {
                throw runtime_error("This array has only two axis");
            }
        }

        throw runtime_error("This dimension is not supported.");
    }
public:
    NDArray(int shape[], int dimension, T fill = 0) : shape(shape), dimension(dimension){
        // calculate inner array size
        this->size = shape[0];
        for(int i = 1; i < dimension; i++){
            this->size *= shape[i];
        }
        this->_array = (T *)malloc(this->size * sizeof(T));
        for(int i = 0; i < this->size; i++){
            this->_array[i] = fill;
        }
        this->step = 1;
    }
    NDArray(int shape[], int dimension, int size, T *_array, int step = 1){
        this->shape = shape;
        this->dimension = dimension;
        this->size = size;
        this->_array = _array;
        this->step = step;
    }

    int getDimension(){
        return this->dimension;
    }
    int* getShape(){
        return this->shape;
    }
    
    NDArray<T> transposition(){
        int *newShape = new int[2]{this->shape[1], this->shape[0]};
        NDArray<T> current = NDArray<T>(this->shape, this->dimension, this->size, this->_array, this->step);
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
            NDArray<T> current = NDArray<T>(this->shape, this->dimension, this->size, this->_array, this->step);

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

    NDArray<T> flatten(){
        int _shape[1] = {this->size};
        return NDArray<T>(_shape, 1, this->size, this->_array);
    }

    NDArray<T> slice(int start = 0, int stop = -1, int step = 1){
        // cout << "start " << start << " stop " << stop << " step " << step << endl;
        if(this->dimension == 1){
            // calculate stop
            stop = (stop == -1) ? this->size : stop;
            // define new size
            int newSize = ceil(((float)stop - (float)start) / (float)step);

            return NDArray<T>(this->shape, this->dimension, newSize, this->_array+start, step);
        }else if(this->dimension == 2){
            stop = (stop == -1) ? this->shape[0] : stop;
            int newRowsCount = ceil(((float)stop - (float)start) / (float)step);
            int *newShape = new int[2]{newRowsCount, this->shape[1]};
            int newSize = newRowsCount * this->shape[1];

            return NDArray<T>(newShape, this->dimension, newSize, this->_array+start*this->shape[1], step);
        }

        throw runtime_error("Not supported");
    }

    NDArray<T> min(int axis){
        return this->reduction(axis, "min");
    }
    NDArray<T> max(int axis){
        return this->reduction(axis, "max");
    }
    NDArray<T> average(int axis){
        return this->reduction(axis, "average");
    }
    
    T& operator[](unsigned index){
        if(this->dimension == 1){
            return this->_array[index * this->step];
        }

        throw runtime_error("Not supported");
    }
    NDArray<T> operator()(unsigned row){
        if(this->dimension == 2){
            int rowShape[1] = {this->shape[1]};
            return NDArray<T>(rowShape, 1, this->shape[1], this->_array + row * this->shape[1] * this->step);
        }

        throw runtime_error("Not supported");
    }
    T& operator()(unsigned row, unsigned col){
        if(this->dimension == 2){
            return this->_array[row * this->shape[1] * this->step + col];
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
                    out << arr._array[i * arr.step];
                }else{
                    out << arr._array[i * arr.step] << ", ";
                }
            }
            out << "]";
        }else if (arr.dimension == 2){
            out << "[\n";
            // rows iteration
            for(int i = 0; i < arr.shape[0]; i++){
                out << "    [";

                // calculate position with step
                int startRowIndex = (i * arr.shape[1]) * arr.step;
                int endRowIndex = startRowIndex + arr.shape[1];
                for(int j = startRowIndex; j < endRowIndex; j++){
                    out << arr._array[j];
                    // just pretty end of line
                    if(j != endRowIndex - 1){
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
    static NDArray<float> random(int shape[], int dimension, int start = 0, int stop = 1000){
        // calculate array size
        int size = shape[0];
        for(int i = 1; i < dimension; i++){
            size *= shape[i];
        }
        // initialize random array
        srand((unsigned) time(0));
        cout << "start " << start << " stop " << stop << endl;
        float *arr = new float[size];
        for(int i = 0; i < size; i++){
            arr[i] = start + (rand() % stop);
        }

        return NDArray<float>(shape, dimension, size, arr);
    }
};

int main(){
    int shape[1] = {6};
    int shape2[2] = {3, 5};
    int shape3[2] = {5, 3};
    float *arr = new float[6]{0, 1, 2, 3, 4, 5};
    NDArray<float> empty = NDArray<float>(shape, 1);
    NDArray<float> filled = NDArray<float>(shape, 1, 6, arr);
    NDArray<float> ones = NDArray<float>::ones(shape2, 2);
    NDArray<float> random = NDArray<float>::random(shape2, 2, 0, 10);
    NDArray<float> random2 = NDArray<float>::random(shape3, 2, 10, 20);

    cout << "Empty array: " << empty << endl;
    cout << "Filled: " << filled << endl;
    cout << "Ones: " << ones << endl;
    cout << "Random: " << random << endl;
    cout << "Random2: " << random2 << endl;

    cout << "Empty + Filled = " << empty + filled << endl;
    cout << "Ones * Random = " << ones * random << endl;
    cout << "Random - Ones = " << random - ones << endl;

    cout << "Random1 transposition: " << random.transposition() << endl;
    cout << "Random1 @ Random2 = " << random.matMul(random2) << endl;

    cout << "filled third element: " << filled[2] << endl;
    cout << "Random1 first row: " << random(0) << endl;
    cout << "Random1 second row second element: " << random(1, 1) << endl;
    cout << "Random1 second row second element(different method): " << random(1)[1] << endl;

    // Slices
    NDArray<float> filS = filled.slice(2, -1, 2);
    cout << "Filled slice: " << filS << endl;
    cout << "Change Filled slice[0] to 222" << endl;
    filS[1] = 222;
    cout << "Filled slice: " << filS << endl;
    cout << "Filled: " << filled << endl;

    NDArray<float> randomS = random.slice(0, -1, 2);
    NDArray<float> random2S = random2.slice(0, 5);
    cout << "randomS: " << randomS << endl;
    cout << "random2S: " << random2S << endl;
    cout << "randomS @ random2S: " << randomS.matMul(random2S) << endl;
    cout << "randomST: " << randomS.transposition() << endl;
    cout << "Change randomS(1, 2) to 666" << endl;
    randomS(1, 2) = 222;
    cout << "Random slice: " << randomS << endl;
    cout << "Random: " << random << endl;
    
    // Reduction
    cout << "Reduction Filled max: " << filled.max(0) << endl;
    cout << "Reduction Random min by 0 axis: " << random.min(0) << endl;
    cout << "Reduction Random average by 1 axis: " << random.average(1) << endl;

    return 0;
}
