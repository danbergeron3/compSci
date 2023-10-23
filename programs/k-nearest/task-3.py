# Import the necessary libraries
import numpy as np
from sklearn.model_selection import cross_val_score, train_test_split
from sklearn.neighbors import KNeighborsClassifier
from sklearn.datasets import load_iris
from sklearn.metrics import precision_score, recall_score, f1_score

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

# Step 3: Train the best k-NN model on the entire dataset
knn = KNeighborsClassifier(n_neighbors=best_k)
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)
knn.fit(X_train, y_train)
y_pred = knn.predict(X_test)

# Step 4: Calculate additional evaluation metrics on the testing set
precision = precision_score(y_test, y_pred, average='weighted')
recall = recall_score(y_test, y_pred, average='weighted')
f1 = f1_score(y_test, y_pred, average='weighted')

print(f"Precision: {precision}")
print(f"Recall: {recall}")
print(f"F1-Score: {f1}")
