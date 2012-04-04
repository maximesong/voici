#!/bin/sh

if [[ `basename $PWD` = "tools" ]]
then  cd ..
fi
ROOT_PATH=$PWD
RELEASE_PATH=$PWD/release-`date +%y-%m-%d`/
PROJECT_FILE=$ROOT_PATH/voici.pro
TARGET_FILE=voici
TARGET_FILE_ZH=voici_zh
TARGET_FILE_EN=voici_en

IMPROVE_UI_DOCS="improve_ui_en improve_ui_zh"

rm -rf $RELEASE_PATH
mkdir $RELEASE_PATH
mkdir $RELEASE_PATH/doc
mkdir $RELEASE_PATH/build

cd $ROOT_PATH

# Update the transaltion
lrelease voici.pro

# Turn off quick test
perl -i -p -e "s/DEFINES \+= QUICK_TEST/#DEFINES \+= QUICK_TEST/" voici.pro
# The zh version
perl -i -p -e "s/#DEFINES \+= LANGUAGE_ZH/DEFINES \+= LANGUAGE_ZH/" voici.pro
qmake
make clean
make
mv $ROOT_PATH/$TARGET_FILE $RELEASE_PATH/$TARGET_FILE_ZH

# The en version
perl -i -p -e "s/DEFINES \+= LANGUAGE_ZH/#DEFINES \+= LANGUAGE_ZH/" voici.pro
qmake
make clean
make
mv $ROOT_PATH/$TARGET_FILE $RELEASE_PATH/$TARGET_FILE_EN

# Turn on quick test
perl -i -p -e "s/#DEFINES \+= QUICK_TEST/DEFINES \+= QUICK_TEST/" voici.pro


cp -r $ROOT_PATH/doc/improve_ui/ $RELEASE_PATH/build/improve_ui
cd $RELEASE_PATH/build/improve_ui
for DOC in $IMPROVE_UI_DOCS
do 
    echo "HELLO"
    xelatex $DOC.tex
    mv $RELEASE_PATH/build/improve_ui/$DOC.pdf $RELEASE_PATH/doc
done

# cp -r $ROOT_PATH/{src,texture,music,lib,tools,dll} $RELEASE_PATH

# cp $TARGET_FILES_LINUX $RELEASE_PATH

if [[ -e $ROOT_PATH/voici_en.exe ]]; then
     cp $ROOT_PATH/dll/* $RELEASE_PATH
     cp $ROOT_PATH/basketball.exe $RELEASE_PATH
fi

rm -r $RELEASE_PATH/build

# Source Code
#cp $PROJECT_FILE $RELEASE_PATH

cd $RELEASE_PATH
find -name "*~" | xargs rm
zip -r release-`date +%y-%m-%d`.zip .

