#include <iostream>

using namespace std;

struct Array{
    int *A;
    int size;
    int length;

    void create(int size){
        A = (int *) malloc(size * sizeof(int));
        length = 0;
    }

    void display(){
        for(int i = 0; i < length; i++){
            cout << A[i] << ", ";
        }
        cout << endl;
    }

    void append(int value){
        if(length < size){
            A[length++] = value;
        }
    }

    void insert(int index, int value){
        if(index >= 0 & index < length){
            for(int i = length; i > index; i--){
                A[i] = A[i-1];
            }
            A[index] = value;
            length++;
        }
    }

    int del(int index){
        int x = -1;
        if(index >= 0 & index < length){
            x = A[index];

            for(int i = index; i < length -1; i++){
                A[i] = A[i+1];
            }

            length--;
        }

        return x;
    }

    int find_transposition(int value){
        for(int i = 0; i < length; i++){
            if(A[i] == value){
                swap(A[i], A[0]);
                return i;
            }
        }
    }

    int bin_search(int value){
        int low = 0, mid, hight = length-1;
        while(low < hight){
            mid = low + hight / 2;

            if(A[mid] == value){
                return mid;
            }else if (value < A[mid]){
                hight = mid -1;
            }else {
                low = mid + 1;
            }
        }

        return -1;
    }

    void sort(){
        for(int i = 0; i < length-1; i++){
            for(int j = 0; j < length-i-1; j++){
                if(A[j] > A[j+1]){
                    swap(A[j], A[j+1]);
                }
            }
        }
    }

    int max(){
        int max = A[0];

        for(int i = 1; i < length; i++){
            if(A[i] > max){
                max = A[i];
            }
        }

        return max;
    }

    int sum(){
        int sum = 0;

        for(int i = 0; i < length; i++){
            sum += A[i];
        }

        return sum;
    }

    float mean(){
        return (float)sum() / length;
    }

    void reverse(){
        int *B = (int*)malloc(length + sizeof(int));
        int i, j;

        for(i = length-1, j >= 0; i > 0; i--, j++){
            B[j] = A[i];
        }

        for(i = 0; i < length; i++){
            A[i] = B[i];
        }
    }

    void reverse2(){
        int i, j
        ;
        for(i = 0, j = length-1; i < j; i++, j--){
            swap(A[i], A[j]);
        }
    }

    void reverse(int start, int end){
        for(int i = start; i < end; i++){
            swap(A[i], A[end-start-i]);
        }
    }

    void insert_sorted(int value){
        if(length == size) return;

        int i;
        for(i = length-1; i >= 0 && A[i] > value; i--){
            A[i+1] = A[i];
        }

        A[i+1] = value;
        length++;
    }

    void roll(int n){
        reverse(0, length-1);
        reverse(0, n-1);
        reverse(n, length-1);
    }

    Array union_op(Array other){
        int i, j, k;
        i = j = k = 0;

        Array result;
        result.create(length + other.length);

        while(i < length && j < other.length){
            if(A[i] < other.A[j]){
                result.A[k++] = A[i++];
            } else if(other.A[i] < A[j]){
                result.A[k++] = other.A[j++];
            } else {
                result.A[k++] = A[i++];
                j++;
            }
        }

        for(; i < length; i++){
            result.A[k++] = A[i];
        }
        for(; j < other.length; j++){
            result.A[k++] = other.A[j];
        }

        result.length = k;
        return result;
    }

    Array intersection_op(Array other){
        int i, j, k;
        i = j = k = 0;

        Array result;
        result.create(length + other.length);

        while(i < length && j < other.length){
            if(A[i] < other.A[j]){
                i++;
            } else if(other.A[i] < A[j]){
                j++;
            } else {
                result.A[k++] = other.A[j++];
                i++;
            }
        }

        result.length = k;
        return result;
    }

    Array difference_op(Array other){
        int i, j, k;
        i = j = k = 0;

        Array result;
        result.create(length + other.length);

        while(i < length && j < other.length){
            if(A[i] < other.A[j]){
                result.A[k++] = A[i++];
                i++;
            } else if(other.A[i] < A[j]){
                j++;
            } else {
                result.A[k++] = other.A[j++];
            }

            if(A[i] != other.A[j]){
                result.A[k++] = A[i++];
                j++;
            }else{
                
            }
        }

        result.length = k;
        return result;
    }
};


int main(){
    int raw_array[6] = {1, 2, 3, 4, 5, 6};
    int raw_array2[5] = {4, 5, 6, 7, 8};
    Array arr = {raw_array, 20, 6};
    Array arr2 = {raw_array2, 20, 5};
    
    arr.display();
    arr2.display();
    Array arr3 = arr.union_op(arr2);
    arr3.display();

    return 0;
}