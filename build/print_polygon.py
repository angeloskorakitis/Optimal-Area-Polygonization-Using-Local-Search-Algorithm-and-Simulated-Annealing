import sys
import os
import matplotlib.pyplot as plt

# all the n points
initial_points = []

input_file = sys.argv[1]
print("reading data from", input_file)

polygon = []
# draw the result 
with open(sys.argv[1]) as file:
    for line in file:
        values = line.split(" ")
        point = [int(values[0]), int(values[1])]
        polygon.append(point)
        initial_points.append(point)

# "close" the polygonic line
polygon.append(polygon[0])

xs, ys = zip(*polygon)
x,s = zip(*initial_points)

plt.figure()
plt.title(sys.argv[1])
plt.plot(xs, ys)

for x, y in initial_points:
    plt.plot(x, y, marker="o", markersize=3, markeredgecolor="red")

plt.show()

# print("deleting previous log...")
# os.remove("log.out")
