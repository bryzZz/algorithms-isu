# def follow(y, x, arr, result=True, prevY = None, prevX = None):
#     print(y, x)

#     if arr[y-1][x] != '0' and y-1 != prevY and x != prevX:
#         result = follow(y-1, x, arr, result, y, x)
#     elif arr[y+1][x] != '0' and y+1 != prevY and x != prevX:
#         result = follow(y+1, x, arr, result, y, x)
#     elif arr[y][x-1] != '0' and y != prevY and x-1 != prevX:
#         result = follow(y, x-1, arr, result, y, x)
#     elif arr[y][x+1] != '0' and y != prevY and x+1 != prevX:
#         result = follow(y, x+1, arr, result, y, x)
#     else:
#         result = False

#     return result


def follow(matrix, startPos, currentPos=None):
    for offset in [[-1, 0], [0, 1], [1, 0], [0, -1]]:
        y = startPos[0] + offset[0]
        x = startPos[1] + offset[1]
        if(matrix[y][x] != '0'):
            print(matrix[y][x])
            follow(matrix, [y, x])
            break

def isClosedFigure(matrix, startPos):
    return follow(matrix, startPos)

with open('./inp2.csv', 'r') as f:
    arr = f.readlines()
    arr = [line.rstrip().split(',') for line in arr]      

isClosedFigure(arr, [3, 7])