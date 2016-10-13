call setup-clean.bat
mklink /d WebServer\nodejs-webserver ..\..\..\nodejs-webserver
mkdir Controller\controller
mklink /d Controller\controller\src ..\..\..\..\controller\src
mklink /d Controller\controller\include ..\..\..\..\controller\include
mklink /d Controller\include ..\..\..\include
