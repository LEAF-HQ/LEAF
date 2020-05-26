#include "../include/Event.h"
#include "../include/CleaningModules.h"

using namespace std;

GenJetCleaner::GenJetCleaner(const GenJetId & id_): id(id_) {}

bool GenJetCleaner::process(Event & event){
    clean_collection(event.genjets, event, id);
    return true;
}
