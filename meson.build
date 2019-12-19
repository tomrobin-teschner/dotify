# dotify project
project('dotify', 'cpp', license: 'GPL3', version: '1.0.0', default_options: 'cpp_std=c++14')

#source files
sources = [
            'src/color.cpp',
            'src/fileReader.cpp',
            'src/format.cpp',
            'src/lineParser.cpp',
            'src/main.cpp',
            'src/processCommandLineArguments.cpp',
            'src/styling.cpp'
          ]

# include directories
inc = include_directories('include/')

# generate the executable
executable('dotify', sources, include_directories: inc, install: true)