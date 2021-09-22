# EZHTML : An easy ~~copy and paste machine~~ static website generator
## Why use this?
I know about the existence of Jekyll and its easy integration with Github Pages, but always thought of something more ... customizable. With EZHTML you can configure all the CSS, JS, and even how the HTML is created in each individual file. I started this project due to the frustration from writing a website with only HTML and a filesystem. I got tired really quickly from changing the Navbar or Footer and had to copy those to each and every file. As a result, I created this project to minimize my time dealing with those repeating and tedious processes.

## How to use EZHTML? 
### Generallized File Structure
```
.
├── FOOTER.html
├── LICENSE
├── NAV.html
├── README.md *
├── INFO
├── pg1.html  *
├── pg2.html  *
├── static    *
│   ├── css   *
│   │   └── styles.css *
│   └── img   *
└── staticSiteGenerator.cpp
```
- Those with a * is only optional; you can still generate a website using only the none-stared files.
## `INFO` file syntax (Yes, I created this syntax, shut up)
- `^` + command => Configures how the the static site is generated
    - `CSS` + number => Number of CSS entries you want in each file. (Enter each entrie in the next line, breaking with each line)
    - `JS` + number => Number of JS entries you want in each file. (Enter each entrie in the next line, breaking with each line)
    - `LOCATION` + NEXTLINE + DIRECTORY_NAME => Where you want the whole thing to be generated. Defaults to `docs` if no `LOCATION` was detected. It must be before you define each of the pages.
        - Note: DO NOT USE `./` or else the program will be buggy.
        - Note: The program will clear everything in `./LOCATION/` and then generate the website in `./LOCATION/`, so be careful what files you put in there.
- `#` + File Title => Configures how each page's title will be. Write a `#` command with each file you want. This title will be used in the `<title>` tag in `<head>` (Skip a line and enter the file name, without `.html`)
- Example:
```
^LOCATION
output

^CSS2
./static/css/styles.css
./static/css/anothercss.css

^JS3
./static/js/movingAnimation.js
./static/js/goUp.js
./static/js/switchPageAnimation.js

#Page 1
pg1
#Page 2
pg2
#Homepage
index
#Bibliography
bibliogrpahy
```

## How the generator works
### For each file (`#`, if you remember):
```html
<html>
<head>
    <title>
```
- INSERT TITLE (from `#`)
```html
    </title>
```
- INSERT CSS INFO FROM INFO

```html
</head>
<body>
```
- INSERT everything in NAV.html
```html
    <div class="container">
```
- INSERT everything in `fileName`.html in /
```html
    </div>
```
- INSERT JS records
- INSERT everything in FOOTER.html
```html
</body>
</html>
```
## Stuff that are important but I don't know where to put
- BE SURE TO USE `C++17` or else this will not work.
- Yes, the generator will automatically copy everything in `./static` to `./[WHATEVER_YOU_DEFINED]/static`.
- The compiler will generate everything to `./WHATEVER_YOU_DEFINED`, then you can use services like Github Pages to automatically host your webiste there.
    - NOTE: As of April 5, 2021, Github Pages only suport hosting on `/docs` or `/`, as a result, the generator will automaticaly generate the website to `./docs` and not `./output`
- Compiled version is in `Releases`
- This is only tested on macOS 12.2.3 (Intel), compiled using g++ (C++17). AMD64 Linux also works, but I'm not sure about Windows.
- Compile this using `g++ EZHTML.cpp -std=c++17 -o EZHTML` and execute using `./EZHTML`
- I know this documentation sucks. If you have any questions, feel free to create an issue or email me at [longyklee@gmail.com](mailto:longyklee@gmail.com?subject=EZHTML) with the subject `EZHTML`.
## What is this written with
- C++17
- `<fstream>` to read and write to the files
- `<filesystem>` to copy the entire directory (this is the main reason I had to use `C++17`)
```
EZHTML : An easy static website generator, written entirely in C++
Copyright (C) 2021 Aaron Lee

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Affero General Public License as
published by the Free Software Foundation, either version 3 of the
License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
```
