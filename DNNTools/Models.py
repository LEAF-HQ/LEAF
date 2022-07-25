from keras.models import Sequential, Model
from keras.layers import Dense, Dropout, BatchNormalization, Input, Flatten, Conv2D, MaxPooling2D, LSTM, merge


def SequentialModel(input_shape,output_shape,params):
    model = Sequential()
    # Define layers
    model.add(Dense(params['DenseLayer'][0], input_shape=input_shape, activation=params['activation_first'],kernel_initializer=params['kernel_initializer']))
    for i in range(1,len(params['DenseLayer'])):
        model.add(Dense(params['DenseLayer'][i], activation=params['activation_hidden'], kernel_initializer=params['kernel_initializer'], bias_initializer=params['bias_initializer']))
        if params['batchnorm']:
            model.add(BatchNormalization())
        if params['regularization_method']=='dropout':
            model.add(Dropout(params['regularization_rate']))
    model.add(Dense(output_shape, activation=params['activation_last']))
    # Compile
    myloss = 'categorical_crossentropy'
    if output_shape == 1:
        myloss = 'binary_crossentropy'
    # TODO 'Adamax'
    model.compile(loss=myloss, optimizer= params['optimizer'], metrics=params['metrics'])
    model.summary()
    # TODO
    # save model params
    # plot_model(model, to_file='model.png', show_shapes=True, show_layer_names=False, rankdir='LR')
    return model


def Sequential_LSTM_Model(input_shape,output_shape,params):
    # Define Inputs
    PFs = Input(shape=input_shape)
    # Define Recursive
    rec = LSTM(params['LSTMLayer'])(PFs)
    rec = Dropout(params['regularization_rate'])(rec)
    preds = rec
    for i in range(0,len(params['DenseLayer'])):
        preds = Dense(params['DenseLayer'][i], activation=params['activation_hidden'],kernel_initializer=params['kernel_initializer'],bias_initializer=params['bias_initializer'])(preds)
        if params['batchnorm']:
            preds = BatchNormalization()(preds)
        if params['regularization_method']=='dropout':
            preds = Dropout(params['regularization_rate'])(preds)

    preds = Dense(output_shape, activation=params['activation_last'])(preds)
    model = Model(inputs=[PFs], outputs=preds)
    # Compile
    myloss = 'categorical_crossentropy'
    if output_shape == 1:
        myloss = 'binary_crossentropy'
    model.compile(loss=myloss, optimizer= params['optimizer'], metrics=params['metrics'])
    model.summary()
    return model
