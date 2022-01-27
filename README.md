# Introduction

Write production-grade implementation focusing on simplicity, readability and efficiency. 
The code should be also fully covered by unit tests.

# Instructions and deliverables

1. Before starting to code, initialize a git repository.
2. Perform regular commits during your coding session.
3. When the exercise is done, prepare an archive containing everything (including .git folder) except build output folder.
4. Send this archive by email.

# How to build

First, extract the Google Test archive in-place (directly in 3rdparty/gtest), so that a googletest-master/ folder is available. You need to have a structure like the following:
```
<project root>/
  3rdparty/
    gtest/
      googletest-master/
        googlemock/
          ...
        googletest/
          ...
  include/
    ...
  src/
    ...
  ...
```

To build this project, you will need CMake. To download it, head to https://cmake.org/download/#latest. Under Linux, you can most likely download it from your package manager.

Once you have installed it, the following commands should suffice to create a compilable project; execute them from the project's root directory:
```bash
mkdir build && cd build
cmake ..
cmake --build .
```

This will by default generate under Windows a Visual Studio solution (if installed), or under Linux a Makefile project.

To run the tests, simply launch the produced executable:
```bash
# Under Windows with Visual Studio:
Debug\BowlingKata_Tests.exe

# Under Linux:
./BowlingKata_Tests
```

You can now start coding!

# Problem Statement

Create a program in C++, which, given a valid sequence of rolls for one line of American Ten-Pin Bowling, produces the total score for the game. 
The program should handle eventual invalid input and communicates this to the user.

## Bowling Score Rules

We can briefly summarize the scoring for this form of bowling:

- Each game, or "line" of bowling, includes ten turns, or "frames" for the bowler.
- In each frame, the bowler gets up to two tries to knock down all the pins.
- If in two tries, he fails to knock them all down, his score for that frame is the total number of pins knocked down in his two tries.
- If in two tries he knocks them all down, this is called a "spare" and his score for the frame is ten plus the number of pins knocked down on his next throw (in his next turn).
- If on his first try in the frame he knocks down all the pins, this is called a "strike". His turn is over, and his score for the frame is ten plus the simple total of the pins knocked down in his next two rolls.
- If he gets a spare or strike in the last (tenth) frame, the bowler gets to throw one or two more bonus balls, respectively. These bonus throws are taken as part of the same turn. If the bonus throws knock down all the pins, the process does not repeat: the bonus throws are only used to calculate the score of the final frame.

The game score is the total of all frame scores.
More info on the rules at: http://www.topendsports.com/sport/tenpin/scoring.htm.

## Clues

What makes this game interesting to score is the lookahead in the scoring for strike and spare. At the time we throw a strike or spare, we cannot calculate the frame score: we have to wait one or two frames to find out what the bonus is.

## Suggested Test Cases

(When scoring "X" indicates a strike, "/" indicates a spare, "-" indicates a miss)

- "XXXXXXXXXXXX" (12 rolls: 12 strikes) = 10+10+10 + 10+10+10 + 10+10+10 + 10+10+10 + 10+10+10 + 10+10+10 + 10+10+10 + 10+10+10 + 10+10+10 + 10+10+10 = 300
- "9-9-9-9-9-9-9-9-9-9-" (20 rolls: 10 pairs of 9 and miss) = 9 + 9 + 9 + 9 + 9 + 9 + 9 + 9 + 9 + 9 = 90
- "5/5/5/5/5/5/5/5/5/5/5" (21 rolls: 10 pairs of 5 and spare, with a final 5) = 10+5 + 10+5 + 10+5 + 10+5 + 10+5 + 10+5 + 10+5 + 10+5 + 10+5 + 10+5 = 150
