import matplotlib.pyplot as plt

# Read vertices from file
with open('output.txt') as f:
    content = f.readlines()

# Process vertices for each test case
vertices_list = []
i = 0


while i < len(content) and len(vertices_list) < 50:
    n = int(content[i].strip())
    vertices = []
    for j in range(n):
        x, y = map(int, content[i+j+1].strip().split())
        vertices.append((x, y))
    vertices_list.append(vertices)
    i += (n + 1)

# Read triangulation data from file
triangles_list = []
with open('triangles.txt') as f:
    content = f.readlines()

i = 0
while i < len(content) and len(triangles_list) < 50:
    n = int(content[i].split(':')[-1].strip())
    triangles = []
    for j in range(n - 2):
        triangle = [tuple(map(int, line.strip().split())) for line in content[i+1+3*j:i+1+3*(j+1)]]
        triangles.append(triangle)
    triangles_list.append(triangles)
    i += 1 + 3*(n - 2)

    # Skip the corresponding 5 polygon triangulations
    # num_skipped = 0
    # while num_skipped <= 5:
    #     n = int(content[i].split(':')[-1].strip())
    #     i += 1 + 3*(n - 2)
    #     num_skipped += 1

# Plot vertices, lines, and triangulation for each test case
fig = plt.figure(figsize=(600, 600))
fig.set_figheight(50)
fig.set_figwidth(50)
fig.suptitle("Showing a Subsample of Triangulations")

for i, (vertices, triangles) in enumerate(zip(vertices_list, triangles_list)):
    ax = plt.subplot(5, 10, i+1)
    ax.scatter(*zip(*vertices))
    ax.plot(*zip(*(vertices + [vertices[0]])), color='r')
    
    # Plot triangulation
    for triangle in triangles:
        ax.plot(*zip(*(triangle + [triangle[0]])), color='b', linestyle='--')
    
    ax.set_title(f'Test case {i+1}')
plt.savefig("triangulations.jpg")
plt.show()