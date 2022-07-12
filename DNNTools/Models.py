from keras.models import Sequential
from keras.layers import Dense, Dropout, BatchNormalization

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
