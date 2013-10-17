BGS-dev
=======

Blood Gold and Sorcery is a graphical roguelike, like Dungeon Crawl: Stone Soup or Doom the Roguelike.

But, what is a roguelike ?
--------------------------

Definitions are boring, so here's one from Wikipedia:
*The roguelike is a sub-genre of role-playing video games, characterized by level randomization and permanent death.*
The most famous of all may be Rogue, DCSS or Diablo (yes that's a roguelike !).

Development
-----------

BGS is a C++ game using SFML 2.0 ([http://www.sfml-dev.org/index.php](http://www.sfml-dev.org/index.php)) and BOOST library.

Compiling
---------
BGS need SFML 2.0, boost::filesystem and boost::archive.
####Linux user

    git clone https://github.com/CaptainGobelin/BGS-dev
    cd ./BGS-dev
    cmake . -G"Unix Makefiles"
    make bgs

To compile utils softs, there's no cmake, but a simple makefile (using g++):

    cd ./utils/[soft file name]
    make [make rule]

Look at the makefile to know the make rule.

####Windows user

Use Git et CMake GUI. (I will complete this section step-by-step later)