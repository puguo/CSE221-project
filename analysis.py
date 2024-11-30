import csv
import numpy as np
import matplotlib.pyplot as plt

def compute_stats(file_path):
    with open(file_path, 'r') as csvfile:
        reader = csv.reader(csvfile)
        data = [float(row[0]) for row in reader if row] 

    mean = np.mean(data)
    median = np.median(data)
    std_dev = np.std(data)

    print(f"Overall Mean: {mean:.2f}")
    print(f"Overall Median: {median:.2f}")
    print(f"Overall Standard Deviation: {std_dev:.2f}")

    compute_iqr_stats(data)

def compute_iqr_stats(data):
    q1 = np.percentile(data, 25)
    q3 = np.percentile(data, 75)

    iqr_filtered_data = [x for x in data if q1 <= x <= q3]

    mean = np.mean(iqr_filtered_data)
    median = np.median(iqr_filtered_data)
    std_dev = np.std(iqr_filtered_data)

    print(f"IQR Filtered Mean (25th-75th percentile): {mean:.2f}")
    print(f"IQR Filtered Median (25th-75th percentile): {median:.2f}")
    print(f"IQR Filtered Standard Deviation (25th-75th percentile): {std_dev:.2f}")

def plot_rtt(file_path, title="RTT Over Iterations", output_file="rtt_plot.png"):
    with open(file_path, 'r') as csvfile:
        reader = csv.reader(csvfile)
        rtt_values = [float(row[0]) for row in reader if row]

    iterations = range(1, len(rtt_values) + 1)

    plt.figure(figsize=(10, 6))
    plt.plot(iterations, rtt_values, marker='o', markersize=2, linestyle='-', label='RTT (ns)')
    plt.title(title)
    plt.xlabel("Iteration")
    plt.ylabel("RTT (ns)")
    plt.grid(True)
    plt.legend()
    plt.tight_layout()

    plt.savefig(output_file)
    print(f"Plot saved as {output_file}")

if __name__ == "__main__":
    file_path_remote = './logs/rtt_remote.csv'
    file_path_local = 'logs/rtt_local.csv'
    print("local rtt")
    compute_stats(file_path_local)
    plot_rtt(file_path_local, title="RTT local Over Iterations", output_file="rtt_plot_local.png")
    print("remote rtt")
    compute_stats(file_path_remote)
    plot_rtt(file_path_remote, title="RTT remote Over Iterations", output_file="rtt_plot_remote.png")
