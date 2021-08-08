# PoS Baby by Boss Baby Lovers
**Team members:** Andres Estrada, Ricardo Lira, Jhaymar Sabino, Rizelle Vinluan

## Project Description
**Objective:** We plan on building an interactive evil annoying baby that can be de-armed by doing a puzzle in which the user will perform on the baby. It is essentially a puzzle in the form of an embedded system integrated within a doll. 

**Description:** It will be an embedded system design written in C. The system will be within the doll, and it will control the responses of the doll to make sure the user is solving the puzzle in the correct order and the doll is interacting with the user. Interactions between the user and the project will consist of (reasonably) violent/inappropriate actions in order to quiet the baby. This includes twisting its head around, pulling off its leg from its body, “feeding” it alcohol, “choking” it, etc..  The doll's aesthetic will match what the spirit of the project is supposed to be, such as giving the baby red LEDs for eyes, a “666” display on its body, and vulgar lines output via speaker. 

**System:** The system that it will be in will be an embedded system in a doll with several components and functionalities. The doll will use buttons, sensors and a joystick that it will use as an input and it will have speakers and an LED component that will provide interactive responses for the user. For instance, the user can be instructed to stab the baby's eyes in order for it to stop crying, but if the user doesn't complete the instruction within the time period, the baby gets louder. The joystick will be used for somehow sensing that the user twists the baby's head, which can be another instruction.

**Uses:** The evil annoying baby can be used as a fun puzzle for the user and their friends to do. Its primary use is to provide entertainment for a party of people but it can also be used as a stress reliever and fun activity for those who want to take on the challenge of defeating the interactive evil baby.

**Inspiration:** The inspiration for this project is derived from those who grew traumatized by horror movies and evil dolls. This gives those people a chance to fight back from the trauma they have received as a child. Inspiration also comes from the dolls that are given out to students taking home-economics classes in high school. This project will be the antithesis to the values that home-economics classes try to instill in their students. Rather than attempt to quiet the baby by calming it by cradling it and attending to its “needs”, our baby doll will be a “possessed” baby. 

## Design Constraints
We have a cost constraint because our budget is $200. As a result, we need to be conscious of how much functionality our project will have, which is tied to the price of the components. We also need to follow the scope of the project and ensure that it is not too easy or too difficult. If we are below the budget and are following the plan accordingly, we can add another component. If we are having trouble keeping up with the plan, we can remove a component or replace it as long as it is within our budget.

We also have a design constraint, which is the size of the baby. We will need to somehow fit the breadboard inside the doll and place all according components while also making sure that the power supply doesn't accidentally shut off. We need to take into consideration the placement of components so that they don't accidentally get triggered or fall apart when the user moves the baby around. A size that might work is a baby that is at least 20 inches tall and 9 inches wide. 

It is important to note that this size might not be available, so a backup plan would be to use a cardboard box instead, which would be easier and more feasible considering how we can just place components with ease given a bigger space. However, this does lead to an aesthetic constraint because a box with baby limbs does not look as well put together as a regular baby doll.

We also have another design constraint because we have six sensors among other components. The arduino does not appear capable of addressing this many extensions. As a result, we may have to reduce the number of components or find a work around.

In addition, we must make sure that individuals under 21 do not participate with our project. This is because one of the instructions to disarm the baby is to trigger the alcohol sensor in the baby's mouth. This ties into ethical, safety, and human constraints. Basically, if this were a real product being sold in stores, the box labelling would need an alcohol warning, a “not for children” disclaimer, and a “enjoy responsibly” label. It should probably also be coded into the baby that the “baby thirsty” command comes up less frequently and perhaps no more than x amount over the span of  time so that the users do not get too drunk.

Aesthetic constraints are also an incredibly large issue because we do not have access to a custom doll manufacturer. This means that we will have to either purchase a doll and perform electrical surgery to place our components inside or conjure some very macgyvered version of a puzzle box. Either way, the look of the baby will be as if it was carved into and possibly even falling apart. We will do what we can with materials like duct tape, staples, nails, and hot glue to make sure the doll stays put, but the more we have to do that, the uglier it will be.

## Schedule of Milestones
Milestone # | What to Complete | What to Demo | Date Due
------------ | ------------- | ------------- | -------------
1 | <ul><li>Make sure Arduino Uno isn't faulty</li><li>Set up LCD screen</li><li>Set up speakers</li><li>Set up amplifier</li><li>Set up motion sensor</li><li>Set up touch sensor</li><li>Add scoring system (current and high score)</li><li>Add reset button</li><li>Create instructions</li></ul> | <ul><li>LCD screen outputs text</li><li>Speakers output noise</li><li>Show speaker volume rise and decrease with amplifier</li><li>Motion sensors sense motion</li><li>Touch sensors sense touch</li><li>Reset button sets both scores to 0</li><li>Button acts as successful action to cycle through instructions</li></ul> | 07/18/2021
2 | <ul><li>Set up gyroscope sensor</li><li>Set up alcohol sensor</li><li>Have speakers output custom noise</li><li>Integrate motion sensor into game functionality</li><li>Integrate touch sensor into game functionality</li><li>Randomize instructions</li></ul> | <ul><li>Gyroscope sensor detects twisting movement</li><li>Alcohol sensor detects alcohol</li><li>Speakers output baby crying</li><li>Show motion sensor being triggered while game is playing instead of button</li><li>Show touch sensor being triggered while game is playing instead of button</li><li>Use buttons for other instructions and show that instructions are randomized</li></ul> | 08/08/2021
3 | <li>Integrate gyroscope sensor into game functionality</li><li>Integrate alcohol sensor into game functionality</li><li>Add custom speaker noise for each instruction</li><li>Place components into baby</li> | <li>Show gyroscope sensor being triggered while game is playing instead of button</li><li>Show alcohol sensor being triggered while game is playing instead of button</li><li>Play the entire game to show that there is custom noise for each instruction</li><li>Show that all parts are inside the baby</li> | 08/29/2021

## Project Management Chart
https://trello.com/b/8eTKq5Sz

## Team Member Biographies
### Andres Estrada

4th year in Computer Science
Relevant Coursework: CS 100, CS 120A/B, CS 161
Programming Languages: C/C++, Python, Java
Hardware: Atmega, Spartan 3 FPGA
Software: Atmel Studio

### Ricardo Lira
4th year in Computer Science
Relevant coursework: CS100, CS120A/B, CS161
Programming Languages: C/C++, Java, Javascript
Hardware: Atmega, BASYS 2 Spartan - 3E FPGA Trainer Board
Software: Atmel Studio

### Jhaymar Sabino
4th year in Computer Science
Relevant Coursework: CS100, CS120B, CS170, CS171
Programming Languages: C/C++, Java, Python, Javascript
Hardware: ATMEGA 1284p
Software: Atmel Studio

### Rizelle Vinluan
4th year in Computer Science
Relevant coursework: CS100, CS120A/B, CS161
Programming Languages: C/C++, Python, Javascript
Hardware: Atmega1284p, BASYS 2 Spartan - 3E FPGA Trainer Board
Software: Atmel Studio 7


