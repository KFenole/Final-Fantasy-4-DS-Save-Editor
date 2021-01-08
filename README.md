# Final Fantasy IV (Nintendo DS) Save Editor
## Version 0.6 Beta

This project is currently in beta.
Disclaimer: Please make backups in case something goes wrong (unlikely, but possible). **I am not responsible for loss of data or corruption of data!**

Feel free to use anything from this project, but please credit me if you do!
(Also, if you are working on a similar project, I'd be interested to hear about it)

**Current Features:**
- View/Edit Character EXP
- Heal Characters
- View/Edit Inventory (excluding key items)
- View/Edit Gil

**Features Planned:**
- Add all characters
- Modify status conditons
- Add/remove character skills
- Edit equipment
- Allow opening of file from anywhere
- A User Interface

**Known Issues:**
- When inputting a number, if your input starts with a number then includes illegal characters, the program will break.

As this project is still in beta, you may encounter other bugs, which I urge you to share. Thanks!

**How to use (universal):**
Compile using g++, Visual Studio or any C++ compiler, then run from the same directory as your save file. As the program exits beta, I will make it more and more user friendly. 
At the moment I don't offer any downloads, just the source. However once the project is out of beta, I will have executables for Mac and Windows available to download here.

*How to use (Mac):*
- Download the source (green button at the top right). Unzip if need be and move to a convenient location.
- Open Terminal (you can do "CMD+Space" and type "terminal").
- Type "cd " (no quotes) in the terminal window. Drag the folder (the one with all the source code in it) to the terminal window, then press enter.
- Type the following command to compile: "g++ -std=c++11 Main.cpp SaveFile.cpp" (again no quotes). Congratulations, the program is now compiled (you don't need to repeat this step every time)!
- Copy your .sav file into the folder with all the source. This will be the file you edit, so please make backups in case something goes wrong!
- Type "./a.out" (no quotes) to run the program.
- Enjoy! Feel free to contact me if you have any questions or bugs to report.

*How to use (Windows):*
- Create a new folder for the save editor somewhere on your computer. 
- Download the source (green button at the top right). Unzip if need be and move the .exe file from the executables folder to the same folder you created in the last step.
- Copy your .sav file into the same folder from step 1. This will be the file you edit, so please make backups in case something goes wrong!
- Open the .exe to run the program.
- Enjoy! Feel free to contact me if you have any questions or bugs to report.


**Changes:**
0.6 beta
- Added the option to select save slot (1-3)
- Added Key Item editing as well as item swapping
- Added the ability to view/edit party members
- Finished adding all character names
- Fixed a bug that caused gil modifications to not take effect
- Fixed various small typos and bugs

0.5 beta
- Can choose name of save file to open
- Added all items
- Added help menu
- Fixed a few minor bugs
- Added more detailed instructions on how to use.

0.4 beta
- Created a class for the save file to hide editing implementation and make editing more organized.
- Allowed for editing of EXP

