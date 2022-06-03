import os, json
import pandas as pd
from pickle import dump
from keras.models import model_from_json, load_model
from keras.utils import to_categorical, plot_model
from CallBacksBase import DefineCallbacksBase
from functions_dnn import classes_to_str, float_to_str
from printing_utils import green
from utils import ensureDirectory

class TrainingBase():
    def __init__(self, DNNparams={}, inputdir='', outputdir='', runonfraction=1.0,  do_weights=False):
        self.DNNparams = DNNparams
        self.inputdir = os.path.join(inputdir, classes_to_str(self.DNNparams['classes']))
        self.outputdir = outputdir
        self.frac = float_to_str(runonfraction)
        self.do_weights = do_weights
        self.isFitGenerator = False
        self.modelpath = outputdir
        ensureDirectory(self.modelpath)

    def DefineCallbacks(self):
        self.callbacks = DefineCallbacksBase(self.modelpath)

    def LoadInputs(self):
        raise NotImplementedError('LoadInputs method is not initialized. Fix this and make sure to also load the index here.')

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
            info['validation_data'] = (self.inputs['val'], self.labels['val'], self.weights['val'])


        if self.isFitGenerator:
            self.model.fit_generator(generator=self.training_gen, validation_data=self.validation_gen, max_queue_size=10, use_multiprocessing=True, workers=10, epochs=self.params['epochs'], verbose=1, callbacks=self.callbacks)
            # self.model.fit_generator(generator=self.training_gen, validation_data=self.validation_gen, epochs=self.params['epochs'], verbose=1, callbacks=self.callbacks)
        else:
            history = self.model.fit(self.inputs['train'], self.labels['train'], **info)
        return history

    def Predict(self, column_basename=None, columns=None):
        column_names = []
        if column_basename:
            column_names = [column_basename+'_'+str(c) for c in columns]
        elif columns.isinstance(list):
            column_names = columns
        else:
            raise ArgumentError('Invalid arguments passed to TrainingBase.Predict().')

        self.predictions = {}
        for mode in ['train','val','test']:
            self.predictions[mode] = pd.DataFrame(self.model.predict(self.inputs[mode]), index=self.index[mode], columns=column_names)

    def SavePredictions(self):
        raise NotImplementedError('SavePredictions method is not initialized. Fix this.')

    def SaveModel(self, modelname='finalmodel'):
        self.model.save(os.path.join(self.modelpath, '%s.h5' % (modelname)))
        with open(os.path.join(self.modelpath, '%s_history.pkl' % (modelname)), 'w') as f:
            dump(self.model.history.history, f)

    def LoadModel(self, modelname='finalmodel'):
        self.model = load_model(os.path.join(self.modelpath, '%s.h5' % (modelname)))

    def Train(self):
        self.LoadInputs()
        self.DefineCallbacks()
        self.MakeModel()
        history = self.FitModel()
        self.SaveModel()
        self.Predict(column_basename='score', columns=[i for i in range(self.labels['train'].shape[1])])
        self.SavePredictions()
