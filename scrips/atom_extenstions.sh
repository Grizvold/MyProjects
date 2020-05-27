#!/bin/sh
#creating runnable script on linux
#chmod +x atom_extenstions
#./atom_extenstions

Red='\e[0;31m';
RCol='\e[0m';
#echo -e "${Red}this is red text${RCol}"

#installing apm
echo -e "${Red}apm help install${RCol}"
apm help install

#Beautify HTML, CSS, JavaScript, PHP, Python, Ruby, Java, C, C++, C#, Objective-C, CoffeeScript, TypeScript, Coldfusion, SQL, and more in Atom.
echo -e "${Red}apm install atom-beautify${RCol}"
apm install atom-beautify

#JavaScript code intelligence for atom with tern. Adds support for ES5, ES6, ES7, ES8, Node.js and more. Extendable via plugins.
echo -e "${Red}apm install atom-ternjs${RCol}"
apm install atom-ternjs

#Automates closing of HTML Tags
echo -e "${Red}apm install autoclose-html${RCol}"
apm install autoclose-html

#Emmet – the essential tool for web developers
echo -e "${Red}apm install emmet${RCol}"
apm install emmet

#CSSLint error reports for your Atom editor
echo -e "${Red}apm install csslint${RCol}"
apm install csslint

#A package to display colors in project and files.
echo -e "${Red}apm install pigments${RCol}"
apm install pigments

#EJS support for Atom.
echo -e "${Red}apm install language-ejs${RCol}"
apm install language-ejs

#A live preview tool for Atom Editor.
echo -e "${Red}apm install atom-html-preview${RCol}"
apm install atom-html-preview

#Enable Sublime style 'Column Selection'. Just hold 'alt' while you select, or select using your middle mouse button. Also similar to Texmate's 'Multiple Carets', or BBEdit's 'Block Select'.
echo -e "${Red}apm install sublime-style-column-selection${RCol}"
apm install sublime-style-column-selection

#Lint your JavaScript files in Atom with ESLint
echo -e "${Red}apm install eslint${RCol}"
apm install eslint
