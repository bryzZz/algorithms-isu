import matplotlib.pyplot as plt
import math
import time

def distance(lat1, lon1, lat2, lon2):
    r = 6371

    lat1 = math.radians(lat1)
    lon1 = math.radians(lon1)
    lat2 = math.radians(lat2)
    lon2 = math.radians(lon2)

    a = (math.sin((lat2 - lat1) / 2) ** 2 +
         math.cos(lat1) * math.cos(lat2) *
         math.sin((lon2 - lon1) / 2) ** 2)
    d = 2 * r * math.asin(a ** 0.5)

    return d

def thin_grid(points, min_distance):
    result = []

    p = points.pop()
    result.append(p)

    while points:
        p2 = points.pop()
        for p1 in result:
            if distance(*p1[:2], *p2[:2]) < min_distance:
                break
        else:
            result.append(p2)

    return result

def get_roi(lats, lons, vals, roi):
    result = []
    for lat, lon, val in zip(lats, lons, vals):
        if roi[0] < lon < roi[1] and roi[2] < lat < roi[3]:
            result.append([lat, lon, val])
    return result

def memoize(func):
    cache = dict()
    def wrapped(*args, **kwargs):
        param_hash = hash((args, tuple(kwargs.items())))
        if param_hash in cache:
            return cache[param_hash]
        result = func(*args, **kwargs)
        cache[param_hash] = result
        return result
    return wrapped

@memoize
def query(date: str, roi, min_distance: int=1000):
    with open(date, "r") as f:
        lats = []
        lons = []
        vals = []
        for line in f.readlines()[1:]:
            lat, lon, val = list(map(float, line.split()))
            lats.append(lat)
            lons.append(lon)
            vals.append(val)
        roi = get_roi(lats, lons, vals, roi)
        result = thin_grid(roi, min_distance)
        return result    

t = time.perf_counter()
result = query("2020-01-01.dat", (-100.0, -80.0, 28.0, 45.0))
print(f'Elapsed {time.perf_counter() - t}')

t = time.perf_counter()
result = query("2020-01-01.dat", (-100.0, -80.0, 28.0, 45.0))
print(f'Elapsed {time.perf_counter() - t}')

# plt.scatter(lons, lats, vals)
# plt.show()