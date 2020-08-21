# project-chtholly-qt
This is the Qt rewritten version of project chtholly.

![Licensed under GPL v3](https://www.gnu.org/graphics/gplv3-with-text-136x68.png)


## Usage
Special format is required for namelist files, which should meet the following conditions.

1. It must be a plain text file.
2. The first line should be a single integer *n*, denoting the total number of students.
3. Then *n* lines follow, each line should contain a single name, **as for version 0.9.4, you cannot put spaces in the names, this will be supported in one of the future releases**.


## Download

If you want the stable version, go to [Releases](https://github.com/Ravenclaw-OIer/project-chtholly-qt/releases) page and download the stable release.

The nightly build which are the latest working version can also be downloaded there, **Note that it can be pretty buggy and should NOT be used in production environment**. 

You can also compile and build from source.

### Building from source
Requires:
- CMake >= 3.5
- Qt 5.14
- g++ (must support at least C++14 standard)

On GNU/Linux systems, you can run

```shell script
cd /path/to/installation
cmake .
make
```

## Todo list

- [ ] Encrypt save file (#3)
- [ ] Optimize UI (#5)
- [ ] Thorough runtime logging 

## Contributing
Contributions of all kind welcome! No conditions apply other than GitHub's standard requirements.
