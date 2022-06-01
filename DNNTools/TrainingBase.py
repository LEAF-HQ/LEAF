import os, json
from keras.models import model_from_json, load_model
from keras.utils import to_categorical, plot_model
from CallBacksBase import DefineCallbacksBase
from functions_dnn import classes_to_str, float_to_str

class TrainingBase():
    def __init__(self, DNNparams={}, inputdir='', outputdir='', runonfraction=1.0,  do_weights=False):
        self.DNNparams = DNNparams
        self.inputdir = os.path.join(inputdir, classes_to_str(self.DNNparams['classes']))
        self.outputdir = outputdir
        self.frac = float_to_str(runonfraction)
        self.do_weights = do_weights
        self.isFitGenerator = False
        self.modelpath = os.path.join(outputdir)
        ensureDirectory(self.modelpath)

    def DefineCallbacks(self):
        self.callbacks = DefineCallbacksBase(self.modelpath)

    def LoadInputs(self):
        raise NotImplementedError('LoadInputs method is not initialized. Fix this.')

    def MakeModel(self):
        raise NotImplementedError('MakeModel method is not initialized. Fix this.')

    def FitModel(self):
        print(green('Training'))
        info = {
            'batch_size': self.DNNparams['batch_size'],
            'epochs': self.DNNparams['epochs'],
            'validation_data': (self.inputs['val'], self.labels['val']),
            'callbacks': self.callbacks,
            'verbose':1,
        }
        if self.do_weights:
            info['sample_weight'] = self.weights['train']
        if self.isFitGenerator:
            self.model.fit_generator(generator=self.training_gen, validation_data=self.validation_gen, max_queue_size= 10, use_multiprocessing=True, workers=10, epochs=self.params['epochs'], verbose=1, callbacks=self.callbacks)
            # self.model.fit_generator(generator=self.training_gen, validation_data=self.validation_gen, epochs=self.params['epochs'], verbose=1, callbacks=self.callbacks)
        else:
            history = self.model.fit(self.inputs['train'], self.labels['train'], **info)
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
