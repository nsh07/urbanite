# Shell script to create a .deb file out of the compiled binaries of this
# program. This script is not intended to be run as-is. Run `make deb` instead,
# which calls this script after ensuring that the program is compiled
# successfully.

echo "---Running build-deb.sh---"
printf "Arch of compiled binary [amd64/armel/i386 etc]: "
read arch
version=$(bin/urbanite --dumpversion) # Version string
size=$(du -ch -B "K" bin/urbanite fonts | tail -n1 | cut -d "K" -f 1) # Size variable for Installed-Size
mkdir -p deb-build

# File 1: debian-binary
echo -e "\e[90mCreating debian-binary file..."
echo "2.0" > deb-build/debian-binary
echo "...done"

# File 2: control.tar.xz
echo "Creating control file..."
echo "Package: urbanite" > deb-build/control
echo "Package-Type: deb" >> deb-build/control
echo "Version: " $version >> deb-build/control
echo "Maintainer: Nishant Mishra <nmrocks2828@gmail.com>" >> deb-build/control
echo "Description: Search words on Urban Dictionary at the comfort of your terminal" >> deb-build/control
echo " Urbanite is a program for searching words on Urban Dictionary" >> deb-build/control
echo " (https://urbandictionary.com) from within a terminal emulator/shell/tty." >> deb-build/control
echo -e " .\n Urbanite features a Figlet-style word heading, customizable figlet fonts for" >> deb-build/control
echo " the heading, definition stats (like/dislike counts and ratios) and more." >> deb-build/control
echo "Section: utils" >> deb-build/control
echo "Priority: optional" >> deb-build/control
echo "Installed-Size: $size" >> deb-build/control
echo "Architecture: $arch" >> deb-build/control
echo "Bugs: https://github.com/NMrocks/urbanite/issues" >> deb-build/control
echo "Depends: libcurl4" >> deb-build/control
echo "Suggests: curl, figlet" >> deb-build/control
echo "...done"

# File 3: data.tar.xz (not archived here)
echo "Organizing data files..."
mkdir -p deb-build/usr/bin && mkdir -p deb-build/usr/share/urbanite
cp bin/urbanite deb-build/usr/bin/ && cp fonts/* deb-build/usr/share/urbanite/
echo "...done"

# Archiving file 1 (control)
echo "Creating control.tar.xz..."
cd deb-build
tar -cv -f control.tar ./control
xz -vf control.tar
echo "...done"

# Archiving file 2 (data)
echo "Creating data.tar.xz..."
tar -cv -f data.tar ./usr
xz -vf data.tar
echo "...done"

# Creating final debian archive
echo "Creating final debian archive..."
ar -rv "../bin/urbanite-$version-$arch.deb" debian-binary control.tar.xz data.tar.xz
echo -e "File urbanite-$version-$arch.deb created successfully in bin\e[0m"
cd ..
