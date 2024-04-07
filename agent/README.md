# StarterAgent2D Base
[![GitHub license](https://img.shields.io/github/license/helios-base/helios-base)](https://github.com/helios-base/helios-base/blob/master/LISENCE)

helios-base is a sample team for the RoboCup Soccer 2D Simulator.
StarterAgent2D base is a simplified version of helios-base for the RoboCup Soccer 2D Simulator.
All programs can work with rcssserver-18.

- IranOpen RoboCup Soccer Simulator: https://rcss.ir/
- IranOpen RoboCup Soccer Simulator GitHub: https://github.com/RCSS-IR/
- The RoboCup Soccer Simulator: http://github.com/rcsoccersim/
- RoboCup Official Homepage: http://www.robocup.org/

## Quick Start

The latest helios-base depends on the following libraries:
 - Boost 1.38 or later https://www.boost.org/
 - The latest starter librcsc https://github.com/RCSS-IR/StarterLibRCSC-V2

In the case of Ubuntu 16.04 or later, execute the following commands for installing a basic development environment:
```
sudo apt update
sudo apt install build-essential libboost-all-dev cmake
```
And, install starter librcsc.

To build the team, execute commands from the root of source directory:
```
mkdir build
cd build
cmake ..
make
```

To start the agent2d team, invoke the start script in `build/bin` directory.
```
./start.sh
```

To create a binary, you can use `make-binary.sh` script.

## References

The paper about HELIOS Base:
- Hidehisa Akiyama, Tomoharu Nakashima, HELIOS Base: An Open Source
Package for the RoboCup Soccer 2D Simulation, In Sven Behnke, Manuela
Veloso, Arnoud Visser, and Rong Xiong editors, RoboCup2013: Robot
World XVII, Lecture Notes in Artificial Intelligence, Springer Verlag,
Berlin, 2014. http://dx.doi.org/10.1007/978-3-662-44468-9_46

Related works:
- Zare N, Amini O, Sayareh A, Sarvmaili M, Firouzkouhi A, Rad SR, Matwin S, Soares A. Cyrus2D Base: Source Code Base for RoboCup 2D Soccer Simulation League. InRoboCup 2022: Robot World Cup XXV 2023 Mar 24 (pp. 140-151). Cham: Springer International Publishing. https://arxiv.org/pdf/2211.08585.pdf
- Zare N, Sarvmaili M, Sayareh A, Amini O, Matwin S, Soares A. Engineering Features to Improve Pass Prediction in Soccer Simulation 2D Games. InRobot World Cup 2022 (pp. 140-152). Springer, Cham. https://link.springer.com/chapter/10.1007/978-3-030-98682-7_12
- Zare N, Amini O, Sayareh A, Sarvmaili M, Firouzkouhi A, Matwin S, Soares A. Improving Dribbling, Passing, and Marking Actions in Soccer Simulation 2D Games Using Machine Learning. InRobot World Cup 2021 Jun 22 (pp. 340-351). Springer, Cham. https://link.springer.com/chapter/10.1007/978-3-030-98682-7_28
- Hidehisa Akiyama, Daisuke Katagami, Katsumi Nitta, Team Formation Construction Using a GUI Tool in the RoboCup Soccer Simulation, SCIS & ISIS, 2006, Volume 2006, SCIS & ISIS 2006, Session ID TH-D2-5, Pages 80-85, Released September 12, 2008, https://doi.org/10.14864/softscis.2006.0.80.0
- Hidehisa Akiyama, Daisuke Katagami, Katsumi Nitta, Training of Agent Positioning using Human's Instruction, Journal of Advanced Computational Intelligence and Intelligent Informatics, Vol. 11 No.8, pp.998--1006, 2007-10-20. https://doi.org/10.20965/jaciii.2007.p0998
- 秋山 英久, 野田 五十樹, エージェント配置問題における三角形分割を利用した近似モデル, 人工知能学会論文誌, 2008, 23 巻, 4 号, p. 255-267, 公開日 2008/04/24, Online ISSN 1346-8030, Print ISSN 1346-0714, https://doi.org/10.1527/tjsai.23.255
- Hidehisa Akiyama, Itsuki Noda, Multi-Agent Positioning Mechanism in the Dynamic Environment, In Ubbo Visser, Fernando Ribeiro, Takeshi Ohashi, and Frank Dellaert, editors, RoboCup 2007: Robot Soccer World Cup XI Lecture Notes in Artificial Intelligence, vol. 5001, Springer, pp.377-384, July 2008. https://doi.org/10.1007/978-3-540-68847-1_38
- Hidehisa Akiyama, Tomoharu Nakashima, Shigeto Aramaki, Online Cooperative Behavior Planning using a Tree Search Method in the RoboCup Soccer Simulation, Proc. of 4th IEEE International Conference on Intelligent Networking and Collaborative Systems (INCoS-2012), 2012 Sep. https://doi.org/10.1109/iNCoS.2012.83
- Hidehisa Akiyama, Tomoharu Nakashima, HELIOS2012: RoboCup 2012 Soccer Simulation 2D League Champion, RoboCup 2012: Robot Soccer World Cup XVI Lecture Notes in Computer Science Volume 7500, pp.13-19, June 2013. http://dx.doi.org/10.1007/978-3-642-39250-4_2
- Takuya Fukushima, Tomoharu Nakashima, Hidehisa Akiyama, Mimicking an Expert Team through the Learning of Evaluation Functions from Action Sequences, RoboCup 2018: Robot World Cup XXII Lecture Notes in Computer Science, Vol. 11374, Springer, Cham, pp 170-180, 04 August 2019  https://doi.org/10.1007/978-3-030-27544-0_14
- Hidehisa Akiyama, Tomoharu Nakashima, Takuya Fukushima, Jiarun Zhong, Yudai Suzuki, An Ohori, HELIOS2018: RoboCup 2018 Soccer Simulation 2D League Champion, RoboCup 2018: Robot World Cup XXII, Lecture Notes in Computer Science, Vol.11374, Springer, Cham, pp.450-461, 04 August 2019. https://doi.org/10.1007/978-3-030-27544-0_37
- 福島卓弥, 中島智晴, 秋山英久, RoboCupサッカーにおけるニューラルネットワークを用いた評価関数モデリング, 電気学会論文誌Ｃ（電子・情報・システム部門誌）, 2019, 139 巻, 10 号, pp. 1128-1133, 2019-10-01 https://doi.org/10.1541/ieejeiss.139.1128
- 秋山 英久, 中島 智晴, 五十嵐 治一, RoboCup サッカーシミュレーションにおける局面評価の表現法と学習法, 知能と情報, 2020, 32 巻, 2 号, p. 691-703, 公開日 2020/04/15, Online ISSN 1881-7203, Print ISSN 1347-7986, https://doi.org/10.3156/jsoft.32.2_691
- Takuya Fukushima, Tomoharu Nakashima, Hidehisa Akiyama, Evaluation-function modeling with multi-layered perceptron for RoboCup soccer 2D simulation, Artificial Life and Robotics, Volume 25, issue 3, pp.440-445, 2020-04-30. https://doi.org/10.1007/s10015-020-00602-w

