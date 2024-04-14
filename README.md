In this project we implemented a clustering algorithm that is based on symmetric Non-negative Matrix Factorization (symNMF).
we further applied it to several datasets and compare to K_means.

we Implemented the following files:

    1. symnmf.py: Python interface of our code.
    
    2. symnmf.h: C header file.
    
    3. symnmf.c: C interface of our code.
    
    4. symnmfmodule.c: Python C API wrapper.
    
    5. analysis.py: Analyze the algorithm.
    
    6. setup.py: The setup file.
    
    7. Makefile: Your make script to build the C interface.

**Python Program (symnmf.py)**

  1. Reading user CMD arguments:
     
    (a) k (int, < N): Number of required clusters.
    
    (b) goal: Can get the following values:
    
        i. symnmf: Perform full the symNMF as described in 1 and output H.
        
        ii. sym: Calculate and output the similarity matrix.
        
        iii. ddg: Calculate and output the Diagonal Degree Matrix.
        
        iv. norm: Calculate and output the normalized similarity matrix.
        
    (c) file_name (.txt): The path to the Input file, it will contain N data points for all above
    
        goals, the file extension is .txt
        
  3. Implementation of H initialization when the goal=symnmf
     
  5. Interfacing with your C extension:
     
    (a) Import C module symnmf

    (b) if the goal=’symnmf’, call the symnmf() method with passing the initial H, the datapoints X and other arguments if needed, and get the final H.
    
    (c) if the goal=’sym’, call the sym() method with passing the datapoints X, and get
    similarity matrix.
    
    (d) if the goal=’ddg’, call the ddg() method with passing the datapoints X, and get diagonal degree matrix
    
    (e) if the goal=’norm’, call the norm() method with passing the datapoints X, and get
    normalized similarity matrix.
    
  6. Output the required matrix separated by a comma, such that each row is in a line of its own
     

**C Program (symnmf.c)**

This is the C implementation program, with the following requirements:

  1. Reading user CMD arguments:
     
    (a) goal: Can get the following values:

      i. sym: Calculate and output the similarity matrix.
     
      ii. ddg: Calculate and output the Diagonal Degree Matrix.
     
      iii. norm: Calculate and output the normalized similarity matrix.
     
    (b) file_name (.txt ): The path to the Input file, it will contain N data points for all above goals, the file extension is .txt
    
  3. Output the required matrix separated by a comma, such that each row is in a line of its
  own.


**Python C API (symnmfmodule.c)**

In this file we defined our C extension which will serve the functions: symnmf,sym,ddg,norm
for Python.

**C Header file (symnmf.h)**

This header defined all functions prototypes that is being used in symnmfmodule.c and
implemented at symnmf.c

**analysis.py**

Compares SymNMF to Kmeans++. Applies both methods to given dataset and report the silhouette_score from the sklearn.metrics. For SymNMF,
cluster assignment is done as explained before
The silhouette score measures clustering quality by comparing the between-cluster distance
against within-cluster distance. A higher score indicates better-defined clusters. The score
is calculated as the mean of the silhouette coefficient of each data point separately, which is
computed by the formula below:

    Silhouette coefficient = (b-a)/max(a,b)

where:

• a represents the mean distance between a data point and all other points within its cluster C.

• b represents the minimum over all other clusters D 6= C of the mean distance between the data point and all points in D.

The program has one argument: file_name(.txt): The path to the Input file, it will contain N data points, the file extension is .txt

**Setup (setup.py)**

This is the build used to create the *.so file that will allow symnmf.py to import mykmeanssp.

**Makefile**

Make script for building spkmeans executable, considering all it’s dependency.



