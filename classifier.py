import pandas as pd
import matplotlib.pyplot as plt
from sklearn.preprocessing import LabelEncoder, RobustScaler
from sklearn.model_selection import train_test_split
from sklearn.metrics import plot_confusion_matrix
from sklearn.svm import LinearSVC
import numpy as np

### Entraînement du classifieur

def clean_dataset(df):
    assert isinstance(df, pd.DataFrame), "df needs to be a pd.DataFrame"
    df.dropna(inplace=True)
    indices_to_keep = ~df.isin([np.nan, np.inf, -np.inf]).any(1)
    return df[indices_to_keep].astype(np.float64)

def normalize(X):
         '''
         Batch normalization
         '''
         X_normalized = np.zeros((X.shape))
         for j in range(X.shape[1]):
             mean = np.mean(X[:, j])
             std = np.std(X[:, j])
             for i in range(X.shape[0]):
                 X_normalized[i, j] = (X[i, j] - mean) / (std + 0.000001)
         return X_normalized


PATH = r'./data/features.csv'

dataset = pd.read_csv(PATH,sep=';')

dataset.fillna(1e-6, inplace = True)

columns = dataset.columns.tolist() # get the columns

batch_audio = pd.DataFrame(dataset).to_numpy()

features = batch_audio[:, 1:]
y = batch_audio[:, 0]

X_train, X_test, y_train, y_test = train_test_split(features, y, test_size=0.2, random_state=0)

model = LinearSVC(C=0.1, max_iter=1e5, tol=1e-4) 

# On peut modifier les paramètres C, max_iter et tol, pour augmenter la performance du modèle.

model.fit(X_train, y_train)

print("Performances du modèle sur la base de données de test : ", model.score(X_test, y_test))


### Save W and b

b = model.intercept_
w = model.coef_



np.savetxt("matrice_w.txt", w, fmt='%.4f',delimiter=",")
np.savetxt("vecteur_b.txt", b, fmt='%.4f',delimiter=",")

#Plot Confusion Matrix

labels = ['blues', 'classical', 'country', 'disco', 'hiphop', 'jazz', 'metal', 'pop', 'reggae', 'rock']


fig, ax = plt.subplots(figsize=(10, 10), dpi=300)
plot_confusion_matrix(model, X_test, y_test, ax=ax, normalize='true', display_labels=labels)
plt.savefig('confusion.png',transparent=False, facecolor='white' )


   

