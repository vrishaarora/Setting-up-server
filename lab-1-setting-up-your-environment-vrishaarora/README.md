# Lab 1: Setting up your Development Environment

> Author(s): Andrew Lvovsky (@borninla) and Brian Crites (@brrcrites). Updated by Neftali Watkinson (@neftaliw) and Reem Ali (@reem-ali)

Welcome to CS 100 Software Construction! In this first lab you will be introduced to the tools needed to succeed in this course. The topic you will see today are:

- Using SSH and basic navigation of a Linux operating system
- Compiling with g++
- Introduction to GitHub
- Setting up an Integrated Development Environment

There are many reasons Linux is still used in industry today, ranging from its open-source nature to its excellent stability. There are various versions of Unix/Linux, known as distributions, which are built from a relatively small number of base kernels. In this course, we will be logging into and using a server provided by the university named `cs100`. In addition to learning Linux basics, we will also (re-)introducing g++, CMake, Git and GitHub in this lab.

> Note: any text surrounded by angle brackets `< >` represent a portion of text that is specific to you and needs to be replaced. Make sure you replace that portion with what is requested in the lab description.

# Part 1: Connecting to the server
For this part you will learn how to connect to a server using SSH and setting up your repository. 

## SSH into the CS100 Server 

You will need to log into the `cs100` server using a [Secure Shell (SSH)](https://www.ssh.com/ssh/protocol) application. This server will be used to host all your labs and allows us to maintain a consistent environment for everyone. 

### Linux or Mac
If you are using a Linux or Mac computer, you can run the following command in the terminal:

```sh
ssh <your_CS_username>@cs100.cs.ucr.edu
```
You will then input your CS password to log in.
> Replace <your_CS_username> with the username provided to you by the CS department. If you do not yet have a CS account ask your TA to help you register a new account (some students will need to go through CS systems to get an account, your TA will advise you if this is the case).

### Windows 10 or newer
If you are using a Windows computer, first make sure that it is up to date. Windows doesn't come with SSH enabled by default, so before you can use it form the terminal, you need to enable OpenSSH. To do so follow the next steps:
- Open the Start menu (pressing the Windows key or clicking on the Windows logo in your taskbar)
- Open the settings menu (gear logo on the left side of the menu or by typing "Settings")
- Click on "Apps", then "Optional Features"
- Click on the plus (+) sign next to add a feature.
- Search for "SSH" and choose the "OpenSSH Client"
- Click install

Now you can open a Command Prompt (Start menu -> CMD) or PowerShell terminal (Start menu -> Powershell) and test your SSH connection by running the following command:

```sh
ssh <your_CS_username>@cs100.cs.ucr.edu
```
If this method fails, follow the instructions for Windows 8 computers.

### Windows 8 or older
If you are using a Windows 8 or earlier computer, you will first need to install a program called PuTTY, which can be installed from [putty.org](http://www.putty.org/). When you open PuTTY, there will be a box for a “Host Name”, where you will input `<your_CS_username>@cs100.cs.ucr.edu`.  It is also possible to use ssh on Windows through [cygwin](http://www.cygwin.com/) or [WSL](https://docs.microsoft.com/en-us/windows/wsl/about), both of which emulate a Linux-like environment within Windows.

### General tips
You may be asked to exchange keys with the server (which you should allow). Next, you will be prompted for your password. You should note that when typing your password, no characters will be displayed even though you are still typing (this is a security measure).

To terminate the SSH connection, enter the following command:
```sh
exit
```

> Note: You are not required to develop on the `cs100` server for this course and are encouraged to use your own development environment. However, you will need to validate that your code will run correctly on the `cs100` server as we cannot account for differences in everyone's individual development environments. You are required to host your code on GitHub.


## The Linux File System

The Linux file system is similar to most other file systems. It is helpful to envision a file system like a tree. You have a root directory (node), denoted simply by `/` in Linux and Mac and typically `C:\` in windows, which has many children that are directories that all live in the root directory. Each of those directories can then hold other directories, which can hold other directories, etc. with as many levels as the user would like.

When you logged into `cs100`, you should've been placed into your user root directory (also called your home directory). To verify this, please type `pwd`, the command to "print working directory" or the current directory you are in. You should see the path `/home/csmajs/<your_CS_username>` (where `<your_CS_username>` is your CS username from before) if you are in a CS related major or `/class/classes/<your_CS_username>` if you are taking this course as a service course for your major. If your path is not similar, type `cd ~` where the `~` character is a special character reserved by your terminal to represent your personal home directory. `cd` is the command used to "change directories" and expects a relative or absolute path as an argument (we will explain the difference between paths shortly).

One important thing to note at this point is that you are working on a server which can, and likely currently does, have multiple users connected to it at the same time. You can type the command `who` to see "who" is currently logged into the server. Each of these users has their own username, directories, processes, and resources on the server. This means that each user has a different `~` home directory that typing `cd ~` will take them to. This is an important concept to remember in order to develop programs which are portable and will work across users, but more on that later.

Go ahead and type the following command:

```sh
mkdir example_dir
```

This will create a new directory in your current directory, which (if you ran the last command) should be your home directory. To change into the new directory type `cd example_dir`. Then type `pwd` and you should see your path updated to something like `/home/csmajs/<your_CS_username>/example_dir`. To go back to the directory above, which should be your home directory, type `cd ..`. The two dots `..` represent a reserved directory that denotes the directory above your current directory, known as the parent. There is another reserved single dot directory `.` which represents the current working directory and we'll cover its usage later in this lab. Reserved directories like these make it easy to move up and down the directory structure in a relative manner without having to type the full path to the directory each time.

Now, type the following command:

```sh
cd /home/csmajs/<your_CS_username>/example_dir
```

Notice that you are in the same directory as before (you can verify by running `pwd`). The only difference was which type of path you passed in. In the prior case the `example_dir` in the command `cd example_dir` was a relative path, since you are changing directories *relative to* your current directory. The path `/home/csmajs/<your_CS_username>/exampale_dir` used in `cd /home/csmajs/<your_CS_username>/example_dir` is an absolute path, since it starts with the root directory `/`. All paths which start from the root directory `/` are absolute paths, otherwise the path is relative, although in both cases the path could be valid or invalid.

> Note: Your user root (home) directory is different from the server's root directory. Your home directory is attached to your account and resides as a directory specifically created to hold your files (directories like these are automatically created when new users are added). The system's root directory is the highest (or lowest depending on your view) path on the server and has no parent directory (if you `cd ..` from `/` it will send you back to `/`).

Go back to your home directory (`cd ~`) and type the command `ls` which lists the contents of a directory. You should see the directory `example_dir` we created before as the only entry. Now type `ls -a` and you should see additional "hidden" files which start with a dot (`.`). Any file (even ones you create) that start with a dot are considered hidden files by the system and won't be shown with a normal `ls` command. These files are typically system or configuration files which are used by various systems, such as version control or build systems, or Linux itself, such as `.` and `..`. 

Now that we've demonstrated how to create and traverse directories, let's go ahead and delete `example_dir`. Make sure you are in your home directory, then type:

```sh
rm -rf example_dir
```

`rm` is the command used to "remove" files or directories. If you have a regular file you can enter `rm <filename>` without any flags. However, since we are dealing with a directory we need to add the extra `-rf` options. `r` recursively removes files and directories within the directory you are removing and 'f' ignores nonexistent files and doesn't prompt the user to confirm each deletion. That said, with great power comes great responsibility. Use `rm -rf` only when necessary. The last thing you want is to accidently delete important files or directories.

> Note: There are two useful ways to learn about the usage of a command (including a list of options available and what they do).  The first is the `man` utility (as in "owner's *man*ual").  You can type `man ls` to see usage instruction for the `ls` command.  In addition, most commands are self-documenting and support the `--help` flag. You can get similar information for `ls` by running `ls --help`.

## The `.bashrc` File

Another example of a hidden file used by a system is the `.bashrc` file, which you should see when running `ls -a` from your home directory (`~`). The `.bashrc` file is a config file that is executed every time your terminal loads such as when you login to `cs100` over SSH. Go ahead and type `cat ~/.bashrc` to view its contents. You should see something like below:

```sh
# .bashrc

# Source global definitions
if [ -f /etc/bashrc ]; then
    . /etc/bashrc
fi

# Uncomment the following line if you don't like systemctl's auto-paging feature:
# export SYSTEMD_PAGER=

# User specific aliases and functions
```

The `cat` command is short for "concatenate" which has a lot of different uses, but here we are using it to output the contents of the file to the terminal. 

For this course, you might use Python for your final project and for some lab assignments. The `cs100` server has both Python 2 and Python 3. Since Python 2 has been deprecated for a while, we would like a way to refer to Python 3 by just using the keyword `python`. Right now, you need to add the number 2 or 3 at the end to specify which one you are going to use. To solve this, we are going to use an alias. We will be using Vim here to add the necessary code to the `.bashrc` file.

> Note: If you are unfamiliar with command line editors, you should read these tutorials for [Vim](https://www.linux.com/tutorials/vim-101-beginners-guide-vim/) or [Emacs](http://www.jesshamrick.com/2012/09/10/absolute-beginners-guide-to-emacs/) to get started. Knowing at least one command line editor is extremely important since most servers (especially cloud-based server instances) do not have visual interfaces, so the only way to make changes to files on them is through a command line editor.

Make sure you are in your home directory and type `vim .bashrc` to open the `.bashrc` file for editing in Vim. Vim is designed to allow programmers to work quickly, so it tries to keep you hands on the home row of the keyboard as much as possible. It uses the `j` key to move down, the `k` key to move up, the `l` key to move right, and the `h` key to move left. Move down to the line that has `# User specific aliases and functions` using these keys. Next, hit `Shift-A`. This will move your cursor to the end of the line and put you in Insert mode. Vim has multiple modes, the major ones of which are normal mode which takes key commands as `hjkl` to move or `Shift-A`, and insertion mode, which allows you to type text like you would in a word document (there is also a visual mode which is very useful, but we won't cover it here). You can tell if you are in insert mode by the **-- INSERT --** at the bottom of your window and can use the Esc key to go back to normal mode. 

Go ahead and press Enter while in Insert mode to go to (and create) the next line. Type in `alias python=python3`, then hit the Esc key to go back to normal mode. Type `:` to enter a command sequence followed by `wq` which represent writing the file (`w`) and quitting the program (`q`) and hit Enter. The `:` puts you in command mode which is very powerful in Vim and will let you do everything from [replace all behavior](https://www.linux.com/tutorials/vim-tips-basics-search-and-replace/) to [running bash commands without exiting Vim](https://www.linux.com/tutorials/vim-tips-working-external-commands/). Congrats! You have added your first user-specific alias into `.bashrc`. Now, run `source .bashrc` to make sure the new alias is loaded (you need to do this to reload the file, otherwise you would need to quit `cs100` and log back in for the `.bashrc` file to load).

There are more advanced uses of the `.bashrc` file. For students with Linux and macOS machines: try making an alias in your local machine's `.bashrc` file for logging into `cs100`. Something like this will work:

```sh
alias cs100="ssh <your_CS_username>@cs100.cs.ucr.edu"
```

## Command Line Compilation

GCC is the GNU project C Compiler and is one of the most used compilers for C code (macOS previously used GCC but now uses another compiler called Clang.  GCC and Clang are largely compatible, and g++ is often aliased to clang on MacOS.). It typically also comes with G++, which is used for C++ code. The `g++` command invokes this compiler from the command line. To demonstrate how it works, go ahead and write a simple `hello world!` program using the command line editor of your choice (save the file as `main1.cpp`):

```c++
#include <iostream>

using namespace std;

int main()
{
    cout << "hello world!" << endl;
    return 0;
}
```

Once finished make sure to save and quit out of your editor and then type the following command in the terminal:

```sh
g++ -std=c++14 main1.cpp
```

> Note: Most shells support autocompletion when typing out commands and is useful when you have a command with many arguments to type out. For example, start typing `g++ -std=c++14 ma`. After typing `a`, press the Tab key. Bash (the shell you are currently using in `cs100`) should autocomplete to `main1.cpp`.

If successful, you shouldn't see any output (if not successful, fix your errors until you are able to compile your program). A quick `ls` will show that a new file named `a.out` was generated, which is the executable generated from your program. You execute this executable (also known as a binary) with `./a.out`. Note that the `.` in this case is the current directory and is required [primarily for security reasons](https://stackoverflow.com/questions/6331075/why-do-you-need-dot-slash-before-executable-or-script-name-to-run-it-in-bas). When you execute your program you should see "hello world!" printed out to the terminal.

> Note: The above command will work without the `-std=c++14` flag. By default, g++ (6.1 and newer) will compile to the C++14 standard but it will soon migrate to C++17. It is good to know how to change the standard in case you need to.

Most of the time you want to give your program a recognizable name. Adding the `-o` "output" flag followed by a name and the executable will output with that name. Go ahead and run `rm a.out` to delete the old executable, then run the following command:

```sh
g++ -o hello_world main1.cpp
```

> Note: other useful flags that are commonly used include `-g` (add debugging information), `-O2` or `-O3` (optimization flags), and `-Wall` (enable all warnings).

You have now created an executable called `hello_world` and can execute it by typing `./hello_world`.

When developing larger programs in object-oriented languages (like you will in this class), it is common to break up work into multiple source and header files (in C++'s case, `.cpp`/`.cxx`/`.cc` for source files and `.hpp`/`.h` for header files). The g++ compiler allows you to compile multiple files into a single executable.

Before we write our files, lets create some directories to separate our files and make things easier to find. Create a `src` directory and a `header` directory where we will put the respective source and header files. We will be creating a simple Rectangle class which has a height and width and calculates the rectangle's area. Go ahead and make a header file called `rectangle.hpp` in the `header` directory, and add the following code:

```c++
#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

class Rectangle {
    private:
        int width;
        int height;
    public:
        void set_width(int w);
        void set_height(int h);
        int area();
};

#endif /* RECTANGLE_HPP */
```

> The `#ifndef`, `#define`, and `#endif` are known as [sharp guards or include guards](https://www.cprogramming.com/tutorial/cpreprocessor.html) and cause the compiler to only include this file once even when its referenced multiple times. It is a good idea to add these to the top of all your header files, and we will cover them more in a future lab.

> Tip: Inclusion guards rely on the use of a token (`RECTANGLE_HPP` in the code above) that is unique; the token must not be used for any other purpose (including names of variables, classes, or functions).  This token is often formed from the name of the file, but be careful if your source contains header files in different directories with the same name (or if you are using a library that contains a file with the same name).  Clashes between inclusion guards commonly occur when copying a header but forgetting to change the inclusion guard token.  This mistake leads to very perplexing compiler errors, usually that the compiler cannot find a class or function that is defined in a header that has been included.

Also create a source file called `rectangle.cpp` in the `src` directory, and add the following code:

```c++
#include "../header/rectangle.hpp"

void Rectangle::set_width(int w) {
    this->width = w;
}

void Rectangle::set_height(int h) {
    this->height = h;
}

int Rectangle::area() {
    return this->width * this->height;
}
```

Finally, overwrite your current `main1.cpp` with following code:

```c++
#include <iostream>
#include "../header/rectangle.hpp"

using namespace std;

int main()
{
    Rectangle rect;
    rect.set_width(3);
    rect.set_height(4);
    cout << "Rectangle area: " << rect.area() << endl;
    return 0;
}
```

The `main1.cpp` file was not created in the `src` directory so we should move it there. You can use the command `mv <source> <destination>` to move a file from `<source>` to `<destination>` where the `<source>` is a file and the `<destination>` is a file or folder. From your home directory where `main1.cpp` should be use `mv main1.cpp src/` to move `main1.cpp` into the `src` directory. If you added a filename after `src/` in the destination part of the move command, it would also rename the file. If its omitted, it will use the source files name (which is fine in this case). The `mv` move command is used for both moving files and renaming them. 

We are now ready to compile and run! Go ahead and run the following command (notice that the `g++` command can take relative paths, so the command below is being run from your home directory):

```sh
g++ -o area_calculator src/main1.cpp src/rectangle.cpp
```

Notice that we didn't include the header file `rectangle.hpp` as an argument. The `#include "rectangle.hpp"` within `rectangle.cpp` tells the compiler to include the header for us (and is why the include guards are necessary). Nice! Go ahead and run `./area_calculator`. You should see `Rectangle area: 12` as output.

> Tip: Specifying a header file as an argument to the compiler is not necessarily an error, but it may do something very different from what you might expect.  This may lead to errors that are very difficult to track down, such as causing the compiler to *not notice* changes made to the header file.  In the case of `g++` and `clang++`, it will create a `.gch` file; deleting this file will resolve the problem.

### Make

Now we briefly introduce Make, which is a GNU project build automation tool. Make is essentially a scripting language for building executables from source code. It works by reading a `Makefile` (that is the required file name) which is a text file that tells Make how to build the target program. The `Makefile` is made up of rules that look like the following:

```make
target: dependencies ...
    commands
    ...
```

Let's go ahead and create a `Makefile` for our program above. Add the following rule into the `Makefile`:

```make
area_calculator: src/main1.cpp src/rectangle.cpp
    g++ -o area_calculator src/main1.cpp src/rectangle.cpp
```

Now go ahead and run `make` in your terminal and you should see the rule's command displayed as output. Using `make` allows you to save lots of time typing out compilations commands so you don't need to keep entering `g++ -o area_calculator main1.cpp rectangle.cpp` over and over again when making edits to the source files. It also allows you to create multiple executables from a single command. However, we won't be using Make directly in this course but instead a more powerful system.

### CMake

[CMake](https://cmake.org/) is a build system built on top of GNU's `make` and supports some more advanced features. The CMake system looks for a `CMakeLists.txt` file (again this is the required file name) in order to know what to build. Start by creating the following `CMakeLists.txt` file:

```cmake
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

ADD_EXECUTABLE(area_calculator
    src/main1.cpp
    src/rectangle.cpp
)
```

The first function, `CMAKE_MINIMUM_REQUIRED`, sets the minimum version of CMake that can be used to compile this program. The function `ADD_EXECUTABLE` tells CMake to create a new executable named after the first parameter in that function, in this case `area_calculator`. We then list all the `.cpp` files which need to be included in that executable. Earlier, we mentioned that CMake is built on top of `make`. To be more specific, it generates really good Makefiles. Run the following command from the terminal in order to generate a new Makefile to compile your program:

```sh
$ cmake .
```

This command invokes the CMake build system in the local directory (where our CMakeLists.txt file is located). 

CMake should now have generated a new `Makefile`, so execute the `Makefile` with the `make` command. You should see a nicely designed build percentage which will generate a new `area_calculator` executable.

```sh
$ make
Scanning dependencies of target area_calculator
[ 33%] Building CXX object CMakeFiles/area_calculator.dir/src/main1.cpp.o
[ 66%] Building CXX object CMakeFiles/area_calculator.dir/src/rectangle.cpp.o
[100%] Linking CXX executable area_calculator
[100%] Built target area_calculator
```

As you may have guessed CMake and Make both allow you to generate multiple executables. In this class we will use this functionality to build executables for the regular program and for testing. Let's try creating another executable by creating another main which runs a slightly different program. Create a file with the following code named `new_main.cpp` in the `src` directory:

```c++
#include <iostream>
#include "../header/rectangle.hpp"

using namespace std;

int main()
{
    Rectangle rect;
    rect.set_width(15);
    rect.set_height(30);
    cout << "Rectangle area: " << rect.area() << endl;
    return 0;
}
```

Now add the following snippet of code to the `CMakeLists.txt` file you created previously:

```cmake
ADD_EXECUTABLE(bigger_area_calculator
    src/new_main.cpp
    src/rectangle.cpp
)
```

Now if you run `cmake .` and `make` you will see two executables generated `area_calculator` and `bigger_area_calculator`. If you want to only build one of the executables (for example if you updated only one of the mains) then you can invoke `make` with the name of the executable you want it to build, `make area_calculator` for example, and it will only build that one executable.

## Intro to Git and Github

### Git Config

Git is a local program for performing version control which is usually paired with a remote Git server for saving code off site. GitHub is a web-based Git repository which your local Git program is capable of interfacing with. Git and GitHub are therefore two separate systems and Git needs to be configured correctly in order for your code changes to be tracked and attributed correctly on GitHub. You should run the following commands on any new system you are committing from before you start working (these can be run from any directory and only have to be run once per system):

```sh
git config --global user.name "<github-username>"
git config --global user.email <github-registered-email>
```

GitHub will use the email that you configure with your Git client to track which users are making which changes. This means that you'll need to use the email address you've registered with GitHub in the above configurations (otherwise you may see commits from an anonymous user). In this course we look at commits and who made them to make sure partners in the projects and labs are contributing equally, so having misattributed commits may lead to point deductions. If you have a few which are misattributed this is not an issue but you should configure your client quickly after you notice the problem to correct the issue.

### GitHub Authentication

In order to access GitHub from the terminal, you will need a personal access token. To create a personal access token, follow [these instructions](https://docs.github.com/en/authentication/keeping-your-account-and-data-secure/managing-your-personal-access-tokens#creating-a-personal-access-token-classic) to create a classic personal access token. When prompted for scopes, you can select all of them.

### Git Init & Clone

New Git repositories can be created either locally using the Git client or through GitHub directly. Make sure you are back at your home directory (`cd ~`) and run the following commands on the terminal in `cs100`:

```sh
mkdir lab-01
cd lab-01
```

Then to initialize that directory as a Git project, use the following Git command:

```sh
git init
```

This will create a hidden `.git` repository (which you can see with `ls -a`) that holds all the information that Git uses to keep track of your files and changes. The folder is hidden because it begins with a period (recall earlier in the lab) and is typically not modified by users directly.

However, you use a different method if you want to receive a copy of an already existing repository, which you will do for all of the labs and assignments in this course. Rather than initializing a new repository, you will make a “clone” of a repository that already exists. Start by moving out of the Git project you just created and removing that directory:

```sh
cd ..
rm -rf lab-01
```

Now, go to the upper right of this page and click the “Code” dropdown. A box will appear that should say “Clone” and the HTTPS tab should be selected with an HTTPS link displayed (if it says “Clone with SSH”, then be careful to click the tab to the left that says “HTTPS”).

Copy the link in the box below, this is the GitHub repository url which you will use to clone that repository. Now, run the following command:

```sh
git clone <github-url>
```

Make sure to replace the above `<github-url>` with the url that you copied from the “Clone or download” box. This will create a new folder named `lab-01-intro-to-sct-...` with some additional text based on your username/groupname. This new directory is a copy of the GitHub repository and is already initialized as a Git project. Move into this new directory and we can begin modifying it.

> Note: README.md files are special in GitHub repositories. The contents of the README.md file in the repository's root will actually be rendered along with a list of files for anyone who visits the repository. The hash (#) at the beginning of the line is part of GitHub Markdown which specifies that this line should be a title. [You can read more about GitHub Markdown here](https://guides.github.com/features/mastering-markdown/).

### Git Status, Add & Commit

Remember our program and its source/header files from earlier? Go ahead and move all of those files (including src/header files) into the new `Lab-1-Setting-up-your-environment...` folder.

Git doesn’t automatically keep track of new files for us. Instead, we have to tell Git to start tracking these new files. Run the following command:

```sh
git status
```

The `status` command lists the current status of your Git repository, mostly showing which files have changes. In the output, there is a section labeled "untracked files." Notice the files in that section. This means that Git knows these files exist, but isn’t currently keeping track of changes to them. We want to keep track of all the `.cpp` `.hpp` files and `CMakeLists.txt`, but not the `area_calculator` file since that should be recompiled to run correctly on different machines. It is important to note that Git does not automatically save changes to your files either locally or on GitHub. When you have made a set of changes that you want to save, you will have to use the commands we are going to introduce below so you will use these commands very often.

We don’t want Git to continue to tell us that `area_calculator` is untracked, but luckily Git has a solution for this problem. You can create a file called `.gitignore` that will contain a list of all of the files that you want Git to ignore when it tells you what is/isn’t tracked and modified. To ignore a file, add the name of that file on a new line of `.gitignore`. Now create a file named `.gitignore` and add `area_calculator` to it. Now run `git status` again and take a look at the output. Notice that `area_calculator` is no longer listed, only the `.cpp`, `.hpp`, `CMakeLists.txt` and the new `.gitignore` files are listed as untracked. Now, we can add all of these files to our project with the following commands:

```sh
git add header/rectangle.hpp
git add src/rectangle.cpp
git add src/main1.cpp
git add src/new_main.cpp
git add CMakeLists.txt
git add .gitignore
```

> Note: Do not add executables, object files, or temporary files which are re-generated during compilation to your git repo, only add source files and other necessary files for your submission (these are listed in the assignment specifications). Tracking executables uses LOTS of disk space and they are unlikely to work on other people's machines. **If we see these files in your Git repos, your grade on the assignment will be docked 20%**. You should use a `.gitignore` file so that they don’t appear in your Git status or accidentally get added to your repository.  The `.gitignore` file supports wildcards, so that the entry `*.o` will cause all object files to be ignored.

Now, when we run Git status, there is a section labeled "Changes to be committed" with the files that were just added underneath it. This means that Git now thinks these files are part of the project and will begin to track changes to it.

Whenever we finish a task in our repo, we "commit" our changes. This tells Git to save the current state of the repo, made up of all the files we’ve added, so that we can come back to it later if we need to. Commit your changes using the command:

```sh
git commit -m "Add initial files"
```

Every commit needs a "commit message" that describes what changes were made in the repo. Writing clear, succinct, informative commit messages is one of the keys to using Git effectively. In this case we passed the `-m` flag to Git so we could write the commit message in the command line. If we did not pass a flag, then Git would have opened the Vim editor for us to type a longer commit message which is useful when you are commiting more major changes which require more explanation.

That was not a very informative commit message, so let's edit it to be something more informative. Anytime you need to modify the last commit that you made, you need to amend it, which is done through the following command:

```sh
git commit --amend
```

Running this allows you to edit the last commit that you made, including which files were included in that commit. Anything that you have done a `git add` to before running `git commit --amend` will be added to the last commit in addition to allowing you to edit the commit message.

> Note: the --amend flag will let you add anything to the previous commit, even if it's not a good idea. Because of this you should use it carefully and for situations where you have forgotten a minor change (README, comment, better commit message) or your last commit did not actually function correctly and you need to “patch” it.

We didn’t write an informative commit message, so we should modify it to be something more useful. Run the `git commit --amend` command. You should see something like the following open in either Vim or Emacs.

```
My first commit
  
# Please enter the commit message for your changes. Lines starting
# with ‘#' will be ignored, and an empty message aborts the commit.
#
# On branch brrcrites/lab-01
# Changes to be committed:
#   added:   header/rectangle.hpp
#   added:   src/rectangle.cpp
#   added:   src/main1.cpp
#   added:   .gitignore
#
# Changes not staged for commit:
#
# Untracked files:
#
```

While you can write any message that you want here, GitHub will do some automatic formatting based on past good practices for writing commit messages that you should adhere to. 

* The first line will be formatted as a subject line, and cut off at 50 characters. You should therefore pick a concise subject message that is < 50 characters long 
* You should separate the first line from the rest of your body text with a blank line
* The body of your message (anything else you add after the subject but before the commented lines) should describe what changes occurred and why, rather than how you did it. This is often formatted as a bulleted list using a * as the bullet.

Following these rules will make your commits nicely formatted on GitHub and easier to understand and process. Let's update our commit message to the following:

```
Add rectangle area program

* Added Rectangle class files and main file that calculates the rectangle's area
  
# Please enter the commit message for your changes. Lines starting
# with ‘#' will be ignored, and an empty message aborts the commit.
#
# On branch brrcrites/lab-01
# Changes to be committed:
#   added:   header/rectangle.hpp
#   added:   src/rectangle.cpp
#   added:   src/main1.cpp
#   added:   .gitignore
#
# Changes not staged for commit:
#
# Untracked files:
#
```

After editing the file with the above message, exit your editor and the commit should update.

> Note: The -m flag should only be used when writing very short commit messages, and otherwise you should use the interactive mode to have both a subject and commit body. For some more tips on writing effective git commit messages, read [this blog post](https://chris.beams.io/posts/git-commit/).

> Tip: There are many useful shortcuts that can be used to speed up common workflows.  Multiple files can be added at once: `git add file1 file2 file3`.  You can also specify files to commit directly: `git commit file1 file2 file3`.  You can commit all modified files with `git commit -a`, but be very careful to check first that you actually want to commit all modified files in one commit.

Let's make one more commit so we'll have something to play with. Update your `main1.cpp` to calculate one more rectangle's area:

```c++
#include <iostream>
#include "../header/rectangle.hpp"

using namespace std;

int main()
{
    Rectangle rect1, rect2;
    rect1.set_width(3);
    rect1.set_height(4);

    rect2.set_width(4);
    rect2.set_height(2);

    cout << "Rectangle 1 area: " << rect1.area() << endl;
    cout << "Rectangle 2 area: " << rect2.area() << endl;

    return 0;
}
```

Now run:

```sh
git commit -m "Add one more rectangle and compute its area"
```

Uh oh! We got an error message saying: "no changes added to the commit".

Every time you modify a file, you must explicitly tell Git to add the file again if you want that file included in the commit. This is because sometimes programmers want to commit only some of the modified files. 

Run `git status` to see the files that are currently being tracked. We can add the changes to the `main1.cpp` file, and verify it is added, with:

```sh
$ git add main1.cpp
$ git status
```

We can then commit the changes using:

```sh
$ git commit -m "Add one more rectangle and compute its area"
```

> Note: `git add` is used for several *different* tasks, such as telling git to start tracking a new file, "staging" a modified file for a subsequent commit, or signifying that a conflict has been resolved (we will visit conflicts later).  `git rm` and `git mv` can be used to remove or move files; they work the same way as the regular `rm` and `mv` commands, but they also tell git to make the corresponding changes to the repository.


# Part 2: Setting up an IDE
For this part you will install an IDE and then connect that to the same CS100 server and repository described in part 1.

## IDE
An IDE, or integrated development environment, is a piece of software that provides an integrated solution for coding. Generally, an IDE will have a code or text editor (often with syntax highlighting), some form of build automation, and a debugger. By definition, tools such as Vim or Notepad are editors that can be used to edit or create code files, but they are not IDEs. On the other hand, Notepad++, Netbeans, Eclipse, and Visual Studio are considered to be IDEs because they provide the three basic features we mentioned plus many others. You just finished creating, compiling and executing code without the need for an IDE, therefore they are not critical to writing software. However, IDEs provide tools that make it easier to scale up projects, collaborate with other, and make development easy.

### How to choose an IDE?
There's no such thing as the "best" IDE. In the end they are tools. We can argue that a nail gun is a more sophisticated tool than a hammer, and yet professionals still have hammers in their tool set (some have [multiple hammers](https://youtu.be/fNbNFBNyNA0)). In the end, it is about which tool will help you get the job done and what features are important for you (or which IDE your company wants you to use). 

Even though the choice of an IDE is personal. Feel free to use the following guiding points for picking the one that best fits your needs:
- Does the IDE support the programming languages I am going to use? (Bonus: is it recommended by the development community as a good option for those languages)
- Is it mature and well supported?
- Does it support collaboration and a direct connection to a repository?
- Does it support other technology I will use for my project? (connecting to servers, alternative testing frameworks, etc.)
- Does it have code autocomplete?
- Does it work with my operating system?
- Do I have to pay a license for it?

In this class you will gain experience with a specific IDE. We didn't choose it because it is "the best", and you are encouraged to get experience with other IDEs after CS100. For now, however, we want you to use Microsoft's Visual Studio Code and learn many of its features.

> Historical trivia: On of the CS servers is called "hammer". We used to do CS100 labs on that server because it was widely available, stable, reliable, and familiar. Not unlike a real hammer. As it got older and CS100's material demanded new tools, we moved into another server. 

## Microsoft's Visual Studio Code
Commonly referred to as VS Code, it is a [freeware](https://en.wikipedia.org/wiki/Freeware) application based on open source code (note that VS Code itself is proprietary but the source code has been released under an [MIT License](https://opensource.org/licenses/MIT)). We chose it because it is a lightweight, well supported, widely used IDE that includes all major features that most consider essential for development plus a marketplace of extensions that make it easy to extend functionality. To setup VS Code for CS 100, follow the next steps:
- Download and install VS Code on your machine from [this link](https://code.visualstudio.com/download). Instructions are provided for Windows, Linux, and Mac Operating Systems. Make sure you pick the right version depending on the type of processor you have.
- Open VS Code and go to the extension marketplace (by clicking on the icon with four squares in the left pane of by pressing Ctrl+Shift+X). Search for the extension called Remote-SSH (make sure it is the one published by Microsoft with the blue ribbon of verification). Install the extension (in some instances it might be installed already).
-  Open the command palette (press F1) and type Remote-SSH. You should see an option called "Remote-SSH: Connect to Host". Click on it.
-  Click "Add a new host" and type the following in the textbox that appears:
```sh
ssh <your_CS_username>@cs100.cs.ucr.edu
```
- A new VS Code editor will appear and prompt you for your password for the CS100 server. Type in your password. Now you are connected to the server (to confirm, look for a bar at the bottom left corner with the legend "SSH: cs100.cs.ucr.edu"). 
- Open the extension marketplace and verify that you have two lists: local and ssh installed extensions. Some extensions are installed but disabled by default. Make sure you install or enable the following:
C/C++ by Microsoft
C/C++ Extension Pack by Microsoft
C/C++ Themes by Microsoft
CMake Tools by Microsoft
YAML by Red Hat
Better C++ Syntax by Jeff Hykin
- Click on the menu Terminal > New Terminal. At the bottom of your development area, you should see a fully functioning terminal. You can use this to run terminal commands from now on.
- Click on Source Control in the left task bar (logo is three dots connected by two lines) or press Ctrl+Shift+G. You should see two options: Open Folder and Clone Repository. Click on Open Folder and pick the folder for this Lab. You will be prompted for you password again. After writing your password, you should see the files you created for Part 1. Since this folder is already connected to the repository, you don't need to publish it or clone a new one
- To build and run your code, use the VS Code terminal to type `cmake .` then `make` then run the executable using `./<name-of-executable>`. 
<!-- - Click on the menu Terminal > Run Build Task. You might be asked for the compiler (g++ or GCC) and if you want to use your CMake: Build.--> 

There are ways to do in VS Code all the tasks explained in Part 1 (automatically build a CMake, add file to git, compile and run your code). For now, we will let you explore those options. The terminal will always be a safe option if you are unsure on how to do it in the IDE.

### Git Push & Pull

While git is a version control system (VCS), GitHub is a remote repository which is an important distinction for two reasons. The first is that up until now all the work you’ve done has only been saved locally, so if there is a problem with your computer you would have no backup and therefore no way to recover the files. The second is that because all the changes are local, there is no way for people collaborating with you to see or receive your changes. Go to your GitHub repository for this lab, and you should see that none of the work you've done is listed.

 Since we cloned the remote repository from GitHub directly, our local repository is already associated with a remote repository (usually referred to as “remote” or “upstream”). In part 1, you committed your changes but you may notice they are not in your repository yet. In order to send the changes, we’ve made locally to GitHub, we just need to “push” them up to the server (do this now).

```sh
$ git push
```

This will push all the commits you've made since your last push assuming there haven't been any changes to the remote GitHub repo that your local Git doesn't know about. Notice that if you are not the first to push your changes, you might get a message asking you to update your local repo. For that, run the following command:
```sh
$ git pull
```

If there have been changes you will need to "pull" and "merge" those changes into your local repository, but we will cover those steps in a future lab when we cover Git and GitHub in more depth.

## Submission
Perform the following tasks before your demo. Use VS Code to generate and display the code files.

- Create another main file called `shape_main.cpp`. In this one, the user will be prompted to choose a rectangle or a triangle. Followed by a prompt asking for height and width if it is a rectangle, base instead of width if it is a triangle. Then, it will return the area for the chosen shape and dimensions.
- Create a new `triangle.hpp` and `triangle.cpp` that supports the functionality of `shape_main.cpp`. Compile the code into an executable called `shape_area_calculator`

To gain full credit, your project should feature the following:
- The repository should have the appropriate files from part 1 and the submission (excluding executables).
- `shape_main.cpp` should perform input validation and reject invalid values (for example, less than 0 or letters for dimension).
- When demoing, the machine used to display the code should have VS Code open and connected to the CS100 server. Have the Cmake file, shape_main.cpp, triangle.hpp and triangle.cpp files open. During your demo, you will walk the TA through your code, compile, and run it.
