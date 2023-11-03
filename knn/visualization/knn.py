import json
import matplotlib.pyplot as plt

_, ax = plt.subplots()

f = open('data.json')
data = json.load(f)

x_coords = [float(coord[0]) for coord in data["X"]]
y_coords = [float(coord[1]) for coord in data["X"]]

ax.scatter(x_coords, y_coords, c=data["Y"])
plt.show()

f.close()