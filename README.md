# Final Fantasy IV (Nintendo DS) Save Editor
## Version 0.4 Beta

This project is currently in beta.

Feel free to use anything from this project, but please credit me if you do!
(Also, if you are working on a similar project, I'd be interested to hear about it)

Current Features:
- View/Edit Character EXP
- View/Edit Inventory (most items excluding key items)
- View/Edit Gil

Features Planned:
- Add all characters
- Add all weapons and items
- Heal/Modify Status conditons
- Add/remove character skills
- Allow opening of file from anywhere
- A User Interface

Known Issues:
- When inputting a number, if your input starts with a number then includes illegal characters, the program will break.
- Does not properly read strength, stamina, etc. stats.

As this project is still in beta, you may encounter other bugs, which I urge you to share. Thanks!

How to use:
Compile using g++, Visual Studio or any C++ compiler, then run from the same directory as your save file, named 'FF4.sav'. As the program exits beta, I will make it more and more user friendly. 
At the moment I don't offer any downloads, just the source. However once the project is out of beta, I will have executables for Mac and Windows available to download here.

Changes:
0.4 beta
- Created a class for the save file to hide editing implementation and make editing more organized.
- Allowed for editing of EXP