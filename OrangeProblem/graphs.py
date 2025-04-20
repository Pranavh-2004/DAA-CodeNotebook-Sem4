import pandas as pd
import matplotlib.pyplot as plt

# Load data from the text files
horspool_df = pd.read_csv("/Users/pranavhemanth/Code/Academics/DAA-S4/Student_Copy/horspool_values.txt")
boyermoore_df = pd.read_csv("/Users/pranavhemanth/Code/Academics/DAA-S4/Student_Copy/boyermoore_values.txt")

# Extract relevant columns
text_lengths = horspool_df["textlen"]
horspool_times = horspool_df["timetaken"]
boyermoore_times = boyermoore_df["timetaken"]

# Plot the data
plt.figure(figsize=(10, 6))
plt.plot(text_lengths, horspool_times, marker='o', linestyle='-', label="Horspool")
plt.plot(text_lengths, boyermoore_times, marker='s', linestyle='-', label="Boyer-Moore")

# Labels and title
plt.xlabel("Text Length")
plt.ylabel("Time Taken (ns)")
plt.title("Comparison of Horspool vs Boyer-Moore Algorithm Performance")
plt.legend()
plt.grid(True)

# Save the plot
plt.savefig("comparison_plot.png")
plt.show()
