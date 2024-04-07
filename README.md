# IranOpen - Technical Challenges - Futsal Challenge
[به فارسی 🇮🇷](README.fa.md)

In this repository, you can find the Futsal Challenge of IranOpen Technical Challenges.

## Introduction
Exciting challenges have been introduced to the 2D soccer simulation league.

![GIFMaker_me](https://github.com/RCSS-IR/io-challenges/assets/120306894/8e3e1b51-994e-4a73-ac5f-b8d148f3d230)
![GIFMaker_me (1)](https://github.com/RCSS-IR/io-challenges/assets/120306894/a7a916f4-8ea8-47d9-a4b7-c683c43e3e51)


## 🗒️ Rules

📺 ***Monitor and server:***

rcssmonitor and rcssserver are now applications, so it is more user-friendly and easy to use. 

🔤 ***Base and lib:***

Library will be in a different directory from your original library and the base will access it, so there are no conflicts or problems developing your team.

🪧 ***Play modes:***

No 
- corners
- goal kicks
- penalties
- kick_in
anymore. 

⏲️ ***Game time :***

No halves, the whole game will last 2000 cycles.

✏️ ***Game parameters:***

Game will be in fullstate mode and there's no offside fault. 

📏 ***Size of field:***

Length of field is now 48.0 and 28.0 for the width. 

⚽ ***Ball collision and Field's border:***

Field's border now is not just a line,  it is a wall !
That ball will collide with it.

🟢 ***Semicircular goal and goal area:***

Goal is Semicircular now(r = 3.0) , the goal area is in the same shape(r = 6.0). 

🛑 ***No goalie:***

No goalkeepers are allowed and there is no catch command, try to defend your goal with a tackle! 

👨 ***Agents:***

Only 3 players are allowed.

## Running the challenge locally
First download the futsal_monitor_v1.0 and futsal_server_v1.0 from the Release directory.

- Download and install the fuse package:
```
sudo apt install fuse
```

📁 In the directory run the following command to give executive access to **futsal_server**:
```
chmod +x futsal_server
```
✔️ Run the server:
```
./futsal_server
```
📁 In the directory run the following command to give executive access to **futsal_monitor**:
```
chmod +x futsal_monitor
```
✔️ Run the monitor:
```
./futsal_monitor
```
## 📚 Setup the library

***Note that there will not be any conflicts between your original library and the challenge library***

The latest Challenge-lib depends on the following libraries:

- C++17
- Boost 1.41 or later https://www.boost.org/

In the case of Ubuntu 20.04 or later, execute the following commands for installing a basic development environment:
```
sudo apt update
sudo apt install build-essential libboost-all-dev autoconf automake libtool
```
To build the library, execute commands from the root of source directory:
```
mkdir build
cd build
cmake ..
make -j8
```
- ***make***

Once successfully built, you can install the library file and header files to the default installation directory (/usr/local/Challege_lib):
```
sudo make install
```
## build the base 
The latest challenge-base depends on the following libraries:

- Boost 1.38 or later https://www.boost.org/

In the case of Ubuntu 16.04 or later, execute the following commands for installing a basic development environment:
```
sudo apt update
sudo apt install build-essential libboost-all-dev cmake
```

📁 To build the team, execute commands from the root of source directory:
```
mkdir build
cd build
cmake ..
make
```

To start the challenge-base team, invoke the start script in build/bin directory:
```
./start.sh
```

## License
This repository is licensed under the AGPL-3.0 license, See [LICENSE](LICENSE) for the full license text.

## Authors
Erfan Fathi ([page](https://github.com/ErfanFathii)) & Soroush Mazloom ([page](https://github.com/SoroushGit))
