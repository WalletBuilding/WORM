
Debian
====================
This directory contains files used to package wormd/worm-qt
for Debian-based Linux systems. If you compile wormd/worm-qt yourself, there are some useful files here.

## worm: URI support ##


worm-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install worm-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your wormqt binary to `/usr/bin`
and the `../../share/pixmaps/worm128.png` to `/usr/share/pixmaps`

worm-qt.protocol (KDE)

