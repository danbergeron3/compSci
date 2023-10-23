# Import the necessary libraries
import numpy as np
from sklearn.model_selection import cross_val_score
from sklearn.neighbors import KNeighborsClassifier
from sklearn.datasets import load_iris

# Load the Iris dataset
iris = load_iris()
X = iris.data
y = iris.target

# Step 1: Split the dataset into 'k' equal-sized parts (folds)
k = 5  # You can choose a different value for 'k'

# Step 2: Determine the best value for 'k' using k-fold cross-validation
best_k = None
best_accuracy = 0.0

for k_value in range(1, 11):  # Try k values from 1 to 10
    knn = KNeighborsClassifier(n_neighbors=k_value)
    scores = cross_val_score(knn, X, y, cv=k)
    average_accuracy = np.mean(scores)
    
    print(f"k = {k_value}, Average Accuracy: {average_accuracy}")

    if average_accuracy > best_accuracy:
        best_accuracy = average_accuracy
        best_k = k_value

print(f"Best 'k' for k-NN: {best_k} (with an average accuracy of {best_accuracy})")

# You can use the best_k for your final k-NN model and perform further evaluations
knn = KNeighborsClassifier(n_neighbors=best_k)
scores = cross_val_score(knn, X, y, cv=k)
average_accuracy = np.mean(scores)
print(f"Final k-NN model with best 'k' Accuracy: {average_accuracy}")
