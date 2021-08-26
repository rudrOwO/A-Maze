#include "card.h"
extern sf::RenderWindow window;
extern float cardDrawStartY;


const std::unordered_map<std::string, int> Card::tokenToActionType = {
    {"move",  Action::move},
    {"turn",  Action::turn},
    {"write", Action::write},
    {"state", Action::setState}
};


Card::Card ():
    dataToActionQueue(9),
    cursor("->", firaCode, fontSize + 1),
    cardBox({width, 0.f}),
    startPosition(window.getSize().x * (4.f / 5.f), cardDrawStartY),
    red(Palette::colors.at('7').first),
    grey(Palette::colors.at('*').first),
    blue_grey(Palette::colors.at('5').first)
    
{
    cardBox.setPosition(startPosition);
    cardBox.setFillColor(blue_grey);
    cursor.setPosition(startPosition + sf::Vector2f(10.f, 0.f));
    cursor.setStyle(sf::Text::Style::Bold);
}


void Card::push_line (bool isScopped, const std::pair<std::string, std::string>& token)
{
    code.push_back({false, false, {"", ""}, {0, 0}, sf::Text("", firaCode, fontSize)});

    Line &currentLine = code.back();

    currentLine.isLocked = (token.first != "");
    currentLine.drawToScreen.setPosition(startPosition + sf::Vector2f(offSet, (code.size() - 1) * (fontSize + lineSpace)));

    if (currentLine.isLocked) {
        currentLine.drawToScreen.setStyle(sf::Text::Style::Bold);
        currentLine.drawToScreen.setCharacterSize(fontSize + 1);
    }

    formatCode(isScopped, token);
    cardBox.setSize({width, cardBox.getSize().y + fontSize + lineSpace});
}


void Card::formatCode (bool isScopped, const std::pair<std::string, std::string>& token)
{
    Action pushAction;
    
    if (token.first != "if" and token.first != "")
        pushAction.type = tokenToActionType.at(token.first);

    if (token.first == "move" or token.first == "turn")
        pushAction.argument = std::stoi(token.second);
    else if (token.first == "write" or token.first == "state" or token.first == "if")
        pushAction.argument = token.second[0];
    
    Line &currentLine = code.back();

    currentLine.isScopped = isScopped;
    currentLine.token = token;
    currentLine.action = pushAction;

    fixText(currentLine);
}


void Card::formatCode ()
{
    Action pushAction;
    Line &currentLine = code[lineEditorIndex];
    
    if (currentLine.token.first != "if" and currentLine.token.first != "")
        pushAction.type = tokenToActionType.at(currentLine.token.first);

    if (currentLine.token.first == "move" or currentLine.token.first == "turn")
        pushAction.argument = std::stoi(currentLine.token.second);
    else if (currentLine.token.first == "write" or currentLine.token.first == "state" or currentLine.token.first == "if")
        pushAction.argument = currentLine.token.second[0];
    
    currentLine.action = pushAction;
}


void Card::onKeyPress (sf::Event& event)
{
    switch (event.key.code) {
        case sf::Keyboard::Return:
        case sf::Keyboard::Down:
            if (lineEditorIndex < code.size() - 1) {
                ++lineEditorIndex;
                cursor.move({0.f, fontSize + lineSpace});
            }
            secondWordSelected = false;
            break;

        case sf::Keyboard::Up:
            if (lineEditorIndex > 0) {
                --lineEditorIndex;
                cursor.move({0.f, -(fontSize + lineSpace)});
            }
            secondWordSelected = false;
            break;
        
        case sf::Keyboard::BackSpace:
            if (not code[lineEditorIndex].isLocked) {
                code[lineEditorIndex].token.first = "";    
                code[lineEditorIndex].token.second = "";    
            }
            secondWordSelected = false;
            break;

        case sf::Keyboard::Tab:
            if (not code[lineEditorIndex].isLocked)
                code[lineEditorIndex].isScopped = not code[lineEditorIndex].isScopped;
            break;
        
        default:
            if (not code[lineEditorIndex].isLocked) {
                if (event.key.code == sf::Keyboard::Space)
                    secondWordSelected = true;
                else { 
                    int keyCode = event.key.code;
                    std::string &selectedWord = (secondWordSelected ? code[lineEditorIndex].token.second : code[lineEditorIndex].token.first);

                    if (keyCode < 26)
                        selectedWord.push_back(keyCode + 'a');
                    else
                        selectedWord.push_back(keyCode - 26 + '0');
                }
            }
    }

    fixText(code[lineEditorIndex]);
}


void Card::compileCode ()
{
    for (lineEditorIndex = 0; lineEditorIndex < code.size(); ++lineEditorIndex)
        formatCode();
         
    for (const auto& line : code) {
        if (line.token.first == "if")
            currentScope = line.action.argument - '0';

        else if (line.token.first != "") {
            if (not line.isScopped) {
                for (int i = 0; i < 9; ++i)
                    dataToActionQueue[i].push_back({ tokenToActionType.at(line.token.first), line.action.argument });

            } else {
                dataToActionQueue[currentScope].push_back({ tokenToActionType.at(line.token.first), line.action.argument });
            }
        }
    }
}


const std::deque<Action>& Card::getActionQueue (char data) const
{
    if (data == '*')
        data = '8';

    return dataToActionQueue[data - '0'];
}


void Card::fixText (Line& currentLine)
{
    currentLine.drawToScreen.setString(currentLine.token.first + " " + currentLine.token.second);
    
    if (currentLine.isScopped)
        currentLine.drawToScreen.setPosition({startPosition.x + offSet + indentation, currentLine.drawToScreen.getPosition().y});
    else
        currentLine.drawToScreen.setPosition({startPosition.x + offSet, currentLine.drawToScreen.getPosition().y});
}


void Card::draw ()
{
    window.draw(cardBox);
    window.draw(cursor);
    
    for (const auto& line : code)
        window.draw(line.drawToScreen);
}