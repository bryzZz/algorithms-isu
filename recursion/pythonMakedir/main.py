import os
import pathlib
import json

def makeDirs(destination, dirs, spaces=""):
    spaces += "  "
    for key, item in dirs.items():
        dest = destination / key
        dest.mkdir(exist_ok=True)
        print(f"{spaces}Create dir {dest}")
        for _item in item:
            if isinstance(_item, dict):
                makeDirs(dest, _item, spaces)
            else:
                print(f"{spaces}Create file {dest/ _item}")
                with (dest / _item).open('w') as f:
                    f.write('1')

def checkDirs(destination, dirs, result=True):
    for key, item in dirs.items():
        dest = destination / key
        if not os.path.exists(dest):
            return False
        for _item in item:
            if isinstance(_item, dict):
                result = checkDirs(dest, _item, result)
            else:
                if not os.path.exists(dest / _item):
                    return False
    
    return result


data = json.load(open('./dirs.json'))

# makeDirs(pathlib.Path('/home/nikita/isu/algorithms/recursion/pythonMakedir'), data)
print(checkDirs(pathlib.Path('/home/nikita/isu/algorithms/recursion/pythonMakedir'), data))