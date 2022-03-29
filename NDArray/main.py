import array
from dataclasses import field
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
        else:
            assert len(fill) == self.size
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
                return NDArray(len(values), fill=values)
            else:
                index = self._flatten_indexes(indexes)
                return self._array[index]
        else:
            if isinstance(indexes, int):
                start = indexes * self.shape[1]
                stop = start + self.shape[1]
                values = self._array[start:stop:1]
                return NDArray(len(values), fill=values)
                # return NDArray(self.shape, fill=)
            elif isinstance(indexes, slice):
                rows = []
                c = 0
                start = indexes.start
                stop = indexes.stop
                step = indexes.step
                if start is None:
                    start = 0
                if stop is None:
                    stop = self.shape[0]
                if step is None:
                    step = 1
                for i in range(start, stop, step):
                    rows.extend(self[i])
                    c += 1
                return NDArray((c, self.shape[1]), fill=rows)
            elif len(indexes) == 2:
                if isinstance(indexes[0], int) and isinstance(indexes[1], int):
                    return self[indexes[0]][indexes[1]]
                elif isinstance(indexes[0], slice) and isinstance(indexes[1], int):
                    rows = self[indexes[0]]
                    values = []
                    for row in rows:
                        values.append(row[indexes[1]])
                    return NDArray(rows.shape[0], fill=values)

    def __iter__(self):
        for i in range(self.shape[0]):
            yield self[i]

    def __setitem__(self, indexes, value):
        index = self._flatten_indexes(indexes)
        self._array[index] = value

    def _flatten_indexes(self, indexes):
        if self.ndim == 1:
            return indexes
        if self.ndim == 2:
            return indexes[0] * self.shape[1] + indexes[1]

    def __element_wise_operator(self, other, operator):
        if self.shape != other.shape:
            raise RuntimeError(f"{self.shape} != {other.shape}")
        result = NDArray(self.shape, self._array.typecode)
        with self as a1, other as a2, result as a3:
            for i in range(self.size):
                a3[i] = operator(a1[i], a2[i])
        return result

    def __add__(self, other):
        return self.__element_wise_operator(other, lambda a, b: a + b)

    def __sub__(self, other):
        ...

    def __mul__(self, other):
        return self.__element_wise_operator(other, lambda a, b: a * b)

    def __truediv__(self, other):
        ...

    def T(self):
        result = NDArray((self.shape[1], self.shape[0]), self._array.typecode)
        for i in range(self.shape[1]):
            for j in range(self.shape[0]):
                result[i, j] = self[j, i]
        return result

    def __matmul__(self, other):
        assert self.ndim == 2 and other.ndim == 2
        assert self.shape[0] == other.shape[1]
        assert self.shape[1] == other.shape[0]

        result = NDArray((self.shape[0], self.shape[0]), self._array.typecode)
        otherT = other.T()
        for i in range(self.shape[0]):
            for j in range(self.shape[0]):
                result[i, j] = sum(self[i] * otherT[j])
        return result

    def __enter__(self):
        self._shape = self.shape
        self.shape = [self.size]
        return self

    def __exit__(self, *args):
        self.shape = self._shape

    def flatten(self):
        return self._array

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
    arr = NDArray((3, 3), fill=[1, 2, 3, 4, 5, 6, 7, 8, 9])
    brr = NDArray((3, 3), fill=[1, 2, 3, 4, 5, 6, 7, 8, 9])
    # print(arr[:, 0])
    print(arr @ brr)
    # print(arr[0])
    # print(brr)
    # print(brr.T())
    # print(arr.T())
    # arr.T()
    # for i, row in enumerate(arr):
    #    print(f"row {i}: {row}")
