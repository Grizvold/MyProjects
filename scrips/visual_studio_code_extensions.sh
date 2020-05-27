#!/bin/sh
#creating runnable script on linux
#chmod +x visual_studio_code_extensions.sh
#./visual_studio_code_extensions.sh

Red='\e[0;31m';
RCol='\e[0m';
#echo -e "${Red}this is red text${RCol}"


#HTML preview  publisher:"George Oliveira"

#installing Path Intellisence
echo -e "${Red}code --install-extension christian-kohler.path-intellisense${RCol}"
code --install-extension christian-kohler.path-intellisense

#installing Python
echo -e "${Red}code --install-extension ms-python.python${RCol}"
code --install-extension ms-python.python

#installing Live Server
echo -e "${Red}code --install-extension ritwickdey.liveserver${RCol}"
code --install-extension ritwickdey.liveserver

#installing Visual Studio Intellicode
echo -e "${Red}code --install-extension visualstudioexptteam.vscodeintellicode${RCol}"
code --install-extension visualstudioexptteam.vscodeintellicode

#installing Prettier
echo -e "${Red}code --install-extension esbenp.prettier-vscode${RCol}"
code --install-extension esbenp.prettier-vscode

#installing Bracket Pair Colorizer
echo -e "${Red}code --install-extension coenraads.bracket-pair-colorizer${RCol}"
code --install-extension coenraads.bracket-pair-colorizer

#installing Quokka
echo -e "${Red}code --install-extension wallabyjs.quokka-vscode${RCol}"
code --install-extension wallabyjs.quokka-vscode

#installing JavaScript (ES6) Code Snippets
echo -e "${Red}code --install-extension xabikos.javascriptsnippets${RCol}"
code --install-extension xabikos.javascriptsnippets

#installing Code Spell Checker
echo -e "${Red}code --install-extension streetsidesoftware.code-spell-checker${RCol}"
code --install-extension streetsidesoftware.code-spell-checker

#installing Auto Close Tag
echo -e "${Red}code --install-extension formulahendry.auto-close-tag${RCol}"
code --install-extension formulahendry.auto-close-tag

#installing stylelint-plus
echo -e "${Red}code --install-extension hex-ci.stylelint-plus${RCol}"
code --install-extension hex-ci.stylelint-plus

#installing ESLint
echo -e "${Red}code --install-extension dbaeumer.vscode-eslint${RCol}"
code --install-extension dbaeumer.vscode-eslint

#installing Color Highlight
echo -e "${Red}code --install-extension naumovs.color-highlight${RCol}"
code --install-extension naumovs.color-highlight

#installing EJS language support
echo -e "${Red}code --install-extension DigitalBrainstem.javascript-ejs-support${RCol}"
code --install-extension DigitalBrainstem.javascript-ejs-support

#installing Toggle Column Selection
echo -e "${Red}code --install-extension erikphansen.vscode-toggle-column-selection${RCol}"
code --install-extension erikphansen.vscode-toggle-column-selection

#installing file-icons
echo -e "${Red}code --install-extension file-icons${RCol}"
code --install-extension file-icons

#installing Debugger for Chrome
#echo -e "${Red}code --install-extension msjsdiag.debugger-for-chrome"
#code --install-extension msjsdiag.debugger-for-chrome
