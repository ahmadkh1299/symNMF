# Symmetric Non-negative Matrix Factorization (symNMF)

## 📌 Overview

This project implements a **Symmetric Non-negative Matrix Factorization (symNMF)** clustering algorithm. The implementation is done in **C and Python**, with a **Python C API extension** for performance optimization. The algorithm is applied to multiple datasets and compared to **K-Means++** using the **Silhouette Score** to measure clustering quality.

## 🚀 Features

- **Similarity Matrix Computation**: Computes similarity between data points.
- **Diagonal Degree Matrix Calculation**: Constructs the degree matrix.
- **Normalized Similarity Matrix**: Generates the normalized similarity matrix.
- **SymNMF Optimization**: Applies an iterative update rule to decompose the matrix.
- **Cluster Assignment**: Assigns each data point to a cluster based on association scores.
- **Performance Comparison**: Compares clustering quality against **K-Means++** using Silhouette Score.

## 📂 Project Structure

```
├── symnmf.py          # Python interface
├── symnmf.h           # C header file
├── symnmf.c           # C implementation
├── symnmfmodule.c     # Python C API wrapper
├── analysis.py        # Performance analysis and comparison
├── setup.py           # Python build script
├── Makefile           # Make script for compiling the C module
├── README.md          # Project documentation
```

## 🛠 Installation

This project does not require any external dependencies beyond standard Python and C libraries.

### 1️⃣ Clone the repository

```bash
git clone https://github.com/ahmadkh1299/symNMF.git
cd symNMF
```

### 2️⃣ Compile the C module

```bash
make
```

### 3️⃣ Build the Python C extension

```bash
python setup.py build_ext --inplace
```

## 🎯 Usage

### Running SymNMF

To execute the **SymNMF** algorithm, use:

```bash
python symnmf.py k goal input_file.txt
```

Where:

- `k` : Number of clusters.
- `goal` : Specifies the operation to perform:
  - `symnmf` : Compute **H** using SymNMF.
  - `sym` : Compute the similarity matrix.
  - `ddg` : Compute the diagonal degree matrix.
  - `norm` : Compute the normalized similarity matrix.
- `input_file.txt` : Path to the dataset (text file with N data points).

#### Example:

```bash
python symnmf.py 2 symnmf input_1.txt
```

### Running the Analysis Script

To compare **SymNMF** with **K-Means++**, execute:

```bash
python analysis.py input_file.txt
```

#### Example Output:

```
nmf: 0.1162
kmeans: 0.1147
```

## 🏆 Optimization Strategies

- **Efficient Memory Usage**: Uses in-place updates and optimized storage.
- **Optimized Indexing**: Reduces redundant computations for better performance.
- **C Extensions for Speed**: Uses optimized C implementations for efficiency.

## 🤝 Contributing

Contributions are welcome! Feel free to submit a pull request or open an issue in the repository.

---

This project is actively maintained. Reach out for any questions or improvements!

