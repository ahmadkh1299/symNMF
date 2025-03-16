# Symmetric Non-negative Matrix Factorization (symNMF) Project

## 📌 Overview

This project implements a clustering algorithm based on **Symmetric Non-negative Matrix Factorization (symNMF)**. The implementation is done using **C and Python**, leveraging a **Python C API extension** for performance efficiency. The algorithm is applied to multiple datasets and compared to the **K-Means++** clustering method using the **Silhouette Score** to measure clustering quality.

## 🚀 Features

- **Similarity Matrix Computation**: Construct the similarity matrix based on the Euclidean distance between points.
- **Diagonal Degree Matrix Calculation**: Compute the diagonal degree matrix.
- **Normalized Similarity Matrix**: Generate the normalized similarity matrix.
- **SymNMF Optimization**: Apply the iterative update rule to factorize the matrix.
- **Cluster Assignment**: Assign each data point to a cluster based on the highest association score.
- **Comparison with K-Means++**: Compare results using the Silhouette Score.

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

### 1️⃣ Clone the repository

```bash
git clone https://github.com/your-repo/symnmf.git
cd symnmf
```

### 2️⃣ Install dependencies

```bash
pip install -r requirements.txt
```

### 3️⃣ Compile the C module

```bash
make
```

### 4️⃣ Build the Python C extension

```bash
python setup.py build_ext --inplace
```

## 🎯 Usage

### Running SymNMF

To run the symNMF algorithm, use:

```bash
python symnmf.py k goal input_file.txt
```

Where:

- `k` : Number of clusters.
- `goal` : Can be one of the following:
  - `symnmf` : Compute the full SymNMF and return H.
  - `sym` : Compute and return the similarity matrix.
  - `ddg` : Compute and return the diagonal degree matrix.
  - `norm` : Compute and return the normalized similarity matrix.
- `input_file.txt` : Path to the input file containing data points.

#### Example:

```bash
python symnmf.py 2 symnmf input_1.txt
```

### Running the Analysis Script

To compare SymNMF with K-Means++, run:

```bash
python analysis.py input_file.txt
```

Example output:

```
nmf: 0.1162
kmeans: 0.1147
```

## 🏆 Optimization Strategies

- **Memory Efficiency**: Uses in-place updates and optimized storage for matrices.
- **Indexing and Data Access**: Minimizes redundant computations.
- **Parallel Processing**: Uses optimized C extensions for speed improvements.


---

