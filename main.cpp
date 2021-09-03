#include <iostream>
#include <sstream>
#include <string>
enum switchBoard{
    HOUSE_SUPPLY      = 1 << 0,
    HOUSE_SOCKETS     = 1 << 1,
    HOUSE_LIGHT       = 1 << 2,
    GARDEN_LIGHT      = 1 << 3,
    ROOM_HEATING      = 1 << 4,
    PIPE_HEATING      = 1 << 5,
    ROOM_CONDITIONING = 1 << 6
};
//int condition = 0;
int colorTemperature = 5000;
int reaction(int time, float tIn, float tEx, bool moveEx, bool lightOn){
    int condition = 0;
    if(time >= 16 && time <= 20) {
        colorTemperature = 5000 - (5000 - 2700)/(20 - 16)*(time - 16);
    } else if (time >= 0 && time <= 16) {
        colorTemperature = 5000;
    } else {
        colorTemperature = 2700;
    }

    if(((time >=0 && time <= 5)||(time >=16 && time <= 24)) && moveEx){
        condition |= GARDEN_LIGHT;
    } else condition &= ~GARDEN_LIGHT;

    if(lightOn) {
        condition |= HOUSE_LIGHT;
    } else condition &= ~HOUSE_LIGHT;

    if(tIn < 22) condition |= ROOM_HEATING;
    if(tIn >= 25) condition &= ~ ROOM_HEATING;

    if(tIn >= 30) condition |= ROOM_CONDITIONING;
    if(tIn <= 25) condition &= ~ ROOM_CONDITIONING;

    if(tEx < 0) condition |= PIPE_HEATING;
    if(tEx > 5) condition &= ~ PIPE_HEATING;



    return condition;


}
void outputSwitchBoardChanges(int condition1,int condition2){
    std::stringstream outText;
    if((condition1 & HOUSE_SUPPLY) && !(condition2 & HOUSE_SUPPLY )) outText << "House supply off. ";
    if(!(condition1 & HOUSE_SUPPLY) && (condition2 & HOUSE_SUPPLY)) outText << "House supply on. ";

    if((condition1 & HOUSE_SOCKETS) && !(condition2 & HOUSE_SOCKETS)) outText << "House sockets off. ";
    if(!(condition1 & HOUSE_SOCKETS) && (condition2 & HOUSE_SOCKETS)) outText << "House sockets on. ";

    if((condition1 & HOUSE_LIGHT) && !(condition2 & HOUSE_LIGHT)) outText << "House light off. ";
    if(!(condition1 & HOUSE_LIGHT) && (condition2 & HOUSE_LIGHT)) outText << "House light on. ";

    if(condition2 & HOUSE_LIGHT) outText << "Light temperature is " << colorTemperature <<". ";

    if((condition1 & GARDEN_LIGHT) && !(condition2 & GARDEN_LIGHT)) outText << "Garden light off. ";
    if(!(condition1 & GARDEN_LIGHT) && (condition2 & GARDEN_LIGHT)) outText << "Garden light on. ";

    if((condition1 & ROOM_HEATING) && !(condition2 & ROOM_HEATING )) outText << "Room heating off. ";
    if(!(condition1 & ROOM_HEATING) && (condition2 & ROOM_HEATING)) outText << "Room heating on. ";

    if((condition1 & PIPE_HEATING) && !(condition2 & PIPE_HEATING )) outText << "Pipe heating off. ";
    if(!(condition1 & PIPE_HEATING) && (condition2 & PIPE_HEATING)) outText << "Pipe heating on. ";

    if((condition1 & ROOM_CONDITIONING) && !(condition2 & ROOM_CONDITIONING)) outText << "Room conditioning off. ";
    if(!(condition1 & ROOM_CONDITIONING) && (condition2 & ROOM_CONDITIONING)) outText << "Room conditioning on. ";


    if(outText.str().length() == 0) {
        std::cout << "No changes " << std::endl;
    } else {
        std::cout << outText.str() << std::endl;
    }

}
int main() {
    int conditionBefore = 0, conditionAfter = 0;
    float tIn, tEx;
    bool moveEx, lightOn;
   // char dummy;

    for(int time = 0; time < 48; time++){
        std::string moveExStr, lightOnStr;
        std::stringstream text;
        std::string strText;

        conditionBefore = conditionAfter;
        int dayTime = time % 24;
        std::cout << "Day " << time/24+1 <<" Hour "<< dayTime << ". " <<
        "Input parameters: tIn tEx moveEx(yes/no) lightOn(on/off)" << std::endl;
        getline(std::cin, strText);
        text.str(strText);
        text >> tIn;
        text >> tEx;
        text >> moveExStr;
        text >> lightOnStr;

        moveEx = (moveExStr == "yes");
        lightOn = (lightOnStr == "on");
        std::cout << tIn << " " << tEx << " " << (moveEx? "yes": "no") << " " << (lightOn? "on": "off") << std::endl;
        conditionAfter = reaction(dayTime,tIn,tEx,moveEx,lightOn);
        outputSwitchBoardChanges(conditionBefore, conditionAfter);
    }

    return 0;
}
