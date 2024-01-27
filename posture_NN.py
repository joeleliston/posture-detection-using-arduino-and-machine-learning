import pandas as pd
from sklearn.model_selection import train_test_split
import matplotlib.pyplot as plt
import tensorflow as tf
from tensorflow import keras

raw_data = pd.read_csv("C:/Users/Eli/Desktop/P4/stacked_IMU_data_2.csv")

print(raw_data.head())
print(raw_data.shape)
# Splitting the dataset (sklearn)
x_train, x_test, \
y_train, y_test = train_test_split(raw_data.iloc[:, :3], raw_data.iloc[:, -1], \
                                   train_size=0.7, shuffle=True )


val_per = x_test.shape[0] / x_train.shape[0]
#splitting the test data to test data and validation data
x_train_2, x_val, \
y_train_2, y_val = train_test_split(x_train, y_train, \
                                    test_size=val_per, \
                                    shuffle=True)

print(x_train_2.shape, y_train_2.shape)
print(x_val.shape, y_val.shape)
print(x_test.shape, y_test.shape)


model = tf.keras.Sequential()

# First layer takes a scalar input and feeds it through 8 "neurons". The
# neurons decide whether to activate based on the 'relu' activation function.
model.add(keras.layers.Dense(256, activation='relu', input_shape=(x_train_2.shape[1],)))
model.add(keras.layers.Dense(256, activation='relu'))
model.add(keras.layers.Dense(128, activation='relu'))
model.add(tf.keras.layers.Dropout(0.3))
model.add(keras.layers.Dense(128, activation='relu'))
model.add(keras.layers.Dense(64, activation='relu'))
model.add(tf.keras.layers.Dropout(0.3))

# Final layer is a single neuron, since we want to output a single value
model.add(keras.layers.Dense(5, activation='softmax'))

# Compile the model using the standard 'adam' optimizer and the mean squared error or 'mse' loss function for regression.
model.compile(optimizer='adam', loss=tf.losses.SparseCategoricalCrossentropy(), metrics=['accuracy'])

model.summary()

# defining the epochs and batch size
epochs = 2000
batch_size = 512

# Train the model on our training data while validating on our validation set
history = model.fit(x_train_2, y_train_2, epochs=epochs, batch_size=batch_size,
                        validation_data=(x_val, y_val))

# Draw a graph of the loss, which is the distance between
# the predicted and actual values during training and validation.
train_loss = history.history['loss']
val_loss = history.history['val_loss']

epochs_1 = range(1, len(train_loss) + 1)


plt.plot(epochs_1, train_loss, 'g.', label='Training loss')
plt.plot(epochs_1, val_loss, 'b', label='Validation loss')
plt.title('Training and validation loss')
plt.xlabel('Epochs')
plt.ylabel('Loss')
plt.legend()
plt.show()

# evaluate the model
# Calculate and print the loss on our test dataset
test_loss, test_acc = model.evaluate(x_test, y_test)
print('Test Accuracy: %.3f' % test_acc)

# Convert the model to the TensorFlow Lite format without quantization
converter = tf.lite.TFLiteConverter.from_keras_model(model)
model_no_quant_tflite = converter.convert()

# Save the model to disk
open("posture_IMU.tflite", "wb").write(model_no_quant_tflite)







