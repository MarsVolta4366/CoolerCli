# Cooler CLI
## A simple C++ 17 static library for building CLI tools.

### How to use Cooler CLI as a reference in another project:
1. Clone this repo to your local machine.
2. Open Visual Studio Properties and go to Linker -> Input and under "Additional Dependencies" add the path to the static .lib file with file name.
3. In Visual Studio Properties, go to VC++ Dirctories and under "Include Directories" add the path to ParseArgs.h not including the file name.

### How to use Cooler CLI:
Currently, Cooler CLI only allows for arguments in the format of a hypen followed by a character optionally followed by a value.
For example `-c -n <name>`

Initialize `ParseArgs` then call `addArgs` and pass your argument count and arguments:
```
coolercli::ParseArgs parseArgs;
parseArgs.addArgs(argc, argv);
```
Check if an argument was passed in:
```
parseArgs.argKeyExists("-n");
```
Get value passed in after an argument:
```
parseArgs.getArgValue("-n");
```