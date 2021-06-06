Specifics Engine:
Component based engine.
basecomponent is the base of everything -> you can activate and deactivate any component
final gameobject class -> you can activate and deactivate any gameobject
SceneManager -> you can add scenes and delete them by name -> only yhe active scene gets rendered
Inputmanager -> easy controller and keyboard input, a specific command gets triggered.
Sound manager on seperate thread using simple SDL audio
Seperate gametime class so you can access the current delta time + the ability to pause the time

specifics game:
Observer -> score and player health display in game
Subject component to add the observer to the player
The field gets initialized via a seperate file.
field is made out of textures

Source code Github:
https://github.com/TiboRombaut/Minigin

