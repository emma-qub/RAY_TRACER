#include "Commands.h"

AddLightCommand::AddLightCommand(ParserXML *parser, LightSource light, QUndoCommand *parent) :
    QUndoCommand(parent),
    _light(light) {

    _parser = parser;
}

void AddLightCommand::undo() {
    _parser->removeLight(_parser->nbLights()-1);
}

void AddLightCommand::redo() {
    _parser->addLight(_light);
}
