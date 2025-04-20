import pandas as pd
import matplotlib.pyplot as plt

# Load data from the text files
horspool_df = pd.read_csv("/Users/pranavhemanth/Code/Academics/DAA-S4/Student_Copy/horspool_values.txt")
boyermoore_df = pd.read_csv("/Users/pranavhemanth/Code/Academics/DAA-S4/Student_Copy/boyermoore_values.txt")

# Extract relevant columns
text_lengths = horspool_df["textlen"]
horspool_comparisons = horspool_df["cmp"]
boyermoore_comparisons = boyermoore_df["cmp"]

# Plot the data
plt.figure(figsize=(10, 6))
plt.plot(text_lengths, horspool_comparisons, marker='o', linestyle='-', label="Horspool Comparisons")
plt.plot(text_lengths, boyermoore_comparisons, marker='s', linestyle='-', label="Boyer-Moore Comparisons")

# Labels and title
plt.xlabel("Text Length")
plt.ylabel("Number of Comparisons")
plt.title("Comparison of Horspool vs Boyer-Moore Algorithm (Comparisons)")
plt.legend()
plt.grid(True)

# Save the plot
plt.savefig("comparison_comparisons.png")
plt.show()
