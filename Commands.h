#ifndef COMMANDS_H
#define COMMANDS_H

#include "ParserXML.h"
#include "LightSource.h"

#include <QUndoCommand>

class AddLightCommand : public QUndoCommand {
public:
    AddLightCommand(ParserXML* parser, LightSource light, QUndoCommand* parent = 0);

    void undo();
    void redo();

private:
    ParserXML* _parser;
    LightSource _light;
};

#endif // COMMANDS_H
