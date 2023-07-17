import pandas as pd
import matplotlib.pyplot as plt

# Load data from csv file into a pandas DataFrame
data = pd.read_csv('normal_normalized.csv', header=None)

# Plot histogram of the data with 20 bins
plt.hist(data[0], bins=101)

# Add x and y labels and a title to the plot
plt.xlabel('Value')
plt.ylabel('Frequency')
plt.title('Histogram of Data')

# Show the plot
plt.savefig('ND.png')
plt.show()



