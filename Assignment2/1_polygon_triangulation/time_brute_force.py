import matplotlib.pyplot as plt

# Read data from file
with open("brute_force_time.txt", "r") as f:
    data = list(map(int, f.readlines()))

# Calculate average of each 30 numbers
n = len(data)
step = 30
averages = [sum(data[i:i+step])/step for i in range(0, n, step)]

# Plot the averages
fig, ax = plt.subplots()
ax.plot(range(3, len(averages)+3), averages, 'b.-', label='Brute Force')
print(len(averages))
# Set xticks and xticklabels
xticks = range(0, len(averages)+4, 1)
ax.set_xticks(xticks)
ax.set_xticklabels([str(x) for x in xticks])

ax.set_xlabel('Number of Vertices')
ax.set_ylabel('Time Taken (in ms)')
ax.set_title('Average Time Taken')

ax.legend()
fig.set_size_inches(10, 8)

plt.savefig('brute.jpg')
plt.show()
