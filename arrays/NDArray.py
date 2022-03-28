import array
import math
from collections.abc import Iterable
from msilib.schema import Error

class NDArray:
    def __init__(self, shape, type_ = 'i', fill = 0):
        if not isinstance(shape, Iterable):
            shape = [shape]
        self.shape = shape
        self.size = math.prod(shape)
        self._array = array.array(type_, [fill] * self.size)

    @staticmethod
    def ones(shape, type_='i'):
        return NDArray(shape, type_, fill=1)
    
    @property
    def ndim(self):
        return len(self.shape)

    def __str__(self) -> str:
        if self.ndim == 1:
            return self._array.__str__()
        elif self.ndim == 2:
            s = []
            
            for i in range(self.shape[0]):
                row = self._array[i * self.shape[1] : i * self.shape[1]+self.shape[1]]
                s.append(" ".join(map(str, row)))

            return "\n".join(s)

    def __getitem__(self, indexes):
        return self._array[self._flattenIndex(indexes)]
    
    def __setitem__(self, indexes, value):
        self._array[self._flattenIndex(indexes)] = value
    
    def _flattenIndex(self, indexes):
        if self.ndim == 1:
            return indexes
        elif self.ndim == 2:
            return indexes[0] * self.shape[1] + indexes[1]
    
    def __add__(self, other):
        if self.shape != other.shape:
            raise Error()


if __name__ == '__main__':
    arr1 = NDArray(10)
    arr1[3] = 22
    arr2 = NDArray((2, 2))
    arr2[0, 0] = 1
    arr2[0, 1] = 2
    arr2[1, 0] = 3
    arr2[1, 1] = 4

    print(arr1)
    print(arr2)
    print(arr2[0, 1])