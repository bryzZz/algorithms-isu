import array
import math
from collections.abc import Iterable

class NDArray():
    def __init__(self, shape, type_='i', fill=0):
        if not isinstance(shape, Iterable):
            shape = [shape]
        self.shape = shape
        self.size = math.prod(shape)
        if isinstance(fill, (int, float, complex)):
            fill = [fill] * self.size
        self._array = array.array(type_, fill)

    @classmethod
    def ones(cls, shape, type_='i'):
        return cls(shape, type_, fill=1)

    @property
    def ndim(self):
        return len(self.shape)

    def __getitem__(self, indexes):
        if self.ndim == 1:
            if isinstance(indexes, slice):
                values = self._array[indexes]
                return NDArray(shape = len(values), type_=self._array.typecode, fill=values)
            else:
                index = self._flatten_indexes(indexes)
                return self._array[index]
        elif self.ndim == 2:
            if isinstance(indexes, int):
                start = indexes * self.shape[1]
                stop = start + self.shape[1]
                return self[start:stop:1]
            elif isinstance(indexes, slice):
                rows = []
                print(indexes)
                shape1 = 0
                for i in range(indexes.start, indexes.stop, indexes.step):
                    rows.extend(self._array[i])
                    shape1 += 1
                return NDArray((shape1, self.shape[1]), self._array.typecode, rows)
            elif len(indexes) == 2:
                pass
        

    def __setitem__(self, indexes, value):
        index = self._flatten_indexes(indexes)
        self._array[index] = value

    def _flatten_indexes(self, indexes):
        if self.ndim == 1:
            return indexes
        if self.ndim == 2:
            return indexes[0] * self.shape[1] + indexes[1]
    
    def _element_wise_operator(self, other, operator):
        if self.shape != other.shape:
            raise RuntimeError(f"{self.shape} != {other.shape}")
        result = NDArray(self.shape, self._array.typecode)
        with self as a1, other as a2, result as a3:
            for i in range(self.size):
                a3[i] = operator(a1[i], a2[i])
        return result

    def __add__(self, other):
        return self._element_wise_operator(other, lambda a, b: a + b)

    def __sub__(self, other):
        return self._element_wise_operator(other, lambda a, b: a - b)

    def __mul__(self, other):
        return self._element_wise_operator(other, lambda a, b: a * b)

    def __div__(self, other):
        return self._element_wise_operator(other, lambda a, b: a // b)

    def __truediv__(self, other):
        return self.__div__(other)

    def __radd__(self, other):
        ...
    
    def __matmul__(self, other):
        assert self.ndim == 2 and other.ndim == 2
        assert self.shape[1] and other.shape[0]

        result = NDArray(self.shape, self._array.typecode)

    def flatten(self):
        return self._array
    
    def __enter__(self):
        self._shape = self.shape
        self.shape = [self.size]
        return self
    
    def __exit__(self, *args):
        self.shape = self._shape

    def __str__(self):
        shape = None
        if self.ndim == 1:
            shape = [1, ] + self.shape
        elif self.ndim == 2:
            shape = self.shape
        else:
            raise RuntimeError("Not supported")
        s = []
        for i in range(shape[0]):
            row = self._array[i * shape[1]: 
                                i * shape[1]+shape[1]]
            s.append(" ".join(map(str, row)))
        return "\n".join(s)

if __name__ == "__main__":
    arr = NDArray.ones((10, 10))
    
    # for i in range(arr.size):
    #     arr[i] = i

    print(arr[1])