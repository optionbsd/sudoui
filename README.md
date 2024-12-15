# sudoUI

sudoUI is a UI for sudo, written in C++ and Qt5.


It enhances security as it does not store passwords,
does not have the ability for hidden execution,
and does not allow direct password transmission in the command.
sudoUI displays the executed command,
and the CLI is almost equivalent to regular sudo.
Follow simple installation steps to set up sudoUI on your PC or Mac, 
and use sudo just as you did before.


# How to use sudoUI?

Using sudoUI is safe and efficient. The sudoUI CLI is almost identical to regular sudo.
To run a command, simply enter ```sudo command 1stargument 2ndargument 3rdargument...```.


After that, a window will open where you will need to enter your account password.


# Install sudoUI

- **On macOS with Apple Silicon CPU**:
   1. Download the `darwin-aarch64` release with `UIData.ui`.
   2. Rename it to `sudo`.
   3. Rename the original `sudo` to `callsudo`.
   4. Move `sudoUI` and `UIData.ui` near `callsudo`.
   5. Done! Now you can try using sudoUI. Try this command: `sudo echo hi`.

- **On GNU/Linux, BSD, UNIX, and others**:
   1. Clone this repository with the command: `git clone https://github.com/optionbsd/sudoui.git`.
   2. Navigate to the directory: `cd sudoui`.
   3. Install Qt5 using your package manager.
   4. Compile with Clang: `clang++ main.cpp -o sudo -std=c++11 $(pkg-config --cflags --libs Qt5Widgets Qt5Gui Qt5Core Qt5UiTools)`.
   5. Rename the original `sudo` to `callsudo`.
   6. Move `sudoUI` and `UIData.ui` near `callsudo`.
   7. Done! Now you can try using sudoUI. Try this command: `sudo echo hi`.
