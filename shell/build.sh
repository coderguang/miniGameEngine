#shell
#***********************************************
#
#      Filename: build.sh
#
#      Author: royalchen 
#      Email: royalchen@royalchen.com
#      website: www.royalchen.com
#      Description: ----
#

#     Create: 2017-12-20 20:01:52
#     Last Modified: 2017-12-20 20:01:52
#***********************************************


source ./config.sh

#first make Engine

ENGINE_CODE_DIR=$PRO_ROOT_DIR/Engine



function build_engine(){
	cp makefile_for_lib $ENGINE_CODE_DIR
	cd $ENGINE_CODE_DIR
	svn update .
	echo -e "$GREEN first clean $BLACK"
	#time make -f makefile_for_lib clean
	time make -f makefile_for_lib clean LIB_NAME="libEngine.a" CC="$CC" CFLAG="$LIB_CFLAG" PROJECT_BIN_DIR="$BIN_DIR" PROJECT_LIB_DIR="$LIB_DIR"
	echo -e "$GREEN start build Engine... $BLACK"
	time make -f makefile_for_lib all LIB_NAME="libEngine.a" CC="$CC" CFLAG="$LIB_CFLAG" PROJECT_BIN_DIR="$BIN_DIR" PROJECT_LIB_DIR="$LIB_DIR"
	EXCODE=$?
  	if [ "$EXCODE" != "0" ]; then
   	 echo -e "$RED build Engine error,please check$BLACK"
   	 exit 1
  	fi
	echo -e "$GREEN build Engine success! $BLACK"
	#back to cur dir
	cd $SHELL_ROOT_DIR
}


function build_libs(){
	for v in ${arr_lib[@]};do
		name=$v
		tmpDir=$PRO_GAME_ENGINE_DIR/$name
		cp makefile_for_lib $tmpDir
		cd $tmpDir

		svn update .
		echo -e "$GREEN first clean $name $BLACK"
		time make -f makefile_for_lib clean LIB_NAME="lib$name.a" CC="$CC" CFLAG="$LIB_CFLAG" PROJECT_BIN_DIR="$BIN_DIR" PROJECT_LIB_DIR="$LIB_DIR"
		echo -e "$GREEN start build $name... $BLACK"
		time make -f makefile_for_lib all LIB_NAME="lib$name.a" CC="$CC" CFLAG="$LIB_CFLAG" PROJECT_BIN_DIR="$BIN_DIR" PROJECT_LIB_DIR="$LIB_DIR"
		EXCODE=$?
  		if [ "$EXCODE" != "0" ]; then
   	 		echo -e "$RED build $name error,please check$BLACK"
   	 		exit 1
  		fi
		
		echo -e "$GREEN build $name success! $BLACK"
		#back to cur dir
		cd $SHELL_ROOT_DIR
	done

}

function build_apps(){
	for v in ${arr_bin[@]};do
		name=$v
		tmpDir=$PRO_GAME_ENGINE_DIR/$name
		cp makefile_for_srv $tmpDir
		cd $tmpDir
		svn update .

		echo -e "$GREEN first clean $name $BLACK"
		time make -f makefile_for_srv clean SRV_NAME="$name" CC="$CC" CFLAG="$BIN_CFLAG" PROJECT_BIN_DIR="$BIN_DIR" PROJECT_LIB_DIR="$LIB_DIR" LIBS="$LIBS"
		echo -e "$GREEN start build $name... $BLACK"
		time make -f makefile_for_srv all SRV_NAME="$name" CC="$CC" CFLAG="$BIN_CFLAG" PROJECT_BIN_DIR="$BIN_DIR" PROJECT_LIB_DIR="$LIB_DIR" LIBS="$LIBS"
		EXCODE=$?
  		if [ "$EXCODE" != "0" ]; then
   	 		echo -e "$RED build $name error,please check$BLACK"
   	 		exit 1
  		fi
		
		echo -e "$GREEN build $name success! $BLACK"
		#back to cur dir
		cd $SHELL_ROOT_DIR
	done

}

function clean_all(){
	echo -e "$GREEN start clean Engine $BLACK"
	cp -fr makefile_for_lib $ENGINE_CODE_DIR
	cd $ENGINE_CODE_DIR
	time make -f makefile_for_lib clean LIB_NAME="libEngine.a" CC="$CC" CFLAG="$LIB_CFLAG" PROJECT_BIN_DIR="$BIN_DIR" PROJECT_LIB_DIR="$LIB_DIR"
	EXCODE=$?
  	if [ "$EXCODE" != "0" ]; then
  		echo -e "$RED clean Engine error,please check$BLACK"
    	exit 1
  	fi
	cd $SHELL_ROOT_DIR

	for v in ${arr_lib[@]};do
		name=$v
		tmpDir=$PRO_GAME_ENGINE_DIR/$name
		cp -fr makefile_for_lib $tmpDir
		cd $tmpDir
		echo -e "$GREEN start clean $name $BLACK"
		time make -f makefile_for_lib clean LIB_NAME="lib$name.a" CC="$CC" CFLAG="$LIB_CFLAG" PROJECT_BIN_DIR="$BIN_DIR" PROJECT_LIB_DIR="$LIB_DIR"

		EXCODE=$?
  		if [ "$EXCODE" != "0" ]; then
   	 		echo -e "$RED clean $name error,please check$BLACK"
   	 		exit 1
  		fi
		
		cd $SHELL_ROOT_DIR
	done
	
	for v in ${arr_bin[@]};do
		name=$v
		tmpDir=$PRO_GAME_ENGINE_DIR/$name
		cp makefile_for_srv $tmpDir
		cd $tmpDir
		echo -e "$GREEN start clean $name $BLACK"
		time make -f makefile_for_srv clean SRV_NAME="$name" CC="$CC" CFLAG="$BIN_CFLAG" PROJECT_BIN_DIR="$BIN_DIR" PROJECT_LIB_DIR="$LIB_DIR" LIBS="$LIBS"
		EXCODE=$?
  		if [ "$EXCODE" != "0" ]; then
   	 		echo -e "$RED clean $name error,please check$BLACK"
   	 		exit 1
  		fi
		cd $SHELL_ROOT_DIR
	done

}


clean_all
build_engine
build_libs
build_apps

