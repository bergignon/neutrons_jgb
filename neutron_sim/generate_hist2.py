import numpy as np
import matplotlib.pyplot as plt

filename = 'testSSLG4Ex/build/output.csv'

# # Initialize three separate lists for the three columns
# col1 = []
# col2 = []
# col3 = []
# col4 = []
# col5 = []
# col6 = []
# col7 = []

# # Read and parse data
# with open(filename, 'r') as file:
#     for line in file:
#         line = line.strip()
#         if line and not line.startswith('entries'):  # Skip headers or empty lines
#             parts = line.split(',')
#             if len(parts) == 7:  # Ensure line is properly formatted
#                 try:
#                     val1 = float(parts[0])
#                     val2 = float(parts[1])
#                     val3 = float(parts[2])
#                     val4 = float(parts[3])
#                     val5 = float(parts[4])
#                     val6 = float(parts[5])
#                     val7 = float(parts[6])
#                     col1.append(val1)
#                     col2.append(val2)
#                     col3.append(val3)
#                     col4.append(val4)
#                     col5.append(val5)
#                     col6.append(val6)
#                     col7.append(val7)
#                 except ValueError:
#                     pass  # Skip malformed lines

# # Convert to numpy arrays
# col1 = np.array(col1)
# col2 = np.array(col2)
# col3 = np.array(col3)
# col4 = np.array(col5)
# col5 = np.array(col5)
# col6 = np.array(col6)
# col7 = np.array(col7)
# # Plotting all three histograms separately
# fig, axs = plt.subplots(1, 1, figsize=(10, 12), sharex=False)

# axs[0].hist(col1, bins=500, color='cornflowerblue', edgecolor='black')
# axs[0].set_yscale("log")
# axs[0].set_title('Number of scintillation photons per event')
# axs[0].set_ylabel('Count')
# axs[0].grid(True)

# axs[1].hist(col2, bins=500, color='darkorange', edgecolor='black')
# axs[1].set_title('Total energy deposit (MeV)')
# axs[1].set_ylabel('Count')
# axs[1].set_yscale("log")
# axs[1].grid(True)

# axs[2].hist(col3, bins=500, color='seagreen', edgecolor='black')
# axs[2].set_title('Cumulative energy of single event secondary protons (MeV)')
# axs[2].set_ylabel('Count')
# axs[2].set_yscale("log")
# axs[2].grid(True)

# axs[3].hist(col4, bins=500, color='seagreen', edgecolor='black')
# axs[3].set_title('Cumulative energy of single event secondary electrons (MeV)')
# axs[3].set_ylabel('Count')
# axs[3].set_yscale("log")
# axs[3].grid(True)

# axs[4].hist(col5, bins=500, color='seagreen', edgecolor='black')
# axs[4].set_title('Cumulative energy of single event secondary gammas (MeV)')
# axs[4].set_ylabel('Count')
# axs[4].set_yscale("log")
# axs[4].grid(True)

# axs[5].hist(col6, bins=500, color='seagreen', edgecolor='black')
# axs[5].set_title('Cumulative energy of single event secondary C12 (MeV)')
# axs[5].set_ylabel('Count')
# axs[5].set_yscale("log")
# axs[5].grid(True)

# axs[6].hist(col7, bins=500, color='seagreen', edgecolor='black')
# axs[6].set_title('Cumulative energy of single event secondary deuteron (MeV)')
# axs[6].set_ylabel('Count')
# axs[6].set_yscale("log")
# axs[6].grid(True)

# plt.tight_layout()
# plt.show()

columns = [[] for _ in range(7)]

# Read and parse data
with open(filename, 'r') as file:
    for line in file:
        line = line.strip()
        if line and not line.startswith('entries'):
            parts = line.split(',')
            if len(parts) == 7:
                try:
                    for i in range(7):
                        columns[i].append(float(parts[i]))
                except ValueError:
                    continue  # Skip malformed lines

# Convert and filter zeros
columns = [np.array(col) for col in columns]
columns = [col[col > 0] for col in columns]  # remove zeros

# Plot one histogram (e.g., column 1: scintillation photons)
plt.figure(figsize=(8, 6))
plt.hist(columns[0], bins=500, color='cornflowerblue', edgecolor='black')
# plt.yscale("log")
plt.title('Number of scintillation photons per event (non-zero only)')
plt.xlabel('Photon count')
plt.ylabel('Log-scaled frequency')
plt.grid(True)
plt.tight_layout()
plt.show()