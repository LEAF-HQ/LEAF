import os
from keras.callbacks import History, ModelCheckpoint, ReduceLROnPlateau, Callback
from PlottingFunctions import plot_losses

class PlotOnTrainingBase(Callback):
    def __init__(self, modelPath, eachEpoch=False):
        self.modelPath = modelPath
        self.eachEpoch = eachEpoch
        self.history = {}

    def MakePlots(self):
        plot_losses(self.history, mode='loss', name=os.path.join(self.modelPath,'training_loss'))
        plot_losses(self.history, mode='acc',  name=os.path.join(self.modelPath,'training_acc'))

    def on_epoch_end(self, epoch, logs=None):
        for k, v in logs.items():
            self.history.setdefault(k, []).append(v)
        if self.eachEpoch:
            self.MakePlots()

    def on_train_end(self, logs=None):
        self.MakePlots()


def DefineCallbacksBase(modelpath):
    history = History()
    filepath = os.path.join(modelpath, 'bestmodel_epoch{epoch:03d}_mode{val_mode:.2f}.h5')
    modelCheckpoint_loss_best = ModelCheckpoint(filepath=filepath.replace('_mode','_loss'), monitor='val_loss', save_best_only=True)
    modelCheckpoint_acc_best  = ModelCheckpoint(filepath=filepath.replace('_mode','_acc'),  monitor='val_acc',  save_best_only=True)
    PlotTraining = PlotOnTrainingBase(modelPath=modelpath)

    callbacks = []
    callbacks.append(history)
    callbacks.append(modelCheckpoint_loss_best)
    callbacks.append(modelCheckpoint_acc_best)
    callbacks.append(PlotTraining)
    return callbacks
