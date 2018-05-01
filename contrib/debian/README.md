
Debian
====================
This directory contains files used to package fxrated/fxrate-qt
for Debian-based Linux systems. If you compile fxrated/fxrate-qt yourself, there are some useful files here.

## fxrate: URI support ##


fxrate-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install fxrate-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your fxrate-qt binary to `/usr/bin`
and the `../../share/pixmaps/fxrate128.png` to `/usr/share/pixmaps`

fxrate-qt.protocol (KDE)

