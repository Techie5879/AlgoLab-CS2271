import matplotlib.pyplot as plt

def read_data(file_path):
    data = []

    with open(file_path, 'r') as file:
        lines = file.readlines()

        for i in range(0, len(lines), 2):
            vertices = int(lines[i].split()[-1])
            value = float(lines[i + 1])
            data.append((vertices, value))

    return data

file1_data = read_data('greedy.txt')
file2_data = read_data('dp.txt')

vertices1, values1 = zip(*file1_data)
vertices2, values2 = zip(*file2_data)


diff = []
for i in range(0, len(file1_data), 30):
    values1_subset = [v for _, v in file1_data[i:i+30]]
    values2_subset = [v for _, v in file2_data[i:i+30]]
    avg1 = sum(values1_subset)/30
    avg2 = sum(values2_subset)/30
    diff.append(avg1 - avg2)


vertices1 = vertices1[::30]

fig, ax = plt.subplots(figsize=(10, 8)) # Change the figure size as per your requirement

ax.plot(vertices1, diff, 'r.-', label='Difference')
ax.set_xlabel('Number of vertices')
ax.set_ylabel('Difference')
ax.set_title('Difference between DP vs Greedy Approach')
ax.legend()
ax.set_xticks(range(0, vertices1[-1]+1, 5)) # set x-axis ticks every 5 starting from 2

plt.savefig("diff.jpg")
plt.show()