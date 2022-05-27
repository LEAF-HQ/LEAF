import os, json

from keras.models import model_from_json, load_model
from keras.utils import to_categorical, plot_model

from CallBacksBase import DefineCallbacksBase
from functions_dnn import float_to_str
from utils import ensureDirectory

class TrainingBase():
    def __init__(self, DNNparams={}, inputdir='', outputdir='',  do_weights=False):
        self.DNNparams = DNNparams
        self.inputdir = inputdir
        self.outputdir = outputdir
        self.isFitGenerator = False
        self.frac = float_to_str(1.0)
        self.modelpath = os.path.join(outputdir)
        self.do_weights=do_weights
        ensureDirectory(self.modelpath)

    def DefineCallbacks(self):
        self.callbacks = DefineCallbacksBase(self.modelpath)

    def LoadInputs(self):
        raise NotImplementedError('LoadInputs method is not initialized. Fix this.')

    def MakeModel(self):
        raise NotImplementedError('MakeModel method is not initialized. Fix this.')

    def FitModel(self):
        print 'Training'
        if self.isFitGenerator:
            self.model.fit_generator(generator=self.training_gen, validation_data=self.validation_gen, max_queue_size= 10, use_multiprocessing=True, workers=10, epochs=self.params['epochs'], verbose=1, callbacks=self.callbacks)
            # self.model.fit_generator(generator=self.training_gen, validation_data=self.validation_gen, epochs=self.params['epochs'], verbose=1, callbacks=self.callbacks)
        else:
            # self.model.fit(self.inputs_train, self.labels_train, sample_weight=self.weights_train, batch_size=self.params['batch_size'], epochs=self.params['epochs'], verbose=1, validation_data=(self.inputs_val, self.labels_val), callbacks=self.callbacks)
            if self.do_weights:
                history = self.model.fit(self.inputs['train'], self.labels['train'][:,0],  sample_weight=self.weights['train'], batch_size=self.DNNparams['batch_size'], epochs=self.DNNparams['epochs'], validation_data=(self.inputs['val'], self.labels['val'][:,0]), callbacks=self.callbacks, verbose=1)
            else:
                history = self.model.fit(self.inputs['train'], self.labels['train'][:,0],               batch_size=self.DNNparams['batch_size'], epochs=self.DNNparams['epochs'], validation_data=(self.inputs['val'], self.labels['val'][:,0]), callbacks=self.callbacks, verbose=1)
            # self.model.fit(self.input_train, self.labels_train, sample_weight=weights_train, batch_size=self.DNNparams['batch_size'], epochs=self.DNNparams['epochs'], shuffle=True, validation_data=(self.input_val, self.labels_val, self.weights_val), callbacks=self.callbacks, verbose=2)
        return history

    def Predict(self):
        self.predictions = {}
        for mode in ['train','val','test']:
            self.predictions[mode] = self.model.predict(self.inputs[mode])

    def Train(self):
        self.LoadInputs()
        self.DefineCallbacks()
        self.MakeModel()
        history = self.FitModel()
        self.Predict()
