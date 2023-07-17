import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

uniform_df = pd.read_csv('randomizedQS_uniform_avg_obv.csv')
normal_df = pd.read_csv('randomizedQS_normal_avg_obv.csv')

n_uniform = uniform_df['size'].to_numpy()
comp_uniform = uniform_df['avg_count'].to_numpy()
time_uniform = uniform_df['avg_time'].to_numpy()
comp_ratio_uniform = comp_uniform/(n_uniform*np.log2(n_uniform))
time_ratio_uniform = time_uniform/(n_uniform*np.log2(n_uniform))

n_normal = normal_df['size'].to_numpy()
comp_normal = normal_df['avg_count'].to_numpy()
time_normal = normal_df['avg_time'].to_numpy()
comp_ratio_normal = comp_normal/(n_normal*np.log2(n_normal))
time_ratio_normal = time_normal/(n_normal*np.log2(n_normal))

fig, axis = plt.subplots(2, 1, figsize=(10, 7))

fig.suptitle('Comparison and Time Ratio for RQS')

axis[0].plot(comp_ratio_uniform, 'o-', label='Uniform')
axis[0].plot(comp_ratio_normal, 'o--', label='Normal')
axis[0].legend()
axis[0].set_ylabel(r'$\frac{comp}{n*lgn}$', rotation=0, labelpad=13)

axis[1].plot(time_ratio_uniform, 'o-', label='Uniform')
axis[1].plot(time_ratio_normal, 'o--', label = 'Normal')
axis[1].legend()
axis[1].set_ylabel(r'$\frac{time}{n*lgn}$', rotation=0, labelpad=13)


xticks = [i for i in range(0, len(comp_ratio_uniform), 2)]
axis[0].set_xticks(xticks)
axis[0].set_xticklabels([str(i+1) for i in xticks])
axis[1].set_xticks(xticks)
axis[1].set_xticklabels([str(i+1) for i in xticks])




plt.xlabel(r'lgn [array size = $n$]')

plt.savefig('observation.png')
plt.show()
