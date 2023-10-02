import numpy as np
from collections import defaultdict
import os

# Step 1: Data Collection
# You should load your dataset into training_set and testing_set

# Step 2: Preprocessing
def preprocess_email(email):
    # Tokenize the email into words
    words = email.split()
    
    # Remove stop words and convert to lowercase
    stop_words = set(["the", "and", "is"])  # Add more stop words as needed
    words = [word.lower() for word in words if word.lower() not in stop_words]
    
    return words

# Example usage:
preprocessed_email = preprocess_email("This is a sample email with some words.")
print(preprocessed_email)

# Step 3: Training
def train_bayesian_classifier(training_set):
    spam_count = 0
    ham_count = 0
    word_count_spam = defaultdict(int)
    word_count_ham = defaultdict(int)
    
    for email, label in training_set:
        words = preprocess_email(email)
        if label == 'spam':
            spam_count += 1
            for word in words:
                word_count_spam[word] += 1
        else:
            ham_count += 1
            for word in words:
                word_count_ham[word] += 1
    
    # Calculate probabilities
    p_spam = spam_count / len(training_set)
    p_ham = ham_count / len(training_set)
    
    p_word_given_spam = {word: count / spam_count for word, count in word_count_spam.items()}
    p_word_given_ham = {word: count / ham_count for word, count in word_count_ham.items()}
    
    return p_spam, p_ham, p_word_given_spam, p_word_given_ham

# Step 4: Classification
def classify_email(email, p_spam, p_ham, p_word_given_spam, p_word_given_ham):
    words = preprocess_email(email)
    log_p_spam = np.log(p_spam)
    log_p_ham = np.log(p_ham)
    
    for word in words:
        if word in p_word_given_spam:
            log_p_spam += np.log(p_word_given_spam[word])
        if word in p_word_given_ham:
            log_p_ham += np.log(p_word_given_ham[word])
    
    if log_p_spam > log_p_ham:
        return 'spam'
    else:
        return 'ham'

# Step 5: Evaluation
def evaluate_classifier(testing_set, p_spam, p_ham, p_word_given_spam, p_word_given_ham):
    true_positives = 0
    false_positives = 0
    true_negatives = 0
    false_negatives = 0
    
    for email, label in testing_set:
        predicted_label = classify_email(email, p_spam, p_ham, p_word_given_spam, p_word_given_ham)
        
        if predicted_label == 'spam' and label == 'spam':
            true_positives += 1
        elif predicted_label == 'spam' and label == 'ham':
            false_positives += 1
        elif predicted_label == 'ham' and label == 'ham':
            true_negatives += 1
        elif predicted_label == 'ham' and label == 'spam':
            false_negatives += 1
    
    accuracy = (true_positives + true_negatives) / len(testing_set)
    precision = true_positives / (true_positives + false_positives)
    recall = true_positives / (true_positives + false_negatives)
    f1_score = 2 * (precision * recall) / (precision + recall)
    
    return accuracy, precision, recall, f1_score

# Define your training set as a list of tuples
# Specify the path to the folder containing ham email files
ham_folder_path = 'C:/Users/Danie/OneDrive - UMass Lowell/College/Senior Year/Machine Learning/hw3/easy_ham'

# Initialize the training_set as an empty list
training_set = []

for filename in os.listdir(ham_folder_path):

    file_path = os.path.join(ham_folder_path, filename)
    
    # Open the file in binary mode ('rb')
    with open(file_path, 'rb') as file:
        # Read the contents of the file as bytes
        email_content_bytes = file.read()
    
    # Decode the content using a specific encoding (e.g., 'utf-8') or handle as bytes
    try:
        email_content = email_content_bytes.decode('utf-8')
    except UnicodeDecodeError:
        # Handle decoding errors or choose an appropriate fallback strategy
        # For example, you can ignore decoding errors and work with email_content_bytes
        continue
    
    # Assign the 'spam' label to the email and add it to the training_set
    training_set.append((email_content, 'spam'))

# Now, the training_set contains all the spam emails from the specified folder
# Specify the path to the folder containing spam email files
spam_folder_path = 'C:/Users/Danie/OneDrive - UMass Lowell/College/Senior Year/Machine Learning/hw3/spam/'

for filename in os.listdir(spam_folder_path):
    
    file_path = os.path.join(spam_folder_path, filename)
    
    # Open the file in binary mode ('rb')
    with open(file_path, 'rb') as file:
        # Read the contents of the file as bytes
        email_content_bytes = file.read()
    
    # Decode the content using a specific encoding (e.g., 'utf-8') or handle as bytes
    try:
        email_content = email_content_bytes.decode('utf-8')
    except UnicodeDecodeError:
        # Handle decoding errors or choose an appropriate fallback strategy
        # For example, you can ignore decoding errors and work with email_content_bytes
        continue
    
    # Assign the 'spam' label to the email and add it to the training_set
    training_set.append((email_content, 'spam'))

# Now, the training_set contains all the spam emails from the specified folder
testing_set = [
    ("Congratulations! You've won a free gift.", 'spam'),
    ("Reminder: Meeting at 2 PM tomorrow.", 'ham'),
    ("Limited-time offer: Buy one get one free!", 'spam'),
    ("Please find the attached document.", 'ham'),
    # Add more emails and their labels as needed
]
ham_folder_path = 'C:/Users/Danie/OneDrive - UMass Lowell/College/Senior Year/Machine Learning/hw3/hard_ham'

# Initialize the training_set as an empty list

for filename in os.listdir(ham_folder_path):

    file_path = os.path.join(ham_folder_path, filename)
    
    # Open the file in binary mode ('rb')
    with open(file_path, 'rb') as file:
        # Read the contents of the file as bytes
        email_content_bytes = file.read()
    
    # Decode the content using a specific encoding (e.g., 'utf-8') or handle as bytes
    try:
        email_content = email_content_bytes.decode('utf-8')
    except UnicodeDecodeError:
        # Handle decoding errors or choose an appropriate fallback strategy
        # For example, you can ignore decoding errors and work with email_content_bytes
        continue
    
    # Assign the 'spam' label to the email and add it to the training_set
    testing_set.append((email_content, 'spam'))

    spam_folder_path = 'C:/Users/Danie/OneDrive - UMass Lowell/College/Senior Year/Machine Learning/hw3/spam_2/'

for filename in os.listdir(spam_folder_path):
    
    file_path = os.path.join(spam_folder_path, filename)
    
    # Open the file in binary mode ('rb')
    with open(file_path, 'rb') as file:
        # Read the contents of the file as bytes
        email_content_bytes = file.read()
    
    # Decode the content using a specific encoding (e.g., 'utf-8') or handle as bytes
    try:
        email_content = email_content_bytes.decode('utf-8')
    except UnicodeDecodeError:
        # Handle decoding errors or choose an appropriate fallback strategy
        # For example, you can ignore decoding errors and work with email_content_bytes
        continue
    
    # Assign the 'spam' label to the email and add it to the training_set
    testing_set.append((email_content, 'spam'))

# Example usage:
# Training and testing sets should be defined before calling these functions.
p_spam, p_ham, p_word_given_spam, p_word_given_ham = train_bayesian_classifier(training_set)
accuracy, precision, recall, f1_score = evaluate_classifier(testing_set, p_spam, p_ham, p_word_given_spam, p_word_given_ham)
print("Accuracy:", accuracy)
print("Precision:", precision)
print("Recall:", recall)
print("F1 Score:", f1_score)
